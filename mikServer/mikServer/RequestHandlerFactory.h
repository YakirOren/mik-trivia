#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "IDatabase.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	LoginRequestHandler createLoginHandler();
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler(LoggedUser usr);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();


private:
	LoginManager* m_loginManager;
	IDatabase* m_database;
	RoomManager* m_roomManager;
	StatisticsManager* m_StatisticsManager;
};

