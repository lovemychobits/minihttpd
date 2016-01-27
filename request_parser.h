#ifndef MINIHTTPD_REQUESTPARSER_H
#define MINIHTTPD_REQUESTPARSER_H

#include "header.h"

class request_parser {
public:
	request_parser();
	virtual ~request_parser();
	
	bool parse_http_request(int client_fd);
	
	const char* get_method();
	const char* get_url();
	int get_content_length();
	const char* get_content();

protected:
	int get_line(int client_fd, char* buf, int buf_len);
	
private:
	string method;				// request method, GET, POST ...
	string url;					// the url
	bool is_cgi;				// need execute cgi
	int content_length;			// html content length
	char* content;
};

#endif
