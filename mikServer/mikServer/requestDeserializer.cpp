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
LoginRequest requestDeserializer::deserializeLoginRequest(unsigned char* data)
{
	LoginRequest loginRequest;
	nlohmann::json json;

	std::string dataAsAstring(reinterpret_cast<char*>(data));

	std::cout << "Data: " << dataAsAstring << "\n";

	dataAsAstring = dataAsAstring.substr(START_OF_DATA);

	std::cout << "Data: " << dataAsAstring << "\n";

	json = nlohmann::json::parse(dataAsAstring);

	loginRequest = {
		loginRequest.password = json["password"].get<std::string>(),
		loginRequest.username = json["username"].get<std::string>()
	};
	
	//dataAsString = Helper::vectorToString(data);
	//convertedData = Helper::binaryToString(dataAsString);
	
	//std::cout << "Data From Client: " << convertedData << std::endl;
	
	
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
SignupRequest requestDeserializer::deserializeSignupRequest(unsigned char* data)
{
	SignupRequest signupRequest;
	nlohmann::json json;

	std::string dataAsAstring(reinterpret_cast<char*>(data));

	std::cout << "Data: " << dataAsAstring << "\n";

	dataAsAstring = dataAsAstring.substr(START_OF_DATA);

	std::cout << "Data: " << dataAsAstring << "\n";

	json = nlohmann::json::parse(dataAsAstring);

	signupRequest = {
		json["username"].get<std::string>(),
		json["password"].get<std::string>(),
		json["email"].get<std::string>()
	};

	return signupRequest;
}
