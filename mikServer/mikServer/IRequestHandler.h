#pragma once
#include <WinSock2.h>
#include <iostream>
#include <ctime>
#include <vector>
#include "ResponseSerializer.h"
//#include "helper.h"

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(struct RequestInfo request) = 0;
	virtual struct RequestResult handleRequest(struct RequestInfo request) = 0;
};

struct RequestResult
{
	unsigned char* response;
	IRequestHandler* newHandler;
};

struct RequestInfo
{
	int id;
	std::time_t recievalTime;
	unsigned char* buffer;
};
