#pragma once
#include "LoggedUser.h"
#include <vector>
#include "json.hpp"

using json = nlohmann::json;


struct roomData
{
	unsigned int id = 0;
	std::string name = "";
	unsigned int maxPlayers = 4;
	unsigned int timePerQuestion = 60;
	unsigned int isActive = 0;

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
