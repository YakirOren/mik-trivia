#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <string>
#include <vector>

#define SCORE_RIGHT_ANSWER 100
#define NUMBER_OF_WRONG_ANSWERS 3

static std::vector<std::string> dataHolder;
int callBack(void* data, int argc, char** argv, char** azColName);

class sqlDatabase :
	public IDatabase
{
public:
	sqlDatabase();
	virtual ~sqlDatabase();

	bool doesUserExists(std::string name) override;
	bool doesUserExists(std::string name, std::string password) override;
	void createUser(std::string name, std::string password, std::string email) override;

	bool isValidPassword(std::string password) override;
	
	bool open();
	void close();

	std::vector<std::string> GetStatistics(std::string username);

private:
	void updateScore(std::string username, unsigned int timeToAnswer, unsigned int timePerQuestion);
	int calculateScore(std::string username, unsigned int timeToAnswer, unsigned int timePerQuestion);
	std::string dbName;
	sqlite3* db;

	float getPlayerAvarageAnswerTime(std::string username);
	int getNumOfCorrectAnswers(std::string username);
	int getNumOfTotalAnswers(std::string username);
	int getNumOfPlayerGames(std::string username);

	int execute(std::string sql, int (*callback)(void*, int, char**, char**), void*, char** errmsg);
	int execute(std::string sql);

	void selectBy(std::string source, std::string condition, std::string request, sqlite3* db);

	void updateBy(std::string source, std::string condition, std::string column, std::string value, sqlite3* db);

	// init functions.
	static int int_callback(void* data, int argc, char** argv, char** azColName);

};

