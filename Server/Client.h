#pragma once

#include <queue>
#include <memory>
#include <enet/enet.h>
#include "Packet.h"

class Client
{
public:
	Client(ENetPeer* enetPeer) { m_ENetPeer = enetPeer; m_ID = *(int*)enetPeer->data; };
	~Client();

	template<struct T>
	void Send(const T &packet)
	{
		ENetPacket* packet = enet_packet_create((char*)T, sizeof(T), 0);
		enet_peer_send(m_ENetPeer, 0, packet);
	}

private:
	ENetPeer* m_ENetPeer;
	int m_ID;
	std::queue<std::shared_ptr<IPacket>> m_OutgoingPackets;
	std::queue<std::shared_ptr<IPacket>> m_IncomingPackets;
};