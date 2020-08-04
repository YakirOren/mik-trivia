#pragma once
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "RoomAdminRequestHandler.h"

class RequestHandlerFactory;
class LoginRequestHandler;
class RoomAdminRequestHandler;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RequestHandlerFactory* handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo reqInfo);


private:
	LoggedUser m_user;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult signout();
	RequestResult getRooms();
	RequestResult getPlayersInRoom(GetPlayersInRoomRequest getPLayerReq);
	RequestResult getStatistics();
	RequestResult joinRoom(JoinRoomRequest joinRoomReq);
	RequestResult createRoom(CreateRoomRequest createRoomReq);

};
