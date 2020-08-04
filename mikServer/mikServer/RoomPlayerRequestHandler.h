#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class RequestHandlerFactory;
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;

class RoomPlayerRequestHandler : public IRequestHandler
{
public:
	RoomPlayerRequestHandler(Room* room, LoggedUser* loggedUser, RequestHandlerFactory* handlerFactory);

	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);


private:
	Room* m_room;
	LoggedUser* m_user;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult leaveRoom(LeaveRoomRequest request);
	RequestResult getRoomState(GetRoomStateRequest request);

};