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

	static struct StartRoomRequest deserializeStartRoomRequest(std::vector<unsigned char> data);
	static struct CloseRoomRequest deserializeCloseRoomRequest(std::vector<unsigned char> data);
	static struct GetRoomStateRequest deserializeGetRoomStateRequest(std::vector<unsigned char> data);
	static struct LeaveRoomRequest deserializeLeaveRoomRequest(std::vector<unsigned char> data);
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
	unsigned int maxUsers = 0;
	unsigned int questionCount = 0;
	unsigned int answerTimeout = 0;
};

struct StartRoomRequest
{
	unsigned int roomId;
};

struct CloseRoomRequest
{
	unsigned int roomId;
};

struct GetRoomStateRequest
{
	unsigned int roomId;
};

struct LeaveRoomRequest
{
	unsigned int roomId;
};






