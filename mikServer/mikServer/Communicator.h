#pragma once
#include <WinSock2.h>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include <thread>
#include <map>
#include<set>

class Communicator
{
private:
	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	
	void accept();
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);


	void removeClient(SOCKET clientSocket);


public:
	void startHandleRequests();
	Communicator();
	~Communicator();
};

