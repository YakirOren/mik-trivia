#include "Room.h"

Room::Room(unsigned int id, std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout)
{
	m_metadata.id = id;
	m_metadata.isActive = 1;
	m_metadata.maxPlayers = maxUsers;
	m_metadata.name = roomName;
	m_metadata.timePerQuestion = answerTimeout;
}

Room::~Room()
{
}

/*
	Adds a user to the room
*/
bool Room::addUser(LoggedUser user)
{
	bool hasAdded = false;
	if (m_users.size() < MAX_PLAYERS)
	{
		m_users.push_back(user);
		hasAdded = true;
	}
	return hasAdded;
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
