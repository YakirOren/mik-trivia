#pragma once

#include <vector>
#include <string>
#include <bitset>
#include <WinSock2.h>
#include "RoomManager.h"

enum MessageType
{
	CLIENT_LOGIN = 200,
	CLIENT_SIGNUP = 204,
	SERVER_ERROR = 50,
	MAX_USERS_ERROR = 51,
	CLIENT_LOGOUT = 201,
	ROOM_RESPONSE = 100,
	ROOM_PLAYERS_RESPONSE = 101,
	ROOM_LOGIN = 102,
	ROOM_LEAVE = 109,
	ROOM_CREATE = 103,
	ROOM_PLAYERS = 104,
	ROOM_STATE = 106,
	ROOM_START = 107,
	ROOM_CLOSE = 108,
	ROOMS = 105,
	STATISTICS = 40,
};

class Helper
{
public:
	static int getMessageTypeCode(SOCKET sc);
	static std::string getStringPartFromSocket(SOCKET sc, int bytesNum);
	static std::string vectorToString(std::vector<unsigned char> buffer);
	static std::string binaryToString(std::string binaryString);
	static void sendData(SOCKET sc, std::string message);
	static void sendData(SOCKET sc, const char* message, int length);
	static void sendData(SOCKET sc, std::vector<unsigned char>& data, int length);
	static unsigned char(&to_array(std::string const& str))[];
	static int getMessageLen(SOCKET sc);
	static int byteToInt(char* buffer);
	static unsigned char* intToByte(const int& number);
	static int getMessageLength(std::vector<unsigned char> buffer);
	static int getNumberOfRooms(std::vector<RoomData> data);

private:
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);

};

