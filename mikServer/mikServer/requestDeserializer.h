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
	static struct LoginRequest deserializeLoginRequest(std::vector<unsigned char> data);
	static struct SignupRequest deserializeSignupRequest(std::vector<unsigned char> data);

	static struct GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> data);
	static struct JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> data);
	static struct CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> data);

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

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};






