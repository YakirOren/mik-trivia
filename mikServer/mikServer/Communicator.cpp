#include "Communicator.h"


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

	// Creates a thread for the client
	std::thread new_client(&Communicator::handleNewClient, this, client_socket);
	new_client.detach();

	LoginRequestHandler* loginRequest = new LoginRequestHandler();

	// Inserts the client's data into the client's map
	m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, loginRequest));

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
	Handle's 
*/
void Communicator::handleNewClient(SOCKET clientSocket)
{
	RequestInfo requestInfo;
	RequestResult requestResult;
	
	int type = 0;
	std::string data;
	int name_len = 0;

	try
	{
		type = Helper::getMessageTypeCode(clientSocket);
				
		name_len = Helper::getMessageLen(clientSocket);

		data = Helper::getStringPartFromSocket(clientSocket, name_len);

		std::cout << "got message" << std::endl;

		std::cout << data << std::endl;

		requestInfo.id = type;
		requestInfo.buffer = Helper::to_array(data);

		time(&(requestInfo.recievalTime)); // Getting the recieval time
		requestResult = m_clients.at(clientSocket)->handleRequest(requestInfo);

		Helper::sendData(clientSocket, requestResult.response);
		
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
Communicator::Communicator()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
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


