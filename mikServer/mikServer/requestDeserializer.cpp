#include "requestDeserializer.h"

using namespace nlohmann;

/*
	This function deserializes the data from the client from unsigned char* to a LoginRequest.
	The data from the client is sorted like so:

	Thank you Senpai Yakir

	[BYTE]  [4 BYTES] [REST]
	MsgCode DataSize  Data

	Input:
		data (std::vector<unsigned int>): The data from the client ( saved as a vector of unsigned int )
	Output:
		LoginRequest (struct): The request from the user after being deserialized.
*/
LoginRequest requestDeserializer::deserializeLoginRequest(std::vector<unsigned char> data)
{
	LoginRequest loginRequest;

	std::string dataAsString = Helper::vectorToString(data);

	json parsedData = json::parse(dataAsString);

	loginRequest = {
		parsedData["password"].get<std::string>(),
		parsedData["username"].get<std::string>()
	};

	return loginRequest;
}

/*
	This function deserializes the data from the client from unsigned char* to a SignupRequest.
	The data from the client is sorted like so:

	Thank you Senpai Yakir

	[BYTE]  [4 BYTES] [REST]
	MsgCode DataSize  Data

	Input:
		data (std::vector<unsigned int>): The data from the client ( saved as a vector of unsigned int )
	Output:
		SignupRequest (struct): The request from the user after being deserialized.
*/
SignupRequest requestDeserializer::deserializeSignupRequest(std::vector<unsigned char> data)
{
	SignupRequest signupRequest;

	std::string dataAsString = Helper::vectorToString(data);

	json parsedData = json::parse(dataAsString);

	signupRequest = {
		parsedData["username"].get<std::string>(),
		parsedData["password"].get<std::string>(),
		parsedData["email"].get<std::string>()
	};

	return signupRequest;
}

/*
	This function deserializes the data from the client from std::vector<unsigned char> to a GetPlayersInRoomRequest.
*/
GetPlayersInRoomRequest requestDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> data)
{
	GetPlayersInRoomRequest request;

	std::string dataAsString = Helper::vectorToString(data);

	json parsedData = json::parse(dataAsString);

	request = { parsedData["roomId"].get<unsigned int>() };

	return request;
}

/*
	This function deserializes the data from the client from std::vector<unsigned char> to a JoinRoomRequest.
*/
JoinRoomRequest requestDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> data)
{
	JoinRoomRequest request;

	std::string dataAsString = Helper::vectorToString(data);

	json parsedData = json::parse(dataAsString);

	request = { parsedData["roomId"].get<unsigned int>() };

	return request;
}

/*
	This function deserializes the data from the client from std::vector<unsigned char> to a CreateRoomRequest.
*/
CreateRoomRequest requestDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> data)
{
	CreateRoomRequest request;

	std::string dataAsString = Helper::vectorToString(data);

	json parsedData = json::parse(dataAsString);

	std::cout << dataAsString << std::endl; 

	request = {

			parsedData["roomName"].get<std::string>(),
			parsedData["maxUsers"].get<unsigned int>(),
			parsedData["questionCount"].get<unsigned int>(),
			parsedData["answerTimeout"].get<unsigned int>()
	};

	return request;
}

