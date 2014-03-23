#include <iostream>
#include <enet/enet.h>
#include "Server.h"

using namespace std;

int main(int argc, char const *argv[])
{
	int error = 0;

	if ((error = enet_initialize()) != 0)
	{
		cout << "Error initializing Enet library, Error code: " << error << endl;
	}
		
	
	Server* server = new Server(1234);

	server->Run();

	delete server;

	enet_deinitialize();

	return 0;
}