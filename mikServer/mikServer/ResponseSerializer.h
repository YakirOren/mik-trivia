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
	static unsigned char* serializeResponse(ErrorResponse res);
	static unsigned char* serializeResponse(LoginResponse res);
	static unsigned char* serializeResponse(SignupResponse res);
	
	
private:
	static unsigned char* to_data(json data, MessageType type);

	static unsigned char(&to_array(std::string const& str))[];
};

