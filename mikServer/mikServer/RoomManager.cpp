#include "RoomManager.h"

RoomManager::RoomManager(IDatabase* database)
{
	m_database = database;
}

/*
	Creates a new room.
	Input: 
		The neccessery parameters for creating a room:
			name		  - The name of the room.
			maxUsers	  - The maximum amount of users the room can handle.
			questionCount - The amount of question in the trivia.
			answerTimeout - The time for each question.
*/

int RoomManager::createRoom(std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout)
{
	unsigned int id = 0;
	id = (*(--m_rooms.end())).first + 1; //Creating a new ID for the room, the new ID is the last room's ID + 1
	Room newRoom = Room(id, roomName, maxUsers, questionCount, answerTimeout);
	m_rooms.insert(std::pair<unsigned int, Room*>(id, &newRoom));
	return id;
}

/*
	Deletes a room from the game based on it's id
	Input: 
		unsigned int id: The id of the room we want to remove
*/
void RoomManager::deleteRoom(unsigned int id)
{
	m_rooms.erase(id);
}

/*
	Returns the state of the room with the entered id
	Input:
		unsigned int id: The id of the room 
	Output:
		0 if the room isn't active, 1 otherwise.
*/
unsigned int RoomManager::getRoomState(unsigned int id)
{
	if (m_rooms.find(id) == m_rooms.end())
	{
		throw std::exception("Room doesn't exist");
	}
	return ((*m_rooms[id]).getRoomData().isActive);
}

/*
	Returns the data from all of the rooms currently exist.
	Output:
		an std::vector<RoomData> which contains all the data of the rooms.
*/
std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> data;

	for (auto iterator : m_rooms)
	{
		data.push_back((*iterator.second).getRoomData());
	}
	return data;

}

/*
	Returns the room with the entered id.
	Input: 
		unsigned int id: The id of the room we search for
	Output: 
		The room with the corresponding id, if it doesn't exist we throw an exception.
*/
Room& RoomManager::getRoom(unsigned int id)
{
	for (auto iterator = m_rooms.begin(); iterator != m_rooms.end(); iterator++)
	{
		if ((*iterator).first == id)
		{
			return *(*iterator).second;
		}
	}
	throw std::exception("Room doesn't exist");
}
