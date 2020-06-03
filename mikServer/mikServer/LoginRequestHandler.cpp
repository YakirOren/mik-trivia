#include "LoginRequestHandler.h"

//LoginRequestHandler::LoginRequestHandler(IDatabase* database) : IRequestHandler(), _handlerFactory(new RequestHandlerFactory(database))
//{
//
//}

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
	struct RequestResult result = {};
	
	if (isRequestRelevant(request))
	{
		if (request.id == CLIENT_LOGIN)
		{
			LoginResponse loginResponse = {(unsigned) 1};
			result.response = ResponseSerializer::serializeResponse(loginResponse);
		}
		else if (request.id == CLIENT_SIGNUP)
		{
			SignupResponse signupResponse = {(unsigned) 1};
			result.response = ResponseSerializer::serializeResponse(signupResponse);
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

RequestResult LoginRequestHandler::login(RequestInfo request)
{
	return RequestResult();
}

RequestResult LoginRequestHandler::signup(RequestInfo request)
{
	return RequestResult();
}
