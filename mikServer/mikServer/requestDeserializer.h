#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Helper.h"


class requestDeserializer
{
public:
	static struct LoginRequest deserializeLoginRequest(std::vector<unsigned char> data);
	static struct SignupRequest deserializeSignupRequest(std::vector<unsigned char> data);
};

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};


