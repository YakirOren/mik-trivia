#include "RoomPlayerRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomPlayerRequestHandler::RoomPlayerRequestHandler(Room* room, LoggedUser* loggedUser, RequestHandlerFactory* handlerFactory)
{
	m_room = room;
	m_user = loggedUser;
	m_handlerFactory = handlerFactory;
}

/*
	Checks if the request is relevant
	Input:
		requestInfo request: the request we check
	Output:
		True if the request is relevent, false otherwise
*/
bool RoomPlayerRequestHandler::isRequestRelevant(RequestInfo request)
{
	bool flag = false;
	if (request.id == ROOM_LEAVE || request.id == ROOM_STATE)
	{
		flag = true;
	}
	return flag;
}

/*
	Handles the request by passing it to the correct function according to its id, then returns the result of the request.
	Input:
		RequestInfo requestInfo : The request info
	Output :
		The result of passing the request to the corresponding function.
*/
RequestResult RoomPlayerRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult result = { std::vector<unsigned char>(), nullptr };
	GetRoomStateRequest stateRequest = { 0 };
	LeaveRoomRequest leaveRequest = { 0 };

	if (isRequestRelevant(request))
	{
		switch (request.id)
		{
		case ROOM_LEAVE:
			leaveRequest = requestDeserializer::deserializeLeaveRoomRequest(request.buffer);
			result = leaveRoom(leaveRequest);
			break;

		case ROOM_STATE:
			stateRequest = requestDeserializer::deserializeGetRoomStateRequest(request.buffer);
			result = getRoomState(stateRequest);
			break;

		default:
			result.response = ResponseSerializer::serializeResponse(ErrorResponse{ "Request Doesn't Exist" });
			break;
		}
	}
	else
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ "Request Doesn't Exist" });
	}

	return result;
}

/*
	Returns the result of leaveRoom query
	Input:
		None
	Output:
		RequestResult: The result of executing the leaveRoom query
*/
RequestResult RoomPlayerRequestHandler::leaveRoom(LeaveRoomRequest request)
{
	RequestResult result;
	LeaveRoomResponse response = { 1 };

	try
	{
		m_room->removeUser(*m_user);
		result.response = ResponseSerializer::serializeResponse(response);
		result.newHandler = m_handlerFactory->createMenuRequestHandler(*m_user);
	}
	catch (std::exception e)
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return result;
}

/*
	Returns the result of getRoomState query
	Input:
		None
	Output:
		RequestResult: The result of executing the getRoomState query
*/
RequestResult RoomPlayerRequestHandler::getRoomState(GetRoomStateRequest request)
{
	RequestResult result;
	GetRoomStateResponse response = { 0 };

	std::vector<std::string> players;

	// Recieving all of the users that are currently waiting in the room
	for (LoggedUser user : m_room->getAllUsers())
	{
		players.push_back(user.getUsername());
	}

	response = { 1, m_room->getRoomData().isActive, players, m_room->getRoomData().maxPlayers, m_room->getRoomData().timePerQuestion };

	try
	{
		result.response = ResponseSerializer::serializeResponse(response);
		result.newHandler = m_handlerFactory->createRoomPlayerRequestHandler(m_room, m_user);
	}
	catch (std::exception e)
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return result;
}
