#pragma once

class IPacket
{
public:
	virtual char* GetSerializedData() = 0;
};