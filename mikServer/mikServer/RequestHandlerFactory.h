#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomPlayerRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "Room.h"
#include "LoggedUser.h"
#include "IDatabase.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomPlayerRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginHandler();
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler(LoggedUser usr);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

	RoomPlayerRequestHandler* createRoomPlayerRequestHandler(Room* room, LoggedUser* loggedUser);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room* room, LoggedUser* loggedUser);

private:
	LoginManager* m_loginManager;
	IDatabase* m_database;
	RoomManager* m_roomManager;
	StatisticsManager* m_StatisticsManager;
};

