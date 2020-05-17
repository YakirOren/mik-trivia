#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <string>

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


private:

	std::string dbName;
	sqlite3* db;

	int execute(std::string sql, int (*callback)(void*, int, char**, char**), void*, char** errmsg);
	int execute(std::string sql);


	// init functions.
	static int int_callback(void* data, int argc, char** argv, char** azColName);

};

