#pragma once
#include "json.hpp"
#include <bitset>
#include <string>
#include <iostream>
#include "Helper.h"

using json = nlohmann::json;

struct ErrorResponse
{
	std::string message;

};

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

class ResponseSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse res);
	static std::vector<unsigned char> serializeResponse(LoginResponse res);
	static std::vector<unsigned char> serializeResponse(SignupResponse res);
		   
private:   
	static std::vector<unsigned char> generatePacket(json data, MessageType type);
};

