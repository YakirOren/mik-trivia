#include "ResponseSerializer.h"


unsigned char* ResponseSerializer::serializeResponse(ErrorResponse res)
{
	json data;
	data["message"] = res.message;

	return to_data(data, MessageType::SERVER_ERROR);

}

unsigned char* ResponseSerializer::serializeResponse(LoginResponse res)
{
	json data;
	data["status"] = res.status;

	return to_data(data, MessageType::CLIENT_LOGIN);


}

unsigned char* ResponseSerializer::serializeResponse(SignupResponse res)
{
	json data;
	data["status"] = res.status;

	return to_data(data, MessageType::CLIENT_SIGNUP);

}


unsigned char* ResponseSerializer::to_data(json data, MessageType type){
	

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


	std::string str = { 0 };

	char currChar = '\0';

	for (int i = 0; i <= bytes; i++)
	{
		currChar - msgSize >> i * 8;
		str[3 - i] = currChar;

	}

	std::string returnStr = (char)(type) + str + data.dump();

	return to_array(str);


}




unsigned char(&ResponseSerializer::to_array(std::string const& str))[]
{
	static thread_local std::vector<unsigned char> result;
	result.assign(str.data(), str.data() + str.length() + 1);
	return reinterpret_cast<unsigned char(&)[]>(*result.data());
}
