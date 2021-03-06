#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <mutex>

class RequestHandlerFactory;
class MenuRequestHandler;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(IDatabase* database);
	~LoginRequestHandler();
	virtual bool isRequestRelevant(struct RequestInfo request);
	virtual struct RequestResult handleRequest(struct RequestInfo request);
private:
	RequestHandlerFactory *_handlerFactory;
	RequestResult login(LoginRequest request);
	RequestResult signup(SignupRequest request);
};

