#pragma once

#include <WinSock2.h>
#include "Helper.h"
#include <thread>
#include "Communicator.h"



class Server
{
private:
	Communicator* m_communicator;
	IDatabase* _database;
	RequestHandlerFactory* _handlerFactory;
	
public:
	Server();
	~Server();
	void run();

};

