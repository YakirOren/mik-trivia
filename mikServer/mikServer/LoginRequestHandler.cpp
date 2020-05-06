#include "LoginRequestHandler.h"

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
	bool isRelevant = true;
	if (request.id == CLIENT_LOGIN || request.id == CLIENT_SIGNUP)
	{
		isRelevant = false;
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
			//LoginResponse loginResponse = {1};
			//result.response = responseSerializer::serializeResponse(loginResponse);
		}
		else
		{
			//SignupResponse signupResponse = {1};
			//result.response = responseSerializer::serializeResponse(signupResponse);
		}
	}
	else
	{
		//ErrorResponse errorResponse = {"ERROR"};
		//result.respose = responseSerializer::serializeResponse(errorResponse)
	}
	return result;
}
