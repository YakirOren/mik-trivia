#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(IDatabase* database);
	~LoginRequestHandler();
	virtual bool isRequestRelevant(struct RequestInfo request);
	virtual struct RequestResult handleRequest(struct RequestInfo request);
private:
	LoginManager _loginManager;
	RequestHandlerFactory _handlerFactory;
	RequestResult login(RequestInfo request);
	RequestResult signup(RequestInfo request);
};

