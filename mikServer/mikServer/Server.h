#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include "Helper.h"
#include <thread>
#include <vector>
#include "Client.h"
#include <mutex>


class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:
	
	void removeClient(SOCKET clientSocket);
	std::string getAll_usernames();
	void accept();
	void clientHandler(SOCKET clientSocket);
	bool exist(const std::string& name);
	std::vector<Client> connected_clients;
	SOCKET _serverSocket;
};

