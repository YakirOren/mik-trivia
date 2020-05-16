#pragma once
#include <WinSock2.h>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "Helper.h"
#include <thread>
#include <map>
#include<set>

class Communicator
{
private:
	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void accept();
	void handleNewClient(SOCKET clientSocket);
	void removeClient(SOCKET clientSocket);
	void startHandleRequests();
	void recieveData(SOCKET clientSocket, std::vector<unsigned char>& buffer, unsigned int size);

public:
	void bindAndListen();
	Communicator();
	~Communicator();
};

