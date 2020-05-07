#include "ResponseSerializer.h"


std::string ResponseSerializer::serializeResponse(ErrorResponse res)
{
	return to_bin(SERVER_ERROR+ " {\"message:\":\""+ res.message +"\"}");
}

std::string ResponseSerializer::serializeResponse(LoginResponse res)
{
	return to_bin(std::to_string(CLIENT_LOGIN) + " {\"status\":" + std::to_string(res.status) + "}");

}

std::string ResponseSerializer::serializeResponse(SignupResponse res)
{
	return to_bin(std::to_string(CLIENT_SIGNUP) + " {\"status\":" + std::to_string(res.status) + "}");
}


std::string ResponseSerializer::to_bin(std::string str){
	
	std::string binary;
	for (char& _char : str) {
		 binary += (std::bitset<8>(_char).to_string()) + " ";
	}

	return binary;
}
