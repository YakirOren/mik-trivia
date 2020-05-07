#pragma once
#include "IRequestHandler.h"


class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(struct RequestInfo request);
	virtual struct RequestResult handleRequest(struct RequestInfo request);
private:
	// No Private Variables/Functions In Version 1.0.2

};

