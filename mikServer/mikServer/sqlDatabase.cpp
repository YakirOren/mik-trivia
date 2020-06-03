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
	if (file_exist == 0)
	{
		execute("CREATE TABLE USERS (ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , NAME TEXT NOT NULL , PASSWORD TEXT NOT NULL , EMAIL TEXT NOT NULL);");

	}

	close();
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
