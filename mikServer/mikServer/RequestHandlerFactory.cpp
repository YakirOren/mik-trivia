#include "RequestHandlerFactory.h"

/*
	Constructor
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(new LoginManager(database)), m_database(database), m_StatisticsManager(nullptr)
{
	m_roomManager = RoomManager::getInstance(m_database);
}

/*
	Destructor
*/
RequestHandlerFactory::~RequestHandlerFactory()
{
	//clear memory of all allocated managers
	if (m_StatisticsManager != nullptr)
	{
		delete m_StatisticsManager;
		m_StatisticsManager = nullptr;
	}
	if (m_loginManager != nullptr)
	{
		delete m_loginManager;
		m_loginManager = nullptr;
	}
	if (m_roomManager != nullptr)
	{
		delete m_roomManager;
		m_roomManager = nullptr;
	}
}

/*
	Creates a new LoginRequestHandler object
	Input:
		None
	Output:
		a new LoginRequestHandler object
*/
LoginRequestHandler RequestHandlerFactory::createLoginHandler()
{
	return LoginRequestHandler(m_database);
}

/*
	Returns the login manager
	Input:
		None
	Output:
		Pointer to the login manager
*/
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return *m_loginManager;
}

/*
	creates menu manager
	Input:
		None
	Output:
		MenuRequestHandler object
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	m_StatisticsManager = new StatisticsManager(m_database);
	return (new MenuRequestHandler(user, this));
}

/*
	Returns the statistics manager
	Input:
		None
	Output:
		Pointer to the statistics manager
*/
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return *m_StatisticsManager;
}

/*
	Returns the room manager
	Input:
		None
	Output:
		Pointer to the room manager
*/
RoomManager& RequestHandlerFactory::getRoomManager()
{
	std::cout << &m_roomManager << std::endl;
	return *m_roomManager;
}
