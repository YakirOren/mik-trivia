#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser* loggedUser, RequestHandlerFactory* handlerFactory)
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
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request)
{
	bool flag = false;
	if (request.id == ROOM_CLOSE || request.id == ROOM_START || request.id == ROOM_STATE)
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
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result = { std::vector<unsigned char>(), nullptr };
	CloseRoomRequest closeRequest = { 0 };
	GetRoomStateRequest stateRequest = { 0 };
	StartRoomRequest startRequest = { 0 };

	if (isRequestRelevant(requestInfo))
	{
		switch (requestInfo.id)
		{
		case ROOM_CLOSE:
			closeRequest = requestDeserializer::deserializeCloseRoomRequest(requestInfo.buffer);
			result = closeRoom(closeRequest);
			break;

		case ROOM_START:
			startRequest = requestDeserializer::deserializeStartRoomRequest(requestInfo.buffer);
			result = startGame(startRequest);
			break;

		case ROOM_STATE:
			stateRequest = requestDeserializer::deserializeGetRoomStateRequest(requestInfo.buffer);
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
	Returns the result of closeRoom query
	Input:
		None
	Output:
		RequestResult: The result of executing the closeRoom query
*/
RequestResult RoomAdminRequestHandler::closeRoom(CloseRoomRequest request)
{
	RequestResult result;
	CloseRoomResponse closeRoomResponse = { 1 };
	try
	{
		m_handlerFactory->getRoomManager().deleteRoom(request.roomId);
		result.response = ResponseSerializer::serializeResponse(closeRoomResponse);
		result.newHandler = m_handlerFactory->createMenuRequestHandler(*m_user);
	}
	catch (std::exception e)
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return result;
}


/*
	Returns the result of startRoom query
	Input:
		None
	Output:
		RequestResult: The result of executing the startRoom query
*/
RequestResult RoomAdminRequestHandler::startGame(StartRoomRequest request)
{
	RequestResult result;
	StartGameResponse startGameResult = { 1 };

	try
	{
		result.response = ResponseSerializer::serializeResponse(startGameResult);
		//result.newHandler = m_handlerFactory->createRoomAdminRequestHandler(m_room, m_user);
		result.newHandler = m_handlerFactory->createRoomAdminRequestHandler(m_room, m_user);
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
RequestResult RoomAdminRequestHandler::getRoomState(GetRoomStateRequest request)
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
		result.newHandler = m_handlerFactory->createRoomAdminRequestHandler(m_room, m_user);
	}
	catch (std::exception e)
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return result;
}
