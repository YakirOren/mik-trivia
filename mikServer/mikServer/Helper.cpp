#include "Helper.h"
#include <winsock.h>
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
	return (unsigned char)s[0];
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
int Helper::getMessageLen(SOCKET sc)
{
	char* buffer = getPartFromSocket(sc, 4, 0);

	int a = byteToInt(buffer);

	return a;
}


std::string Helper::vectorToString(std::vector<unsigned char> buffer)
{
	std::string bufferAsString(buffer.begin(), buffer.end());
	//std::cout << "vector as string: " << bufferAsString << std::endl;
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

void Helper::sendData(SOCKET sc, const char* message, int length)
{
	if (send(sc, (char*)message, length, 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

void Helper::sendData(SOCKET sc, std::vector<unsigned char>& data, int length)
{
	std::cout << "Data Sent" << std::endl;
	const char* temp = reinterpret_cast<const char*>(data.data());
	if (send(sc, temp, length, 0) == SOCKET_ERROR)
	{
		throw std::exception("Error while sending message to client, Socket error - " + WSAGetLastError());
	}
}

unsigned char(&Helper::to_array(std::string const& str))[]
{
	static thread_local std::vector<unsigned char> result;
	result.assign(str.data(), str.data() + str.length() + 1);
	return reinterpret_cast<unsigned char(&)[]>(*result.data());
}

int Helper::byteToInt(char* buffer)
{
	int number = int((unsigned char)(buffer[0]) << 24 |
		(unsigned char)(buffer[1]) << 16 |
		(unsigned char)(buffer[2]) << 8 |
		(unsigned char)(buffer[3]));

	return number;
}

unsigned char* Helper::intToByte(const int& number) 
{
	unsigned char* byte = new unsigned char[4];

	byte[0] = (number >> 24) & 0xFF;
	byte[1] = (number >> 16) & 0xFF;
	byte[2] = (number >> 8) & 0xFF;
	byte[3] = number & 0xFF;

	return byte;
}

int Helper::getMessageLength(std::vector<unsigned char> buffer)
{
	return (int)(buffer[3] << 24 | buffer[2] << 16 | buffer[1] << 8 | buffer[0]);
}

int Helper::getNumberOfRooms(std::vector<RoomData> data)
{
	int counter = 0;
	for (std::vector<RoomData>::iterator i; i != data.end(); i++)
	{
		counter++;
	}
	return counter;
}

