#include "ResponseSerializer.h"

std::string ResponseSerializer::serializeResponse(ErrorResponse res)
{
	return to_bin(res.message);
}

std::string ResponseSerializer::serializeResponse(LoginResponse res)
{
	return to_bin(std::to_string(res.status));
}

std::string ResponseSerializer::serializeResponse(SignupResponse res)
{
	return to_bin(std::to_string(res.status));
}


std::string ResponseSerializer::to_bin(std::string str){
	
	std::string binaryString = "";
	for (char& _char : str) {
		binaryString += std::bitset<8>(_char).to_string();
	}

	return binaryString;
}
