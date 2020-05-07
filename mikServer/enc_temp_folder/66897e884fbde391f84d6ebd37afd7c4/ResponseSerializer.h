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
	static std::string serializeResponse(ErrorResponse res);
	static std::string serializeResponse(LoginResponse res);
	static std::string serializeResponse(SignupResponse res);
	static std::string to_bin(std::string str);


};

