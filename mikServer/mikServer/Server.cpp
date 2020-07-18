#include "Server.h"
#include <exception>
#include <iostream>
#include <string>

Server::Server() : _database(new sqlDatabase()), m_communicator(new Communicator(_database, _handlerFactory)), _handlerFactory(new RequestHandlerFactory(_database))
{
}

Server::~Server()
{
	delete _database;
	delete m_communicator;
}

void Server::run()
{
	std::thread t_connector(&Communicator::bindAndListen, new Communicator(_database, _handlerFactory));
	t_connector.detach();
	
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
}


