#include "LoginRequestHandler.h"

std::mutex databaseMutex;

/*
	Constructor
*/
LoginRequestHandler::LoginRequestHandler(IDatabase* database) : IRequestHandler(), _handlerFactory(new RequestHandlerFactory(database))
{

}

/*
	Destructor
*/
LoginRequestHandler::~LoginRequestHandler()
{
}

/*
	Checks if the request of the client is valid ( If it includes a valid message type code
	then it's valid and the function returns true, if it doesn't the function returns false )
	Input: 
		RequestInfo request (struct): The request of the client
	Output:
		True of the request is valid, false otherwise.
*/
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	bool isRelevant = false;
	if (request.id == CLIENT_LOGIN || request.id == CLIENT_SIGNUP)
	{
		isRelevant = true;
	}
	return isRelevant;
}

/*
	Returns the correct response to the client's request after being serialized.
	Input:
		RequestInfo request (struct): The request of the client
	Output: 
		RequestResult result (struct): The response of the server based on the client's request
*/
RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult result = {};
	LoginRequest loginRequest = {};
	SignupRequest signupRequest = {};
	_handlerFactory->createLoginHandler();

	if (isRequestRelevant(request))
	{
		if (request.id == CLIENT_LOGIN)
		{
			// Deserializing the request of the client
			std::vector<unsigned char> buffer(request.buffer, request.buffer + strlen((char*)request.buffer));
			loginRequest = requestDeserializer::deserializeLoginRequest(buffer);
			databaseMutex.lock();
			result = login(loginRequest);
			databaseMutex.unlock();
			//result.response = ResponseSerializer::serializeResponse(loginResponse);
		}
		else if (request.id == CLIENT_SIGNUP)
		{
			//SignupResponse signupResponse = {(unsigned) 1};
			//result.response = ResponseSerializer::serializeResponse(signupResponse);
			std::vector<unsigned char> buffer(request.buffer, request.buffer + strlen((char*)request.buffer));
			signupRequest = requestDeserializer::deserializeSignupRequest(buffer);
			databaseMutex.lock();
			result = signup(signupRequest);
			databaseMutex.unlock();
		}
		else
		{
			ErrorResponse errorResponse = { "ERROR" };
			result.response = ResponseSerializer::serializeResponse(errorResponse);
		}
	}
	else
	{
		//If the request doesn't exist
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ "Request doesnt Exist" });
	}

	return result;
}

RequestResult LoginRequestHandler::login(LoginRequest request)
{
	RequestResult result = {};
	LoginResponse loginResponse = {1};
	try
	{
		_handlerFactory->getLoginManager().login(request.username, request.password);
		result.response = ResponseSerializer::serializeResponse(loginResponse);
	}
	catch (std::exception error)
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ error.what() });
	}
	return result;
}

RequestResult LoginRequestHandler::signup(SignupRequest request)
{
	RequestResult result = {};
	LoginResponse signupResponse = { 1 };
	try
	{
		_handlerFactory->getLoginManager().login(request.username, request.password);
		result.response = ResponseSerializer::serializeResponse(signupResponse);
	}
	catch (std::exception error)
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ error.what() });
	}
	return result;
}
