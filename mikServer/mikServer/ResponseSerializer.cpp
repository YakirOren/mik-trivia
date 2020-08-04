#include "ResponseSerializer.h"

/*
	Serializes the error response using generatePacket
	Input:
		SignupResponse res: The error response the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(ErrorResponse response)
{
	json data;
	data["message"] = response.message;

	return generatePacket(data, MessageType::SERVER_ERROR);
}

/*
	Serializes the login response using generatePacket
	Input:
		SignupResponse res: The login response the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(LoginResponse response)
{
	json data;
	data["status"] = response.status;

	return generatePacket(data, MessageType::CLIENT_LOGIN);
}

/*
	Serializes the signup response using generatePacket
	Input:
		SignupResponse res: The signup response the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(SignupResponse response)
{
	json data;
	data["status"] = response.status;

	return generatePacket(data, MessageType::CLIENT_SIGNUP);
}

/*
	Serializes the logout response using generatePacket
	Input:
		LogoutResponse res: The logout response the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(LogoutResponse response)
{
	json data;
	data["status"] = response.status;

	return generatePacket(data, MessageType::CLIENT_LOGOUT);
}

/*
	Serializes the GetRoomResponse using generatePacket
	Input:
		GetRoomResponse res: The GetRoomResponse the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(GetRoomsResponse response)
{
	json data;
	data["status"] = response.status;
	//data["rooms"] = response.rooms;

	return generatePacket(data, MessageType::ROOM_RESPONSE);
}

/*
	Serializes the GetPlayersInRoomResponse using generatePacket
	Input:
		GetPlayersInRoomResponse res: The GetPlayersInRoomResponse the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(GetPlayersInRoomResponse response)
{
	json data;
	data["players"] = response.players;

	return generatePacket(data, MessageType::ROOM_PLAYERS_RESPONSE);
}

/*
	Serializes the JoinRoomResponse using generatePacket
	Input:
		JoinRoomResponse res: The JoinRoomResponse the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(JoinRoomResponse response)
{
	json data;
	data["status"] = response.status;

	return generatePacket(data, MessageType::ROOM_LOGIN);
}

/*
	Serializes the CreateRoomResponse using generatePacket
	Input:
		CreateRoomResponse res: The CreateRoomResponse the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(CreateRoomResponse response)
{
	json data;
	data["status"] = response.status;
	data["roomId"] = response.roomId;

	std::cout << "Data Serialized" << std::endl;

	return generatePacket(data, MessageType::ROOM_CREATE);
}

/*
	Serializes the GetStatisticsResponse using generatePacket
	Input:
		GetStatisticsResponse res: The GetStatisticsResponse the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(GetStatisticsResponse response)
{
	json data;
	data["status"] = response.status;
	data["statistics"] = response.statistics;

	return generatePacket(data, MessageType::STATISTICS);
}

/*
	Generates the response that will be retured to the user.
	Input:
		json data: The data that we wish to send to the user.
		MessageType type: The type of the message (CLIENT_SIGNUP, CLIENT_LOGIN ect...).
	Output:
		a vector of unsigned char containing the response to the user.
*/
std::vector<unsigned char> ResponseSerializer::generatePacket(json data, MessageType type)
{
	int bytes = 0;
	int messageSize = data.dump().size();

	std::cout << messageSize << std::endl;

	unsigned char* sizeAsBytes = Helper::intToByte(messageSize);

	printf("%d %d %d %d \n", sizeAsBytes[0], sizeAsBytes[1], sizeAsBytes[2], sizeAsBytes[3]);

	std::vector<unsigned char> packet;

	packet.push_back((unsigned char)type);

	for (int i = 0; i < 4; i++)
	{
		packet.push_back(sizeAsBytes[i]);
	}

	for (int i = 0; i < messageSize; i++)
	{
		packet.push_back(data.dump().c_str()[i]);
	}

	return packet;
}

