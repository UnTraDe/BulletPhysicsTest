#pragma once

#include <vector>
#include "Packet.h"
#include "Structures.h"

#include <assert.h>

class WorldStatePacket : public Packet
{
public:
	WorldStatePacket() {};
	WorldStatePacket(const unsigned char* data, int dataSize);
	~WorldStatePacket() {};
	virtual unsigned char* GetData();
	virtual int GetDataSize();

	void AddObject(ObjectState objectState) { m_Objects.push_back(objectState); };

private:
	std::vector<ObjectState> m_Objects;
};