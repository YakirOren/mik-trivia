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
	unsigned int lengthOfBuffer = 0;
	std::vector<std::string> buffer;
	//std::string message;
	RequestInfo requestInfo;
	RequestResult requestResult;
	
	std::string temp;

	try
	{
		Helper::sendData(clientSocket, "0b10100");

		buffer = recieveData(clientSocket);

		std::cout << "got message" << std::endl;

		requestInfo.buffer = buffer;
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



	//int name_len;
	//int second_name_len;

	//std::string name;
	//std::string second_name;
	//std::string file_name;

	//try
	//{
	//	while (true)
	//	{
	//		int type = Helper::getMessageTypeCode(clientSocket);


	//		switch (type)
	//		{

	//		case MessageType::MT_CLIENT_LOG_IN:
	//			std::cout << "login!" << std::endl;
	//			name_len = stoi(Helper::getStringPartFromSocket(clientSocket, 2));
	//			name = Helper::getStringPartFromSocket(clientSocket, name_len);

	//			connected_clients.emplace_back(clientSocket, name, name_len);

	//			std::cout << name << std::endl;

	//			Helper::send_update_message_to_client(clientSocket, "", "", getAll_usernames());

	//			break;

	//		case MessageType::MT_CLIENT_UPDATE:

	//			second_name_len = stoi(Helper::getStringPartFromSocket(clientSocket, 2));
	//			second_name = Helper::getStringPartFromSocket(clientSocket, second_name_len);

	//			int msg_len = stoi(Helper::getStringPartFromSocket(clientSocket, 5));
	//			std::string msg = Helper::getStringPartFromSocket(clientSocket, msg_len);



	//			if (name < second_name) // sorting the names
	//			{
	//				file_name = name + "&" + second_name + ".txt";
	//			}
	//			else
	//			{
	//				file_name = second_name + "&" + name + ".txt";
	//			}

	//			std::ofstream file(file_name, std::ofstream::out | std::ofstream::app);

	//			if (msg != "")
	//			{
	//				std::cout << file_name << std::endl;
	//				file << "&MAGSH_MESSAGE&&Author&" << name << "&DATA&" << msg << "\n";
	//			}

	//			file.close();

	//			std::ifstream ifs(file_name);
	//			std::string str(std::istreambuf_iterator<char>{ifs}, {});

	//			Helper::send_update_message_to_client(clientSocket, str, second_name, getAll_usernames());
	//			break;

	//		}

	//	}
	//closesocket(clientSocket);
	//}
	//catch (const std::exception & e)
	//{
	//	
	//	std::cout << clientSocket << " disconnected" << std::endl;
	//	removeClient(clientSocket);
	//	std::cout << clientSocket <<"removed from list" << std::endl;

	//	//std::cout << e.what() << std::endl;
	//	closesocket(clientSocket);
	//}



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

std::vector<std::string> Communicator::recieveData(SOCKET clientSocket)
{
	std::vector<std::string> bin_data;
	std::string temp;

	int result = 0;
	char buffer[1] = { 0 };
	int count = 0;

	result = recv(clientSocket, buffer, 1, NULL);
	while (result != 0)
	{
		if (buffer[0] != ' ')
		{
			temp += buffer[0];
		}
		else
		{
			bin_data.push_back(temp);
			temp = "";
			if (count > 2)
			{
				int len = std::stoi(bin_data[1], nullptr, 2);

				if (count == len) {
					break;
				}

			}
			count++;
		}

		result = recv(clientSocket, buffer, 1, NULL);

	}


	return bin_data;
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


