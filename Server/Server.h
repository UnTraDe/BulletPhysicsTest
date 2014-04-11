#pragma once

#include <map>
#include <thread>
#include <enet/enet.h>
#include "Packet.h"
#include "Client.h"
#include "World.h"

class Server
{
public:
	Server(int port);
	~Server();

	void Run();
	
	
private:
	ENetAddress m_ENetAddress;
	ENetHost* m_ENetHost;

	World world;
	std::map<int, Client> m_Clients;

	void ProcessPacket(ENetPacket* packet);
};