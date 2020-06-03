#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	LoginRequestHandler createLoginHandler();
	LoginManager& getLoginManager();

private:
	LoginManager* _loginManager;
	IDatabase* _database;
};

