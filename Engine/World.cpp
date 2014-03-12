#include "World.h"

World::World(glm::mat4 projection)
{
	mProjection = projection;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
}

World::~World()
{
	delete mDynamicsWorld;
	delete mSolver;
	delete mDispatcher;
	delete mCollisionConfiguration;
	delete mBroadphase;
}

void World::Initialize()
{
	//-Resources-

	ResourceManager* resources = ResourceManager::GetInstance();
	//Load Shaders
	resources->LoadShader("default.vert", "default.frag");

	//Load Textures
	//resources->LoadTexture("wooden_plank.jpg");

	//Create Camera
	mCamera = new FPSCamera(glm::vec3(0.0f, 10.0f, 2.0f));

	//-Physics-

	//Setup World
	mBroadphase = new btDbvtBroadphase();
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mSolver = new btSequentialImpulseConstraintSolver;
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);
	//World Properties
	mDynamicsWorld->setGravity(btVector3(0, -10, 0));

	
	//TODO Create special object for this
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setFriction(5.0);
	mDynamicsWorld->addRigidBody(groundRigidBody);

	for (int i = 0; i < 100; i++)
	{
		glm::vec3 color(((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f));
		Cube* cube = new Cube(color);
		cube->SetPosition(glm::vec3(i % 10, 0.5, i / 10) * 1.1f);
		mObjects.push_back(cube);
		mDynamicsWorld->addRigidBody(cube->GetRigidBody());
	}

	player = new Player();
	player->SetPosition(glm::vec3(-2, 1, -2));
	mObjects.push_back(player);
	mDynamicsWorld->addRigidBody(player->GetRigidBody());
}

void World::Update(float deltaTime, GLFWwindow* window)
{
	objects = 0;
	for (std::vector<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		if ((*it) == nullptr)
			continue;
		objects++;
		(*it)->Update(deltaTime);
		if ((*it)->IsAlive() == false || glm::distance(player->GetPosition(), (*it)->GetPosition()) > 100)
		{
			mDynamicsWorld->removeRigidBody((*it)->GetRigidBody());
			delete (*it);
			*it = nullptr;
		}
	}
	
	mCamera->SetPosition(this->player->GetPosition() + glm::vec3(0, 0.6f, 0));
	ProcessInput(deltaTime, window);
	mCamera->Update();
	mDynamicsWorld->stepSimulation(1 / 60.f, 10);
}

void World::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = mCamera->GetView();

	for (std::vector<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		if ((*it) == NULL)
			continue;
		(*it)->Render(mProjection, view);
	}
}

void World::ProcessInput(float deltaTime, GLFWwindow* window)
{
	float speed = 1.0f;
	btVector3 vel = btVector3(0,0,0);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed *= 5.0f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		vel.setX(vel.getX() + glm::sin(mCamera->GetHorizontalAngle()) * 7.0f);
		vel.setZ(vel.getZ() + glm::cos(mCamera->GetHorizontalAngle()) * 7.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		vel.setX(vel.getX() - glm::sin(mCamera->GetHorizontalAngle()) * 7.0f);
		vel.setZ(vel.getZ() - glm::cos(mCamera->GetHorizontalAngle()) * 7.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		vel.setX(vel.getX() + glm::sin(mCamera->GetHorizontalAngle() + glm::radians(90.0f)) * 7.0f);
		vel.setZ(vel.getZ() + glm::cos(mCamera->GetHorizontalAngle() + glm::radians(90.0f)) * 7.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		vel.setX(vel.getX() + glm::sin(mCamera->GetHorizontalAngle() - glm::radians(90.0f)) * 7.0f);
		vel.setZ(vel.getZ() + glm::cos(mCamera->GetHorizontalAngle() - glm::radians(90.0f)) * 7.0f);
	}
	vel *= speed;
	vel.setY(player->GetRigidBody()->getLinearVelocity().getY());

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		vel.setY(4.0);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetTime() - lastShot > 0.2)
	{
		lastShot = glfwGetTime();
		glm::vec3 dir = mCamera->GetDirection();

		Bullet* bullet = new Bullet();
		bullet->SetPosition(mCamera->GetPosition() + glm::normalize(mCamera->GetDirection() * 2.0f));
		bullet->GetRigidBody()->setLinearVelocity(btVector3(dir.x, dir.y, dir.z).normalize() * 400.0);
		mObjects.push_back(bullet);
		mDynamicsWorld->addRigidBody(bullet->GetRigidBody());
	}
	player->GetRigidBody()->setLinearVelocity(vel);
	int wX;
	int wY;
	glfwGetWindowSize(window, &wX, &wY);

	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);

	mCamera->AddVerticalAngle((float)((wY / 2.0f) - y) * 0.002f);
	mCamera->AddHorizontalAngle((float)((wX / 2.0f) - x) * 0.002f);
	
	glfwSetCursorPos(window, wX / 2, wY / 2);
}