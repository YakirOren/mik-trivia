#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory* handlerFactory) : m_handlerFactory(handlerFactory), m_user(user)
{

}


/*
	Checks if the request is relevant
	Input: 
		requestInfo request: the request we check
	Output: 
		True if the request is relevent, false otherwise
*/
bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	bool flag = false;
	if (request.id == CLIENT_LOGOUT || request.id == ROOM_PLAYERS || request.id == ROOMS || request.id == STATISTICS|| request.id == ROOM_CREATE || request.id == ROOM_LOGIN)
	{
		flag = true;
	}
	return flag;
}



/*
	Handles the request by passing it to the correct function according to its id, then returns the result of the request.
	Input: 
		RequestInfo requestInfo: The request info
	Output: 
		The result of passing the request to the corresponding function.
*/
RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo)
{
	std::vector<unsigned char> buffer;
	RequestResult result = { std::vector<unsigned char>(), nullptr };

	GetPlayersInRoomRequest getPlayersRequest = { 0 };
	JoinRoomRequest request = { 0 };
	CreateRoomRequest createRequest = { "", 0, 0, 0 };
	//result.newHandler = nullptr;

	if (isRequestRelevant(requestInfo))
	{
		switch (requestInfo.id)
		{
			case CLIENT_LOGOUT:
			{
				result = signout();
				break;
			}
			case ROOM_PLAYERS:
			{
				//std::vector<unsigned char> v(requestInfo.buffer, requestInfo.buffer + sizeof(requestInfo.buffer) / sizeof(requestInfo.buffer[0]));
				getPlayersRequest = requestDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);
				result = getPlayersInRoom(getPlayersRequest);
				break;
			}
			case ROOMS:
			{
				result = getRooms();
				break;
			}
			case ROOM_LOGIN:
			{
				//std::vector<unsigned char> v(requestInfo.buffer, requestInfo.buffer + sizeof(requestInfo.buffer) / sizeof(requestInfo.buffer[0]));
				request = requestDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
				result = joinRoom(request);
				break;
			}
			case ROOM_CREATE:
			{
				//std::vector<unsigned char> v(requestInfo.buffer, requestInfo.buffer + sizeof(requestInfo.buffer) / sizeof(requestInfo.buffer[0]));
				std::cout << "Creating Room" << std::endl;
				createRequest = requestDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);
				result = createRoom(createRequest);
				break;
			}
			case STATISTICS:
			{
				result = getStatistics();
				break;
			}
			default:
			{
				result.response = ResponseSerializer::serializeResponse(ErrorResponse{ "Request Doesn't Exist" });
				break;
			}
		}
	}
	else
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ "Request Doesn't Exist" });
	}

	return result;
}

/*
	Returns the result of signout query
	Input:
		None
	Output:
		RequestResult: The result of executing the signout query
*/
RequestResult MenuRequestHandler::signout()
{
	RequestResult request;
	SignupResponse response{ 1 };

	try
	{
		request.response = ResponseSerializer::serializeResponse(response);
		request.newHandler = m_handlerFactory->createMenuRequestHandler(m_user);
	}
	catch (std::exception e)
	{
		request.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return request;
}

/*
	Returns the result of getRooms query
	Input:
		None
	Output:
		RequestResult: The result of executing the getRooms query
*/
RequestResult MenuRequestHandler::getRooms()
{
	RequestResult request;
	GetRoomsResponse response{ 1, std::vector<RoomData>() };
	response.status = 1;
	try
	{
		response.rooms = m_handlerFactory->getRoomManager().getRooms();
		for (auto& i : response.rooms)
		{
			std::vector<LoggedUser> usersInRoom = m_handlerFactory->getRoomManager().getRoom(i.id).getAllUsers();
			/*for (auto iterator = usersInRoom.begin(); iterator != usersInRoom.end(); iterator++)
			{
				i.maxPlayers++;
			}
			std::cout << i.id << i.isActive << i.maxPlayers << i.name << i.timePerQuestion << std::endl;*/
		}
		request.response = ResponseSerializer::serializeResponse(response);
		request.newHandler = m_handlerFactory->createMenuRequestHandler(m_user);
	}
	catch (std::exception e)
	{
		request.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return request;
}

/*
	Returns the result of getPlayersInRoom query
	Input:
		None
	Output:
		RequestResult: The result of executing the getPlayersInRoom query
*/
RequestResult MenuRequestHandler::getPlayersInRoom(GetPlayersInRoomRequest getPLayerReq)
{
	RequestResult request;
	GetPlayersInRoomResponse response{ std::vector<std::string>() };

	try
	{
		std::vector<LoggedUser> usersInRoom = m_handlerFactory->getRoomManager().getRoom(getPLayerReq.roomId).getAllUsers();
		for (auto iterator = usersInRoom.begin(); iterator != usersInRoom.end(); iterator++)
		{
			response.players.push_back((*iterator).getUsername());
		}
		request.response = ResponseSerializer::serializeResponse(response);
		request.newHandler = m_handlerFactory->createMenuRequestHandler(m_user);
	}
	catch (std::exception e)
	{
		request.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return request;
}

/*
	Returns the result of getStatistics query
	Input:
		None
	Output:
		RequestResult: The result of executing the getStatistics query
*/
RequestResult MenuRequestHandler::getStatistics()
{
	RequestResult request;

	try
	{
		request.response = ResponseSerializer::serializeResponse(GetStatisticsResponse{ 1, m_handlerFactory->getStatisticsManager().getStatistics(m_user.getUsername()) });
		request.newHandler = m_handlerFactory->createMenuRequestHandler(m_user);
	}
	catch (std::exception e)
	{
		request.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return request;
}

/*
	Returns the result of joinRoom query
	Input:
		None
	Output:
		RequestResult: The result of executing the joinRoom query
*/
RequestResult MenuRequestHandler::joinRoom(JoinRoomRequest joinRoomReq)
{
	RequestResult request;
	JoinRoomResponse response{ 0 };

	try
	{
		response.status = 1;
		if (m_handlerFactory->getRoomManager().getRoom(joinRoomReq.roomId).addUser(m_user))
		{
			request.response = ResponseSerializer::serializeResponse(response);
			request.newHandler = m_handlerFactory->createMenuRequestHandler(m_user);
		}
		else
		{
			request.response = ResponseSerializer::serializeResponse(MaxUsersError{ "Error: Room Is Already Full!" });
		}
	}
	catch (std::exception e)
	{
		request.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return request;
}

/*
	Returns the result of createRoom query
	Input:
		None
	Output:
		RequestResult: The result of executing the createRoom query
*/
RequestResult MenuRequestHandler::createRoom(CreateRoomRequest createRoomReq)
{
	RequestResult request;
	CreateRoomResponse response{ 0 };

	try
	{
		response.status = 1;
		response.roomId = m_handlerFactory->getRoomManager().createRoom(createRoomReq.roomName, createRoomReq.maxUsers + 1, createRoomReq.questionCount, createRoomReq.answerTimeout);
		std::cout << "Room Created" << std::endl;
		m_handlerFactory->getRoomManager().getRoom(response.roomId).addUser(m_user);
		request.response = ResponseSerializer::serializeResponse(response);
		request.newHandler = m_handlerFactory->createRoomAdminRequestHandler(&m_handlerFactory->getRoomManager().getRoom(response.roomId), &m_user);
	}
	catch (std::exception e)
	{
		request.response = ResponseSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return request;
}
