#include "LoginManager.h"

/*
	Constructor
*/
LoginManager::LoginManager(IDatabase* database)
{
	m_database = database;
}

/*
	Destructor
*/
LoginManager::~LoginManager()
{

}



/*
this function should be called when the user wants to signup.
Input:
	name, password, email.
Output:
	True/False if successful.
*/
bool LoginManager::signup(std::string name, std::string password, std::string email)
{
	bool status = false;
	if (!this->m_database->doesUserExists(name))
	{
		if (this->m_database->isValidPassword(password))
		{
			this->m_database->createUser(name, password, email);
			this->m_loggedUsers.emplace_back(name);
			status = true;
		}
		else
		{
			// password is invalid.
			status = false;
		}

	}
	else
	{
		// user with that name already exists.
		status = false;
	}

	return status;

}

/*
this function should be called when the user wants to login.
Input:
	name and password.
Output:
	True/False if successful.
*/
bool LoginManager::login(std::string name, std::string password)
{
	bool status = false;
	if (this->m_database->doesUserExists(name, password)) // if a user with that name and password exists let them in.
	{
		this->m_loggedUsers.emplace_back(name);
		status = true;
	}
	else
	{
		status = false;
	}
	return status;


}


/*
this function should be called when the user request to logout or the connection fails.
the function deletes the user from the connected users vector.
Input:
	the name of the user we want to delete.
Output:
	True/False if successful.
*/
bool LoginManager::logout(std::string name)
{
	bool status = false;
	//find the user.
	auto user = std::find_if(std::begin(this->m_loggedUsers), std::end(this->m_loggedUsers), [&](const auto& a) {return a.getUsername() == name; });
	if (user != std::end(this->m_loggedUsers))
	{
		//and delete the user
		this->m_loggedUsers.erase(user);
		status = true;
	}
	else
	{
		status = false;
	}

	return status;

}
