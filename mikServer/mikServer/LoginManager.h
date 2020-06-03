#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "LoggedUser.h"
#include "IDatabase.h"
#include <algorithm>

class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;

public:
	bool signup(std::string name, std::string password, std::string email);
	bool login(std::string name, std::string password);
	bool logout(std::string name);
	LoginManager(IDatabase* database);
	~LoginManager();
};
