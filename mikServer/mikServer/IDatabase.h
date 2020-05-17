#pragma once
#include <string>
class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool doesUserExists(std::string name) = 0;
	virtual bool doesUserExists(std::string name, std::string password) = 0;
	virtual void createUser(std::string name, std::string password, std::string email) = 0;
	virtual bool isValidPassword(std::string password) = 0;

private:
	virtual bool open() = 0;
	virtual void close() = 0;



};

