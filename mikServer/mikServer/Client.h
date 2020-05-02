#pragma once
#include <string>
#include <WinSock2.h>

class Client
{
public:
	Client(SOCKET client_socket, std::string name, int name_len);
	~Client();


	std::string name;
	int name_len;

	SOCKET client_socket;


	std::string toString();

	void initName(std::string name, int name_len);



};

