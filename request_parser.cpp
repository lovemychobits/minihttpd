#include "request_parser.h"

request_parser::request_parser() : is_cgi(false), content_length(0)
{

}

request_parser::~request_parser()
{

}

bool request_parser::parse_http_head(const char* request)
{
	// HTTP request format is:
	// like "GET /icwork/? search=product HTTP/1.1"
	
	int index = 0;
	// get the request method first
	while (request[index] != ' ') {			// until find the space
		method.append(1, request[index++]);
	}
	++index;
	
	// get the url
	while (request[index] != ' ') {			// until find the space
		url.append(1, request[index++]);
	}

	// find the content length
	const char* content = strstr(request, "Content-Length");
	if (content) {							// Content-Length is exist
		char content_len[12] = {0};
		const char* len = content + strlen("Content-Length:");
		int count = 0;
		while (len[count] != '\n') {
			content_len[count] = len[count];
			++count;
		}
		content_len[count] = '\0';
		content_length = atoi(content_len);
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

int request_parser::get_content_length() {
	return content_length;
}
