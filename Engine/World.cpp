#include "World.h"

World::World(glm::mat4 projection)
{
	mProjection = projection;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_CULL_FACE);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

World::~World()
{
	delete terrain;
	delete mDynamicsWorld;
	delete mSolver;
	delete mDispatcher;
	delete mCollisionConfiguration;
	delete mBroadphase;
	delete mGui;
}

void World::Initialize()
{
	//-Resources-

	ResourceManager* resources = ResourceManager::GetInstance();
	//Load Shaders
	resources->LoadShader("default.vert", "", "default.frag");
	resources->LoadShader("simple.vert", "", "simple.frag");
	resources->LoadShader("terrain.vert", "", "terrain.frag");

	//Load Textures
	resources->LoadTextureTransparent("cursor.png");
	resources->LoadTexture("grass.png");

	//Create Camera
	mCamera = new FPSCamera(glm::vec3(0.0f, 10.0f, 2.0f));

	//-Physics-
	srand(time(NULL));
	//Setup World
	mBroadphase = new btDbvtBroadphase();
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mSolver = new btSequentialImpulseConstraintSolver;
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);
	//World Properties
	mDynamicsWorld->setGravity(btVector3(0, -10, 0));

	terrain = new Terrain(100);
	mDynamicsWorld->addRigidBody(terrain->GetRigidBody());
	for (int i = 0; i < 10; i++)
	{
		glm::vec3 color(((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f));
		Cube* cube = new Cube(color);
		cube->SetPosition(glm::vec3(i % 5, 0.5, i / 5) * 2.0f);
		mObjects.push_back(cube);
		mDynamicsWorld->addRigidBody(cube->GetRigidBody());
	}

	player = new Player();
	player->SetPosition(glm::vec3(1, 30, 1));
	mObjects.push_back(player);
	mDynamicsWorld->addRigidBody(player->GetRigidBody());

	//Models
	Model* testModel = Model::ReadModelFromObjFile("resources/models/MetalBarrel.obj", 0.01f);
	ObjectModel* objm = new ObjectModel(glm::vec3(20, 50, 20), testModel);
	mObjects.push_back(objm);
	mDynamicsWorld->addRigidBody(objm->GetRigidBody());
	mGui = new Gui();
}

void World::Update(float deltaTime, GLFWwindow* window)
{
	objects = 0;
	for (std::vector<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		objects++;
		(*it)->Update(deltaTime);
		if ((*it)->IsAlive() == false)
		{
			Explode((*it)->GetPosition(), 100, 10);
			mDynamicsWorld->removeRigidBody((*it)->GetRigidBody());
			delete (*it);
			*it = nullptr;
		}
	}
	mObjects.erase(std::remove(std::begin(mObjects), std::end(mObjects), nullptr), std::end(mObjects));

	mCamera->SetPosition(this->player->GetPosition() + glm::vec3(0, 0.6f, 0));
	ProcessInput(deltaTime, window);
	mCamera->Update();
	mDynamicsWorld->stepSimulation(1 / 60.f, 10);
}

void World::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glm::mat4 view = mCamera->GetView();
	terrain->Render(mProjection, view);

	for (std::vector<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		(*it)->Render(mProjection, view);
	}
	mGui->Render();
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
		vel.setY(4.0 * speed);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetTime() - lastShot > 0.5)
	{
		lastShot = glfwGetTime();
		glm::vec3 dir = mCamera->GetDirection();
		Bullet* bullet = new Bullet();
		bullet->SetPosition(player->GetPosition() + glm::vec3(0, 0.6f, 0) + glm::normalize(mCamera->GetDirection()));
		bullet->GetRigidBody()->setLinearVelocity(btVector3(dir.x, dir.y, dir.z).normalize() * 100.0);
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

	//Gui cursor scaling
	/*glm::vec3 dir1 = mCamera->GetDirection() * 2.0f;
	glm::vec3 dir = mCamera->GetDirection() * 100.0f;
	glm::vec3 pos = mCamera->GetPosition();
	if (pos.x * pos.y * pos.z == 0)
		return;
	btCollisionWorld::ClosestRayResultCallback RayCallback(btVector3(pos.x, pos.y, pos.z), btVector3(pos.x + dir.x, pos.y + dir.y, pos.z + dir.z));
	mDynamicsWorld->rayTest(btVector3(pos.x + dir1.x, pos.y + dir1.y, pos.z + dir1.z), btVector3(pos.x + dir.x, pos.y + dir.y, pos.z + dir.z), RayCallback);

	float scale = 1.0f;
	if (RayCallback.hasHit()) {
		float d = btDistance(btVector3(pos.x, pos.y, pos.z), RayCallback.m_hitPointWorld) / 10.0f;
		scale = d;
	}
	btClamp(scale, 1.0f, 4.0f);
	mGui->scale = scale;*/
}

void World::Explode(glm::vec3 pos, float power, float radius)
{
	for (std::vector<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		if ((*it) == NULL)
			continue;
		float distance = glm::distance((*it)->GetPosition(), pos);
		if (distance == 0 || distance >= radius)
			continue;
		glm::vec3 dir = (*it)->GetPosition() - pos;
		dir = glm::normalize(dir);
		(*it)->GetRigidBody()->activate();
		(*it)->GetRigidBody()->applyCentralImpulse(btVector3(dir.x, dir.y, dir.z) * power / (distance / radius));
	}
	/*btGhostObject* explosionObj = new btPairCachingGhostObject();
	btCollisionShape* explosionshape = new btSphereShape(radius);
	explosionObj->setCollisionShape(explosionshape);
	explosionObj->setCollisionFlags(explosionObj->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	explosionObj->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));

	mDynamicsWorld->addCollisionObject(explosionObj, btBroadphaseProxy::SensorTrigger, btBroadphaseProxy::AllFilter);
	btAlignedObjectArray<btCollisionObject*> inrangeObjects = explosionObj->getOverlappingPairs();
	for (int i = 0; i < inrangeObjects.size(); i++)
	{
		if (!inrangeObjects.at(i)->isStaticObject())
		{
			btCollisionObject* obj = inrangeObjects.at(i);

			btVector3 explosionDir = obj->getWorldTransform().getOrigin() - btVector3(pos.x, pos.y, pos.z);
			explosionDir.normalize();

			btRigidBody::upcast(obj)->applyCentralImpulse(explosionDir*power); //problem is here, commenting out this line prevents crash
		}
	}

	mDynamicsWorld->removeCollisionObject(explosionObj);
	delete explosionObj;
	delete explosionshape;*/
}