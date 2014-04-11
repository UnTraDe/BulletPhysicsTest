#include "World.h"

long long milliseconds_now()
{
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (1000LL * now.QuadPart) / s_frequency.QuadPart;
	}
	else {
		return GetTickCount();
	}
}

void World::Initialize()
{
	m_Broadphase = new btDbvtBroadphase();
	m_CollisionConfiguration = new btDefaultCollisionConfiguration();
	m_Dispatcher = new btCollisionDispatcher(m_CollisionConfiguration);
	m_Solver = new btSequentialImpulseConstraintSolver;
	m_DynamicsWorld = new btDiscreteDynamicsWorld(m_Dispatcher, m_Broadphase, m_Solver, m_CollisionConfiguration);
	
	m_DynamicsWorld->setGravity(btVector3(0, -10, 0));

	int objectCounter = 0;

	float color[3] { 0.0f, 1.0f, 0.0f };
	float position[3] { 0.0f, 50.0f, 0.0f };
	Cube* cube = new Cube(objectCounter, position, color);
	m_Objects.push_back(cube);
	m_DynamicsWorld->addRigidBody(cube->GetRigidBody());

	objectCounter++;
}

void World::Run()
{
	m_IsRunning = true;
	
	long limit = (1 / 60.0f) * 1000;
	long previous = milliseconds_now();

	while (m_IsRunning)
	{
		long start = milliseconds_now();
		long deltaTime = start - previous;
		previous = start;

		std::cout << m_Objects[0]->GetObjectState().position[1] << std::endl;

		m_DynamicsWorld->stepSimulation(1 / 60.0f, 10);

		long end = milliseconds_now();
		long dt = end - start;

		if (dt < limit)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(limit - dt));
		}
	}
}

WorldStatePacket World::TakeSnapshot()
{
	WorldStatePacket wsp;
	
	for (std::vector<Object*>::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it)
	{
		ObjectState objectState = (*it)->GetObjectState();
		wsp.AddObject(objectState);
	}

	return wsp;
}