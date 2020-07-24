#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>

int main()
{
	std::cout << "Press any key to close the server:" << std::endl;
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		myServer.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	
	return 0;
}