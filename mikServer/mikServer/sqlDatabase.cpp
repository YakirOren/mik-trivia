#include "sqlDatabase.h"
#include <io.h>
#include <iostream>

sqlDatabase::sqlDatabase()
{
	this->dbName = "galleryDB.sqlite";
	int file_exist = _access(this->dbName.c_str(), 0);

	if (!open())
	{
		throw std::exception("Failed to open DB");
	}

	//create a new table if it doesn't exists.
	if (file_exist != 0)
	{
		//execute("CREATE TABLE USERS (ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , NAME TEXT NOT NULL , PASSWORD TEXT NOT NULL , EMAIL TEXT NOT NULL);");
		execute("CREATE TABLE \"USERS\" (\"USERNAME\"	TEXT NOT NULL,\"PASSWORD\"	TEXT NOT NULL,\"EMAIL\"	TEXT NOT NULL,PRIMARY KEY(\"USERNAME\"));"
			"CREATE TABLE \"questions\" (\"data\"	TEXT NOT NULL,\"correct\"	TEXT NOT NULL,\"ans1\"	TEXT NOT NULL,\"ans2\"	TEXT NOT NULL,\"ans3\"	TEXT NOT NULL,\"id\"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT);"
			"CREATE TABLE \"Statistics\" (\"UserName\"	TEXT NOT NULL,\"AvarageAnswerTime\"	REAL NOT NULL,\"CorrectAnswers\"	INTEGER NOT NULL,\"Answers\"	INTEGER NOT NULL,\"Games\"	INTEGER NOT NULL,\"Score\"	INTEGER NOT NULL, PRIMARY KEY(\"USERNAME\"));");
		
	}
}

sqlDatabase::~sqlDatabase()
{
}


/*
this function checks if a user exists in the database by name.
Input:
	name.
Output:
	True/False.
*/
bool sqlDatabase::doesUserExists(std::string name)
{
	std::string sql = "select count(*) from users where name = '" + name + "';";

	int d = 0;
	execute(sql, int_callback, static_cast<void*>(&d), nullptr);

	return d;
	
}

/*
this function checks if a user exists in the database by name and password.
Input:
	name, password
Output:
	True/False.
*/
bool sqlDatabase::doesUserExists(std::string name, std::string password)
{
	std::string sql = "select count(*) from users where name = '" + name + "'"+ "and password = '" + password + "'"+";";

	int d = 0;
	execute(sql, int_callback, static_cast<void*>(&d), nullptr);

	return d;
}

/*
this function creates a new user in the database.
Input:
	name, password, emai.
Output:
	None
*/
void sqlDatabase::createUser(std::string name, std::string password, std::string email)
{
	std::string sql = "insert into users (NAME, PASSWORD, EMAIL) VALUES ('" + name + "' ,'" + password + "', '" + email + "');";
	execute(sql);
	//selectBy("USERS", "USERNAME " "= \"" + name + "\"", "USERNAME", db);
	sql = "insert into statistics (UserName, AvarageAnswerTime, CorrectAnswers, Answers, Games, Score) VALUES ('" + name + "' ,'0,0,0,0,0');";
	execute(sql);
}

/*
this function checks if a given a password string is valid.
Input:
	string password.
Output:
	True/False.
*/
bool sqlDatabase::isValidPassword(std::string password)
{
	return true;
}

/*
this function opens connection to the database. 
Input:
	None
Output:
	True/False if was able to connect to the database.
*/
bool sqlDatabase::open()
{
	int res = sqlite3_open(this->dbName.c_str(), &this->db);

	if (res != SQLITE_OK) {
		this->db = nullptr;
		return false;
	}

	return true;
}

/*
this function closes connection to the database.
Input:
Output:
*/
void sqlDatabase::close()
{
	sqlite3_close(this->db);
	this->db = nullptr;
}

std::vector<std::string> sqlDatabase::GetStatistics(std::string username)
{
	std::vector<std::string> stats;
	//add to the stats vector all the data about every user.
	stats.push_back(username);
	stats.push_back(std::to_string(this->getPlayerAvarageAnswerTime(username)));
	stats.push_back(std::to_string(this->getNumOfCorrectAnswers(username)));
	stats.push_back(std::to_string(this->getNumOfTotalAnswers(username)));
	stats.push_back(std::to_string(this->getNumOfPlayerGames(username)));
	return stats;
}

