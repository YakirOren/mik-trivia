#pragma once
#include <WinSock2.h>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include <thread>
#include <map>
#include <mutex>
#include <set>

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
	Communicator(IDatabase* database, RequestHandlerFactory* handerFactory);
	~Communicator();
	RequestHandlerFactory* _handlerFactory;
	IDatabase* _database;
};

