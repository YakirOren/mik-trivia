#pragma once

#include <vector>
#include <string>
#include <bitset>
#include <WinSock2.h>


//enum MessageType : byte
//{
//	MT_CLIENT_LOG_IN = 200,
//	MT_CLIENT_UPDATE = 204,
//	MT_CLIENT_FINISH = 207,
//	MT_CLIENT_EXIT = 208,
//	MT_SERVER_UPDATE = 101,
//};


enum MessageType
{
	CLIENT_LOGIN = 200,
	CLIENT_SIGNUP = 204,
	SERVER_ERROR = 500

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

private:
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);

};

