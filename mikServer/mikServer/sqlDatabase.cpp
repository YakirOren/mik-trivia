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

	if (file_exist == 0)
	{
		execute("CREATE TABLE USERS (ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , NAME TEXT NOT NULL , PASSWORD TEXT NOT NULL , EMAIL TEXT NOT NULL);");

	}



	close();
}

bool sqlDatabase::doesUserExists(int userId)
{
	std::string sql = "select count(*) from users where id = " + std::to_string(userId) + ";";

	int d = 0;
	execute(sql, int_callback, static_cast<void*>(&d), nullptr);

	return d;
	
}

void sqlDatabase::createUser(std::string name, std::string password, std::string email)
{
	std::string sql = "insert into users (NAME, PASSWORD, EMAIL) VALUES ('" + name + "' ,'" + password + "', '" + email + "');";
	execute(sql);

}

bool sqlDatabase::isValidPassword(std::string)
{
	return true;
}

bool sqlDatabase::open()
{
	int res = sqlite3_open(this->dbName.c_str(), &this->db);

	if (res != SQLITE_OK) {
		this->db = nullptr;
		return false;
	}

	return true;
}

void sqlDatabase::close()
{
	sqlite3_close(this->db);
	this->db = nullptr;
}

int sqlDatabase::execute(std::string sql, int(*callback)(void*, int, char**, char**), void* parm, char** errmsg)
{
	open();
	int ret = sqlite3_exec(this->db, sql.c_str(), callback, parm, nullptr);
	close();

	return ret;
}

int sqlDatabase::execute(std::string sql)
{
	return execute(sql, nullptr, nullptr, nullptr);
}

int sqlDatabase::int_callback(void* data, int argc, char** argv, char** azColName)
{
	auto dd = reinterpret_cast<int*>(data);

	for (int i = 0; i < argc; i++)
	{
		*dd = atoi(argv[i]);
	}

	return 0;
}
