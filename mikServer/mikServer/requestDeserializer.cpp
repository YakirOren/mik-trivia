#include "requestDeserializer.h"

/*
	This function deserializes the data from the client from BSON to a LoginRequest.
	The data from the client is sorted like so:

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
	std::string dataAsString = "", convertedData = "";
	
	dataAsString = Helper::vectorToString(data);
	convertedData = Helper::binaryToString(dataAsString);
	
	std::cout << "Data From Client: " << convertedData << std::endl;
	
	
	return LoginRequest();
}

/*
	This function deserializes the data from the client from BSON to a SignupRequest.
	The data from the client is sorted like so:

	[BYTE]  [4 BYTES] [REST]
	MsgCode DataSize  Data

	Input: 
		data (std::vector<unsigned int>): The data from the client ( saved as a vector of unsigned int )
	Output: 
		SignupRequest (struct): The request from the user after being deserialized.		
*/
SignupRequest requestDeserializer::deserializeSignupRequest(std::vector<unsigned char> data)
{
	return SignupRequest();
}
