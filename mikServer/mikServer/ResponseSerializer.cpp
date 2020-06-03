#include "ResponseSerializer.h"

/*
	Serializes the error response using generatePacket
	Input:
		SignupResponse res: The error response the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(ErrorResponse res)
{
	json data;
	data["message"] = res.message;

	return generatePacket(data, MessageType::SERVER_ERROR);
}

/*
	Serializes the login response using generatePacket
	Input:
		SignupResponse res: The login response the function serializes
	Output:
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(LoginResponse res)
{
	json data;
	data["status"] = res.status;

	return generatePacket(data, MessageType::CLIENT_LOGIN);
}

/*
	Serializes the signup response using generatePacket
	Input: 
		SignupResponse res: The signup response the function serializes
	Output: 
		a vector of unsigned char containing the serialized response
*/
std::vector<unsigned char> ResponseSerializer::serializeResponse(SignupResponse res)
{
	json data;
	data["status"] = res.status;

	return generatePacket(data, MessageType::CLIENT_SIGNUP);
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

