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

	if (isRequestRelevant(request))
	{
		if (request.id == CLIENT_LOGIN)
		{
			loginRequest = requestDeserializer::deserializeLoginRequest(request.buffer);
			databaseMutex.lock();
			result = login(loginRequest);
			databaseMutex.unlock();
		}
		else if (request.id == CLIENT_SIGNUP)
		{
			signupRequest = requestDeserializer::deserializeSignupRequest(request.buffer);
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
		if (_handlerFactory->getLoginManager().login(request.username, request.password))
		{
			result.response = ResponseSerializer::serializeResponse(loginResponse);
			result.newHandler = _handlerFactory->createMenuRequestHandler(LoggedUser(request.username));
		}
		else
		{
			result.response = ResponseSerializer::serializeResponse(ErrorResponse{ "Error: Password or Username are not correct" });
		}
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
	SignupResponse signupResponse = { 1 };
	try
	{
		if (_handlerFactory->getLoginManager().signup(request.username, request.password, request.email))
		{
			result.response = ResponseSerializer::serializeResponse(signupResponse);
			result.newHandler = _handlerFactory->createMenuRequestHandler(LoggedUser(request.username));
		}
		else
		{
			result.response = ResponseSerializer::serializeResponse(ErrorResponse{ "Error: User Already Exist!" });
		}
	}
	catch (std::exception error)
	{
		result.response = ResponseSerializer::serializeResponse(ErrorResponse{ error.what() });
	}
	return result;
}
