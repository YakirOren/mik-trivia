#include "Communicator.h"

std::mutex clientsInsertMutex;

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

	IDatabase* database = new sqlDatabase();
	// Creates a thread for the client
	std::thread new_client(&Communicator::handleNewClient, this, client_socket);
	new_client.detach();

}

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
	
	int type = 0, lengthOfData = 0;
	std::string data = "";

	try
	{
		//Recieving the code from the message
		type = Helper::getMessageTypeCode(clientSocket); //Function doesn't work for some reason, Need to be fixed
		type = CLIENT_SIGNUP;
		
		//Recieving the length of the data
		lengthOfData = Helper::getMessageLen(clientSocket); //Works

		//Recieving the data itself
		data = Helper::getStringPartFromSocket(clientSocket, lengthOfData); //Works

		std::cout << "got message" << std::endl;

		std::cout << data << std::endl;

		requestInfo.id = type;
		requestInfo.buffer = Helper::to_array(data);

		time(&(requestInfo.recievalTime)); // Getting the recieval time
		requestResult = m_clients.at(clientSocket)->handleRequest(requestInfo);
		unsigned char* response = static_cast<unsigned char*>(requestResult.response.data());
		Helper::sendData(clientSocket, response);
		
		while (true)
		{

		}
		
		removeClient(clientSocket);
	}
	catch (const std::exception&)
	{
		removeClient(clientSocket);
	}

	closesocket(clientSocket);
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

void Communicator::recieveData(SOCKET clientSocket, std::vector<unsigned char>& buffer, unsigned int size)
{
	/*char* data = {};
	int index = 1;
	buffer.clear();
	buffer.resize(size);
	while (true)
	{
		recv(clientSocket, data, index, 0);
		if (data[strlen(data)] != " ")
		{

		}
	}*/

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

