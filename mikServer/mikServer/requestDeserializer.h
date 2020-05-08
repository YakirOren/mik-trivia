#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Helper.h"

#define START_OF_DATA 5

class requestDeserializer
{
public:
	static struct LoginRequest deserializeLoginRequest(unsigned char* data);
	static struct SignupRequest deserializeSignupRequest(unsigned char* data);
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


