#pragma once

#include <vector>
#include "WorldStatePacket.h"
#include "Object.h"
#include "Cube.h"

class World
{
public:
	World() { Initialize(); };
	~World() { };
	void Initialize();
	void Run();
	WorldStatePacket TakeSnapshot();

private:
	std::vector<Object*> m_Objects;
};