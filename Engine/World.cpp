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
	resources->LoadShader("depth.vert", "", "depth.frag");

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

	player = new Player();
	player->SetPosition(glm::vec3(10, 30, 10));
	mObjects.push_back(player);
	mDynamicsWorld->addRigidBody(player->GetRigidBody());

	//Models
	Model* testModel = Model::ReadModelFromObjFile("resources/models/MetalBarrel.obj", 0.01f);
	ObjectModel* objm = new ObjectModel(glm::vec3(20, 50, 20), testModel, new btCylinderShape(btVector3(0.55f, 0.80f, 0.55f)));
	mObjects.push_back(objm);
	mDynamicsWorld->addRigidBody(objm->GetRigidBody());
	mGui = new Gui();

	mFbo = new FrameBufferObject(1024);
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
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	glm::mat4 depthProj = glm::ortho<float>(-5, 5, -5, 5, -100, 100);
	glm::mat4 depthView = glm::lookAt(mCamera->GetPosition() - glm::normalize(glm::vec3(1.0f, -3.0f, 2.0f)) * 10.0f, mCamera->GetPosition(), glm::vec3(0, 1, 0));

	Shader* depthShader = resourceManager->GetShader("depth");
	Shader* defaultShader = resourceManager->GetShader("default");

	//			Depth map rendering
	mFbo->Bind();
	depthShader->Bind();
	RenderObjects(depthShader, depthProj, depthView, false);
	mFbo->Unbind();

	//			World rendering
	defaultShader->Bind();
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mFbo->textureID);
	glUniform1i(defaultShader->GetUniformLocation("shadowMap"), 1);

	GLuint depthMVPLocation = defaultShader->GetUniformLocation("depthMVP");
	glUniformMatrix4fv(depthMVPLocation, 1, GL_FALSE, &(depthProj * depthView)[0][0]);

	RenderObjects(defaultShader, mProjection, mCamera->GetView(), true);
	

	mGui->Render();
}

void World::RenderObjects(Shader* shader, glm::mat4 projection, glm::mat4 view, bool renderTerrain)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (renderTerrain)
		terrain->Render(projection, view, shader);

	for (std::vector<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		(*it)->Render(projection, view, shader);
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
		vel.setY(4.0 * speed);
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && glfwGetTime() - lastShot > 0.5)
	{
		bool bullet = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
		glm::vec3 color(((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f));
		lastShot = glfwGetTime();
		glm::vec3 dir = mCamera->GetDirection();
		Object* obj;
		if (bullet)
			obj = new Cube(color);
		else {
			obj = new Bullet();
			obj->GetRigidBody()->setLinearVelocity(btVector3(dir.x, dir.y, dir.z).normalize() * 100.0);
		}
		obj->SetPosition(player->GetPosition() + glm::vec3(0, 0.6f, 0) + glm::normalize(mCamera->GetDirection()));
		mObjects.push_back(obj);
		mDynamicsWorld->addRigidBody(obj->GetRigidBody());
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
}