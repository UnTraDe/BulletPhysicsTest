#pragma once

#include <queue>
#include <memory>
#include <enet/enet.h>
#include "Packet.h"

class Client
{
public:
	Client() {};
	Client(ENetPeer* enetPeer) { m_ENetPeer = enetPeer; m_ID = *(int*)enetPeer->data; };
	~Client() {};

	void Send(void* data, int size, int channel, int flags);

private:
	ENetPeer* m_ENetPeer;
	int m_ID;
	std::queue<std::shared_ptr<Packet>> m_OutgoingPackets;
	std::queue<std::shared_ptr<Packet>> m_IncomingPackets;
};