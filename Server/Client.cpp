#include "Client.h"

void Client::Send(void* data, int size, int channel, int flags)
{
	ENetPacket* packet = enet_packet_create(data, size, flags);
	enet_peer_send(m_ENetPeer, channel, packet);
}