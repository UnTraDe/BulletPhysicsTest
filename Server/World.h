#pragma once

#include <thread>
#include <vector>
#include "WorldStatePacket.h"
#include "Object.h"
#include "Cube.h"

#include <iostream>
#include <Windows.h>

class World
{
public:
	World() { };
	~World() { };
	void Initialize();
	void Run();
	WorldStatePacket TakeSnapshot();

private:
	std::vector<Object*> m_Objects;
	bool m_IsRunning;

	btBroadphaseInterface* m_Broadphase;
	btDefaultCollisionConfiguration* m_CollisionConfiguration;
	btCollisionDispatcher* m_Dispatcher;
	btSequentialImpulseConstraintSolver* m_Solver;
	btDiscreteDynamicsWorld* m_DynamicsWorld;
};