#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "LoggedUser.h"
#include "IDatabase"

class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;

public:
	void signup(std::string name, std::string password, std::string email);
	void login(std::string name, std::string password);
	void logout(std::string name);


};

