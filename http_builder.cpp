#include "html_builder.h"

html_builder::html_builder()
{
}

html_builder::~html_builder()
{
}

string html_builder::build_http_ok()
{
	string header = string("HTTP/1.0 200 OK\r\n") + 
					string("Server: minihttpd/0.1.0\r\n") + 
					string("Content-Type: text/html\r\n") +
					string("\r\n");
	return header;
}
string html_builder::build_http_not_found()
{
	return "";
}
string html_builder::build_http_server_error()
{
	return "";
}