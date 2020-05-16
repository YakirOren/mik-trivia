#pragma once
class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool doesUserExists(int userId) = 0;
	virtual void createUser(std::string name, std::string password, std::string email) = 0;
	virtual bool isValidPassword(std::string) = 0;

	virtual bool open() = 0;
	virtual void close() = 0;



};

