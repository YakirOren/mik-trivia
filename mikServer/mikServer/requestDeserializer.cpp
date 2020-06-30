#include "requestDeserializer.h"

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
	nlohmann::json json;

	std::string dataAsString = Helper::vectorToString(data);

	for (auto& i : dataAsString)
	{
		std::cout << i;
	}

	dataAsString = dataAsString.substr(START_OF_DATA);

	std::cout << "Data: " << dataAsString << "\n";

	json = nlohmann::json::parse(dataAsString);

	loginRequest = {
		loginRequest.password = json["password"].get<std::string>(),
		loginRequest.username = json["username"].get<std::string>()
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
	nlohmann::json json;

	std::string dataAsString = Helper::vectorToString(data);

	for (auto& i : dataAsString)
	{
		std::cout << i;
	}

	dataAsString = dataAsString.substr(START_OF_DATA);

	std::cout << "Data: " << dataAsString << "\n";

	json = nlohmann::json::parse(dataAsString);

	signupRequest = {
		json["username"].get<std::string>(),
		json["password"].get<std::string>(),
		json["email"].get<std::string>()
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

	for (auto& i : dataAsString)
	{
		std::cout << i;
	}

	dataAsString = dataAsString.substr(START_OF_DATA);

	std::cout << "Data: " << dataAsString << "\n";

	nlohmann::json json = nlohmann::json::parse(dataAsString);

	request = { json["roomId"].get<unsigned int>() };

	return request;
}

/*
	This function deserializes the data from the client from std::vector<unsigned char> to a JoinRoomRequest.
*/
JoinRoomRequest requestDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> data)
{
	JoinRoomRequest request;
	std::string dataAsString = Helper::vectorToString(data);

	for (auto& i : dataAsString)
	{
		std::cout << i;
	}

	dataAsString = dataAsString.substr(START_OF_DATA);

	std::cout << "Data: " << dataAsString << "\n";

	nlohmann::json json = nlohmann::json::parse(dataAsString);

	request = { json["roomId"].get<unsigned int>() };

	return request;
}

/*
	This function deserializes the data from the client from std::vector<unsigned char> to a CreateRoomRequest.
*/
CreateRoomRequest requestDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> data)
{
	CreateRoomRequest request;
	std::string dataAsString = Helper::vectorToString(data);

	for (auto& i : dataAsString)
	{
		std::cout << i;
	}

	dataAsString = dataAsString.substr(START_OF_DATA);

	std::cout << "Data: " << dataAsString << "\n";

	nlohmann::json json = nlohmann::json::parse(dataAsString);

	request = {

			json["roomName"].get<std::string>(),
			json["maxUsers"].get<unsigned int>(),
			json["questionCount"].get<unsigned int>(),
			json["answerTimeout"].get<unsigned int>()
	};

	return request;
}

