#include "RequestHandlerFactory.h"

/*
	Constructor
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : _loginManager(new LoginManager(database)), _database(database)
{

}

/*
	Destructor
*/
RequestHandlerFactory::~RequestHandlerFactory()
{

}

/*
	Creates a new LoginRequestHandler object
	Input:
		None
	Output:
		a new LoginRequestHandler object
*/
LoginRequestHandler RequestHandlerFactory::createLoginHandler()
{
	return LoginRequestHandler(_database);
}

/*
	Returns the login manager
	Input:
		None
	Output:
		Pointer to the login manager
*/
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return *_loginManager;
}
