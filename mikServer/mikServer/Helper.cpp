#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int Helper::getMessageTypeCode(SOCKET sc)
{
	char* s = getPartFromSocket(sc, 1);
	std::string msg(s);

	if (msg == "")
		return 0;

	int res = std::atoi(s);
	delete s;
	return  res;
}


// recieve data from socket according byteSize
// returns the data as string
string Helper::getStringPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	string res(s);
	return res;
}


// recieve data from socket according byteSize
// returns the data as string
int Helper::getMessageLen(SOCKET sc, int bytesNum)
{
	char* buffer = getPartFromSocket(sc, bytesNum, 0);

	int a = int((unsigned char)(buffer[0]) << 24 |
		(unsigned char)(buffer[1]) << 16 |
		(unsigned char)(buffer[2]) << 8 |
		(unsigned char)(buffer[3]));

	std::cout << "msg len: " << a << std::endl;

	return a;
}





std::string Helper::vectorToString(std::vector<unsigned char> buffer)
{
	std::string bufferAsString(buffer.begin(), buffer.end());
	std::cout << "vector as string: " << bufferAsString << std::endl;
	return bufferAsString;
}

std::string Helper::binaryToString(std::string binaryString)
{
	std::string buffer = binaryString, data = "";
	std::istringstream stream(buffer);
	std::bitset<8> set;
	while (stream >> set)
	{
		data += (set.to_ulong());
	}
	std::cout << "Binary as string: " << data << std::endl;
	return std::string();
}


// recieve data from socket according byteSize
// this is private function
char* Helper::getPartFromSocket(SOCKET sc, int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

void Helper::sendData(SOCKET sc, std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

void Helper::sendData(SOCKET sc, unsigned char* message)
{
	if (send(sc, (char*)message, strlen((char*)message), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

unsigned char(&Helper::to_array(std::string const& str))[]
{
	static thread_local std::vector<unsigned char> result;
	result.assign(str.data(), str.data() + str.length() + 1);
	return reinterpret_cast<unsigned char(&)[]>(*result.data());
}