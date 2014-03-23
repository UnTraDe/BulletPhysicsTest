#include "WorldStatePacket.h"

WorldStatePacket::WorldStatePacket(const unsigned char* data, int dataSize)
{
	assert(data[0] == PACKET_WORLD_STATE);
	int position = 1;

	unsigned short objectCount = 0;
	memcpy(&objectCount, &data[position], sizeof(unsigned short));
	position += sizeof(unsigned short);

	for (int i = 0; i < objectCount; i++)
	{
		ObjectState os;
		memcpy(&os, &data[position], sizeof(ObjectState));
		position += sizeof(ObjectState);
		AddObject(os);
	}

	assert((position + 1) == dataSize);
}

unsigned char* WorldStatePacket::GetData()
{
	unsigned char* data = new unsigned char[GetDataSize()];
	int position = 0;
	unsigned short objectCount = m_Objects.size();

	//Set header
	data[position] = PACKET_WORLD_STATE;
	position += 1;

	//Set object count
	memcpy(&data[position], (char*)&objectCount, sizeof(unsigned short));
	position += sizeof(unsigned short);

	//Fill the object array
	memcpy(&data[position], &m_Objects[0], sizeof(ObjectState)* m_Objects.size());
	position += sizeof(ObjectState)* m_Objects.size();

	return data;
}

int WorldStatePacket::GetDataSize()
{
	return 1 + sizeof(unsigned short) + (sizeof(ObjectState)* m_Objects.size());
}