#pragma once
#include <WinSock2.h>
#include <iostream>
#include <ctime>
#include <vector>
#include "ResponseSerializer.h"
#include "requestDeserializer.h"

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(struct RequestInfo request) = 0;
	virtual struct RequestResult handleRequest(struct RequestInfo request) = 0;
};

struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler = {};
};

struct RequestInfo
{
	int id = 0;
	std::time_t recievalTime = 0;
	std::vector<unsigned char> buffer;
};
