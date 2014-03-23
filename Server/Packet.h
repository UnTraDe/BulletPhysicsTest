#pragma once

#define PACKET_WORLD_STATE 1


class Packet
{
public:
	virtual unsigned char* GetData() = 0;
	virtual int GetDataSize() = 0;
};