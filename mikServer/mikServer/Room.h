#pragma once
#include "LoggedUser.h"
#include <vector>

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int timePerQuestion;
	unsigned int isActive;

}typedef RoomData;


class Room
{
public:
	Room(unsigned int id, std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout);
	~Room();
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<LoggedUser> getAllUsers();
	RoomData getRoomData();


private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

};