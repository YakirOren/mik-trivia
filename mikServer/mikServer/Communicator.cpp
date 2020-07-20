#include "Communicator.h"

std::mutex clientsInsertMutex;

/*
	Accept's the newly entered user and inserts him into the 
*/
void Communicator::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	std::cout << "client_socket: " << client_socket << std::endl;

	// Inserts the client's data into the client's map
	std::unique_lock<std::mutex> lock(clientsInsertMutex);
	m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, new LoginRequestHandler(_database)));
	lock.unlock();

	//IDatabase* database = new sqlDatabase();
	// Creates a thread for the client
	std::thread new_client(&Communicator::handleNewClient, this, client_socket);
	new_client.detach();

}

/*
	Binds the connection between the server and the client and then listens to the socket.
	Input:
		None
	Output:
		None
*/
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	int port = 6969;

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		startHandleRequests();
	}

}

/*
	Handle's every newly contected client and saves the data from it's request.
	Input:
		SOCKET clientSocket: The socket between the server and the client
	Output:
		None
*/
void Communicator::handleNewClient(SOCKET clientSocket)
{
	RequestInfo requestInfo;
	RequestResult requestResult;
	std::vector<unsigned char> buffer = {};
	int type = 0, lengthOfData = 0;
	std::string data = "";

	try
	{
		//Recieving the code from the message
		type = Helper::getMessageTypeCode(clientSocket); 
		time(&(requestInfo.recievalTime)); // Getting the recieval time

		//Recieving the length of the data
		lengthOfData = Helper::getMessageLen(clientSocket);

		//Recieving the data itself
		recieveData(clientSocket, requestInfo.buffer, lengthOfData);
		
		std::cout << data << std::endl;

		requestInfo.id = type;

		if (m_clients[clientSocket] != nullptr)
		{
			requestResult = m_clients.at(clientSocket)->handleRequest(requestInfo);
			const char* response = reinterpret_cast<char*>(requestResult.response.data());
			std::cout << response << std::endl;
			//std::string temp(requestResult.response.begin(), requestResult.response.end());
			//Helper::sendData(clientSocket, requestResult.response);
			Helper::sendData(clientSocket, response, requestResult.response.size());
		}
		
		//removeClient(clientSocket);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		removeClient(clientSocket);
	}

	//closesocket(clientSocket);
}

/*
	Removes a client from the client's map
	Input:
		SOCKET clientSocket: The socket between the server and the client
	Output:
		None
*/
void Communicator::removeClient(SOCKET clientSocket)
{
	m_clients.erase(clientSocket);
}

/*
	Handles all of the client's requests
	Input:
		None
	Output:
		None
*/
void Communicator::startHandleRequests()
{
	std::cout << "Waiting for client connection request" << std::endl;
	accept();
}

/*
	Recieves the data from the client socket and saves it inside of the buffer
	Input:
		clientSocket: The socket between the client and the player
		buffer: The buffer in which we save the data
		size: The size of the data we want to recieve
	Output:
		None
*/
void Communicator::recieveData(SOCKET clientSocket, std::vector<unsigned char>& buffer, unsigned int size)
{
	buffer.clear();
	buffer.resize(size);
	if (!recv(clientSocket, (char*)&buffer[0], size, 0) || buffer[0] == 0)
	{
		throw std::exception("Error while recieving data");
	}

}


/*
	Constructor
*/
Communicator::Communicator(IDatabase* database, RequestHandlerFactory* handlerFactory)
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
	
	_database = database;
	_handlerFactory = handlerFactory;
}

/*
	Destructor
*/
Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor

		m_clients.erase(m_clients.begin(), m_clients.end());

		closesocket(_serverSocket);
	}
	catch (...) {}
}


