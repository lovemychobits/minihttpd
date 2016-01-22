#ifndef MINIHTTPD_REQUESTPARSER_H
#define MINIHTTPD_REQUESTPARSER_H

#include "header.h"

class request_parser {
public:
	request_parser();
	~ request_parser();
	
	bool parse_http_request(const char* request);
	
	const char* get_method();
	const char* get_url();
	
private:
	string method;				// request method, GET, POST ...
	string url;
};

#endif