#include "LoginManager.h"

void LoginManager::signup(std::string name, std::string password, std::string email)
{

	if (!this->m_database->doesUserExists(name))
	{
		if (this->m_database->isValidPassword(password))
		{
			this->m_database->createUser(name, password, email);
			this->m_loggedUsers.emplace_back(name);

		}
		else
		{
			// password is invalid.
		}

	}
	else
	{
		// user with that name already exists.
	}



}

/*
this function should be called when the user 
Input:
Output:
*/
void LoginManager::login(std::string name, std::string password)
{
	if (this->m_database->doesUserExists(name, password))
	{
		this->m_loggedUsers.emplace_back(name);
	}


}


/*
this function should be called when the user request to logout or the connection fails.
the function deletes the user from the connected users vector.
Input:
	the name of the user we want to delete.
Output:
	None.
*/
void LoginManager::logout(std::string name)
{
	//find and delete the user.
	this->m_loggedUsers.erase(std::find_if(std::begin(this->m_loggedUsers), std::end(this->m_loggedUsers), [&](const auto& a) {return a.getUsername() == name}));


}
