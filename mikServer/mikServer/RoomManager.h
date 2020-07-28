#pragma once
#include "Room.h"
#include "LoggedUser.h"
#include "sqlDatabase.h"
#include <vector>
#include <map>

class RoomManager
{
public:
	static RoomManager* getInstance(IDatabase* database);
	int createRoom(std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout);
	void deleteRoom(unsigned int id);
	unsigned int getRoomState(unsigned int id);
	std::vector<RoomData> getRooms();
	Room& getRoom(unsigned int id);
	

private:
	RoomManager(IDatabase* database); 
	static RoomManager* m_instance;
	std::map<unsigned int, Room*> m_rooms;
	IDatabase* m_database;

};