float sqlDatabase::getPlayerAvarageAnswerTime(std::string username)
{
	float result = 0;
	selectBy("STATISTICS", "USERNAME " "= \"" + username + "\"", "AvarageAnswerTime", db);
	result = stof(dataHolder[0]);
	dataHolder.clear();
	return result;
}

int sqlDatabase::getNumOfCorrectAnswers(std::string username)
{
	int result = 0;
	selectBy("STATISTICS", "USERNAME " "= \"" + username + "\"", "CorrectAnswers", db);
	result = stoi(dataHolder[0]);
	dataHolder.clear();
	return result;
}

int sqlDatabase::getNumOfTotalAnswers(std::string username)
{
	int result = 0;
	selectBy("STATISTICS", "USERNAME " "= \"" + username + "\"", "Answers", db);
	result = stoi(dataHolder[0]);
	dataHolder.clear();
	return result;
}

int sqlDatabase::getNumOfPlayerGames(std::string username)
{
	int result = 0;
	selectBy("STATISTICS", "USERNAME " "= \"" + username + "\"", "Games", db);
	result = stoi(dataHolder[0]);
	dataHolder.clear();
	return result;
}

void sqlDatabase::updateScore(std::string username, unsigned int timeToAnswer, unsigned int timePerQuestion)
{
	int score = calculateScore(username, timeToAnswer, timePerQuestion);
	updateBy("STATISTICS", "USERNAME = \"" + username + "\"", "Score", std::to_string(score), db);
}

int sqlDatabase::calculateScore(std::string username, unsigned int timeToAnswer, unsigned int timePerQuestion)
{
	int newScore = SCORE_RIGHT_ANSWER * timeToAnswer / timePerQuestion;
	selectBy("STATISTICS", "USERNAME = \"" + username + "\"", "Score", db);
	int currentScore = stoi(dataHolder[0]);
	dataHolder.clear();
	//return the sum of the previous score and the new score
	return currentScore + newScore;
}

/*
this function is for genric execute of sql in the database.
*/
int sqlDatabase::execute(std::string sql, int(*callback)(void*, int, char**, char**), void* parm, char** errmsg)
{
	open();
	int ret = sqlite3_exec(this->db, sql.c_str(), callback, parm, nullptr);
	close();

	return ret;
}

/*
this function executes a given sql string.
Input: sql string.
Output:
	the return code from the sqllite3.
*/
int sqlDatabase::execute(std::string sql)
{
	return execute(sql, nullptr, nullptr, nullptr);
}

/*
	Executes a simple select query using the entered values
	Input:
		source: The table from which we want to get the data from
		condition: The conditions for the query
		request: The request itself ( what to search for )
		db: Pointer to the database
	Output: None
*/
void sqlDatabase::selectBy(std::string source, std::string condition, std::string request, sqlite3* db)
{
	char* error = nullptr;
	std::string query;

	if (condition == "")
	{
		query = "SELECT " + request + " FROM " + source + ";";
	}
	else
	{
		query = "SELECT " + request + " FROM " + source + " WHERE " + condition + ";";
	}

	int res = sqlite3_exec(db, query.c_str(), int_callback, nullptr, &error);
	if (sqlite3_errmsg != nullptr)
	{
		std::cout << error << std::endl;
	}
}

/*
	Executes a simple update query using the entered values
	Input:
		source: The table from which we want to get the data from
		condition: The conditions for the query
		column: Which column to update
		value: The new value to insert
		db: Pointer to the database
	Output: None
*/
void sqlDatabase::updateBy(std::string source, std::string condition, std::string column, std::string value, sqlite3* db)
{
	char* error = nullptr;
	std::string sqlQuery = "UPDATE " + source + " SET " + column + " = \"" + value + "\" WHERE " + condition + ";";

	int result = sqlite3_exec(db, sqlQuery.c_str(), nullptr, nullptr, &error);
	if (error != nullptr)
	{
		std::cout << std::string(error) << std::endl;
	}
}

/*
this function is a callback function that returens the type int, can be used for sql strings with count() for example.
Input:
	basic callbacks inputs.
Output:
	int.
*/
int sqlDatabase::int_callback(void* data, int argc, char** argv, char** azColName)
{
	auto dd = reinterpret_cast<int*>(data);

	for (int i = 0; i < argc; i++)
	{
		*dd = atoi(argv[i]);
	}

	return 0;
}

int callBack(void* data, int argc, char** argv, char** azColName)
{
	int i = 0;
	for (i = 0; i < argc; i++)
	{
		dataHolder.push_back(argv[i]);
	}
	return 0;
}
