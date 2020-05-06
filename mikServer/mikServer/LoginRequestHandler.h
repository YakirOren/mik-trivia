#pragma once
#include "IRequestHandler.h"

enum MessageType
{
	CLIENT_LOGIN = 200,
	CLIENT_SIGNUP = 204
};

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(struct RequestInfo request);
	virtual struct RequestResult handleRequest(struct RequestInfo request);
private:
	// No Private Variables/Functions In Version 1.0.2

};

