#pragma once
#include "json.hpp"
#include <bitset>
#include <string>
#include <iostream>
#include "Helper.h"
#include "Room.h"

using json = nlohmann::json;

struct ErrorResponse
{
	std::string message;
};

struct MaxUsersError
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

struct LogoutResponse
{
	unsigned int status;

};

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;

};

struct GetStatisticsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;

};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
	unsigned int roomId;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	unsigned int HasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;

};

class ResponseSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse response);
	static std::vector<unsigned char> serializeResponse(LoginResponse response);
	static std::vector<unsigned char> serializeResponse(SignupResponse response);
	static std::vector<unsigned char> serializeResponse(LogoutResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse response);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse response);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse response);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse response);
	static std::vector<unsigned char> serializeResponse(GetStatisticsResponse response);
	static std::vector<unsigned char> serializeResponse(MaxUsersError response);
	static std::vector<unsigned char> serializeResponse(LeaveRoomResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomStateResponse response);
	static std::vector<unsigned char> serializeResponse(CloseRoomResponse response);
	static std::vector<unsigned char> serializeResponse(StartGameResponse response);
private:
	static std::vector<unsigned char> generatePacket(json data, MessageType type);
};

