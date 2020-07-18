#include "StatisticsManager.h"


StatisticsManager::StatisticsManager(IDatabase* dataBase)
{
	this->m_database = dataBase;
}

StatisticsManager::~StatisticsManager()
{

}

/*
	Calls all of the statistics function from the database class and creates the statisticss struct
	Input: 
		std::string username: the username of the user
	Output:
		the statistics about the player
*/
std::vector<std::string> StatisticsManager::getStatistics(std::string username)
{
	/*std::vector<std::string> statistics;
	statistics.push_back(std::to_string(m_database->getPlayerAvarageAnswerTime(username)));
	statistics.push_back(std::to_string(m_database->getNumOfCorrectAnswers(username)));
	statistics.push_back(std::to_string(m_database->getNumOfTotalAnswers(username)));
	statistics.push_back(std::to_string(m_database->getNumOfPlayerGames(username)));

	return statistics;*/
	return std::vector<std::string>();
}
