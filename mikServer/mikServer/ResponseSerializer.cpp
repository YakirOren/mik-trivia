#include "ResponseSerializer.h"


std::string ResponseSerializer::serializeResponse(ErrorResponse res)
{
	json data;
	data["message"] = res.message;

	return to_data(data, MessageType::SERVER_ERROR);

}

std::string ResponseSerializer::serializeResponse(LoginResponse res)
{
	json data;
	data["status"] = res.status;

	return to_data(data, MessageType::CLIENT_LOGIN);


}

std::string ResponseSerializer::serializeResponse(SignupResponse res)
{
	json data;
	data["status"] = res.status;

	return to_data(data, MessageType::CLIENT_SIGNUP);

}


std::string ResponseSerializer::to_data(json data, MessageType type){
	
	int bytes = 0;
	int msgSize = data.dump().size();
	

	if (msgSize < 0x10000)
	{
		if (msgSize < 0x100)
		{
			bytes = 1;
		}
		else
		{
			bytes = 2;
		}
	}
	else
	{
		if (msgSize < 0x1000000)
		{
			bytes = 3;

		}
		else
		{
			bytes = 4;
		}

	}


	std::string str = {'\0','\0','\0','\0'};

	char currChar = '\0';

	for (int i = 0; i <= bytes; i++)
	{
		currChar = msgSize >> i * 8;
		str[3 - i] = currChar; 

	}

	std::string returnStr = (char)(type) + str + data.dump();
	
	return returnStr;
	

}

