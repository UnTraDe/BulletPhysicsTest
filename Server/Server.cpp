#include "Server.h"

Server::Server(int port)
{
	m_ENetAddress.host = ENET_HOST_ANY;
	m_ENetAddress.port = port;

	ENetHost * server = enet_host_create(&m_ENetAddress, 32, 2, 0, 0);
}

Server::~Server()
{
	enet_host_destroy(m_ENetHost);
}

void Server::Run()
{
	unsigned int counter = 0;
	ENetEvent event;

	while (enet_host_service(m_ENetHost, &event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			printf("A new client connected from %x:%u.\n", event.peer->address.host, event.peer->address.port);
			event.peer->data = &counter;
			counter++;
			m_Clients.push_back(event.peer);
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			printf("A packet of length %u containing %s was received from %s on channel %u.\n", event.packet->dataLength, event.packet->data, event.peer->data, event.channelID);
			
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%s disconected.\n", event.peer->data);
			event.peer->data = NULL;
			break;
		}
	}
}

void Server::ProcessPacket(ENetPacket* packet)
{
	
	
	enet_packet_destroy(packet);
}