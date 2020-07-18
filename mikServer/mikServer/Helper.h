#pragma once

#include <vector>
#include <string>
#include <bitset>
#include <WinSock2.h>

enum MessageType
{
	CLIENT_LOGIN = 200,
	CLIENT_SIGNUP = 204,
	SERVER_ERROR = 500,
	CLIENT_LOGOUT = 201,
	ROOM_RESPONSE = 300,
	ROOM_PLAYERS_RESPONSE = 301,
	ROOM_LOGIN = 302,
	ROOM_CREATE = 303,
	ROOM_PLAYERS = 304,
	ROOMS = 305,
	STATISTICS = 400,
};

class Helper
{
public:
	static int getMessageTypeCode(SOCKET sc);
	static std::string getStringPartFromSocket(SOCKET sc, int bytesNum);
	static std::string vectorToString(std::vector<unsigned char> buffer);
	static std::string binaryToString(std::string binaryString);
	static void sendData(SOCKET sc, std::string message);
	static void sendData(SOCKET sc, unsigned char* message);
	static unsigned char(&to_array(std::string const& str))[];
	static int getMessageLen(SOCKET sc);
	static int byteToInt(char* buffer);
	static unsigned char* intToByte(const int& number);
	static int getMessageLength(std::vector<unsigned char> buffer);

private:
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);

};

