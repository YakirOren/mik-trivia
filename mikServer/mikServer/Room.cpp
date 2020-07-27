#include "Room.h"

Room::Room(unsigned int id, std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout)
{
}

Room::~Room()
{
}

void RoomData::to_json(json& j, const RoomData& d)
{
	j = json{ {"id", d.id}, {"name", d.name}, {"maxPlayers", d.maxPlayers}, {"timePerQuestion", d.timePerQuestion}, {"isActive", d.isActive} };
}

/*
	Adds a user to the room
*/
void Room::addUser(LoggedUser user)
{
}

/*
	Removes a user from the room
*/
void Room::removeUser(LoggedUser user)
{
	auto iterator = m_users.begin();
	for (auto iterator = m_users.begin(); iterator != m_users.end(); iterator++)
	{
		if ((*iterator).getUsername() == user.getUsername())
		{
			m_users.erase(iterator);
		}
	}

}

/*
	Returns the users that are currently logged into the room
	Output: 
		The vector holding the users that are currently logged into the room
*/
std::vector<LoggedUser> Room::getAllUsers()
{
	return m_users;
}

/*
	Returns the data about a room
	Output: 
		Meta data struct which holds the info about the room:
			id				- The room's id (unique)
			name			- The room's name
			maxPlayers		- Maximum capacity in the room
			timePerQuestion - Time for each question
			isActive		- Is the room active or not
*/
RoomData Room::getRoomData()
{
	return m_metadata;
}
