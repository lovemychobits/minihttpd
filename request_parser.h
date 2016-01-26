#ifndef MINIHTTPD_REQUESTPARSER_H
#define MINIHTTPD_REQUESTPARSER_H

#include "header.h"

class request_parser {
public:
	request_parser();
	~ request_parser();
	
	bool parse_http_head(const char* request);
	
	const char* get_method();
	const char* get_url();
	int get_content_length();
	
private:
	string method;				// request method, GET, POST ...
	string url;					// the url
	bool is_cgi;				// need execute cgi
	int content_length;			// html content length
};

#endif
