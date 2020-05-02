#include "Client.h"

Client::Client(SOCKET client_socket,std::string name,int name_len)
{
	this->name = name;
	this->name_len = name_len;
	this->client_socket = client_socket;

}

Client::~Client()
{
}

/*
this function can be used when we want to send the clients info in a packet
the first 2b will be the name_len and the rest will be the name itself.
*/
std::string Client::toString()
{
	return std::to_string(name_len) + name;
}
