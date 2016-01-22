#include "request_parser.h"

request_parser::request_parser() : is_cgi(false)
{

}

request_parser::~request_parser()
{

}

bool request_parser::parse_http_request(const char* request)
{
	// HTTP request format is:
	// like "GET /icwork/? search=product HTTP/1.1"
	
	int index = 0;
	// get the request method first
	while (request[index] != ' ') {			// until find the space
		method.append(1, request[index++]);
	}
	
	// get the url
	while (request[index] != ' ') {			// until find the space
		url.append(1, request[index++]);
	}
	
	return true;
}

const char* request_parser::get_method()
{
	return method.c_str();
}

const char* request_parser::get_url()
{
	return url.c_str();
}
