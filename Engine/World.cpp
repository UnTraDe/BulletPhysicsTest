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
	resources->LoadShader("textured.vert", "textured.frag");

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
	mDynamicsWorld->addRigidBody(groundRigidBody);

	

	for (int i = 0; i < 100; i++)
	{
		glm::vec3 color(((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f), ((std::rand() % 255) / 255.0f));
		Cube* cube = new Cube(color);
		cube->SetPosition(glm::vec3(i % 10, 50, i / 10) * 1.1f);
		mObjects.push_back(cube);
		mDynamicsWorld->addRigidBody(cube->GetRigidBody());
	}
}

void World::Update(float deltaTime, GLFWwindow* window)
{
	mDynamicsWorld->stepSimulation(1 / 60.f, 10);

	for (std::vector<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
	
	ProcessInput(deltaTime, window);	
	mCamera->Update();
}

void World::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = mCamera->GetView();

	for (std::vector<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		(*it)->Render(mProjection, view);
	}
}

void World::ProcessInput(float deltaTime, GLFWwindow* window)
{
	float speed = 0.1f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mCamera->MoveForward(speed);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mCamera->MoveBackward(speed);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mCamera->MoveLeft(speed);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mCamera->MoveRight(speed);

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