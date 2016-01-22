#include "request_parser.h"

request_parser::request_parser()
{

}

request_parser::~request_parser()
{

}

bool request_parser::parse_http_request(const char* request)
{
	// for test
	method = "GET";
	
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
