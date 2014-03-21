#include <iostream>
#include <enet/enet.h>
#include "Server.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if (!enet_initialize())
		cout << "Error initializing Enet library" << endl;
	
	Server *server = new Server(1234);

	server->Run();

	delete server;

	enet_deinitialize();

	return 0;
}