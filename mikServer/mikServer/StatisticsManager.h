#pragma once
#include "sqlDatabase.h"
#include <vector>

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* dataBase);
	~StatisticsManager();
	std::vector<std::string> getStatistics(std::string username);

private:
	IDatabase* m_database;
};
