#include "World.h"

void World::Initialize()
{
	int objectCounter = 0;

	float color[3] { 0.0f, 1.0f, 0.0f };
	float position[3] { 0.0f, 50.0f, 0.0f };
	m_Objects.push_back(new Cube(objectCounter, position, color));

	objectCounter++;
}

void World::Run()
{

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