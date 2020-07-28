#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class RequestHandlerFactory;
class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;

class RoomAdminRequestHandler : public IRequestHandler
{

public:
	RoomAdminRequestHandler(Room* room, LoggedUser* loggedUser, RequestHandlerFactory* handlderFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);

private:
	Room* m_room;
	LoggedUser* m_user;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult closeRoom(CloseRoomRequest request);
	RequestResult startGame(StartRoomRequest request);
	RequestResult getRoomState(GetRoomStateRequest request);
};