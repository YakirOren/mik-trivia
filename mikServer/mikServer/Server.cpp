#include "Server.h"
#include <exception>
#include <iostream>
#include <string>

Server::Server()
{
	m_communicator = new Communicator();
}

Server::~Server()
{
	delete m_communicator;
}

void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, m_communicator);
	
	
	////std::cin();
	int userInput = 1;
	while (userInput != 0)
	{
		std::cin >> userInput;

		//if (std::cin.fail())
		//{
		//	std::cin.clear();
		//	// discard 'bad' character(s)
		//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//}
		//else 
		//{
		//	switch (userInput)
		//	{

		//	default:
		//		break;
		//	}
		//	
		//}

	}
	t_connector.detach();


}


