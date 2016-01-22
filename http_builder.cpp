#include "html_builder.h"

html_builder::html_builder()
{
}

html_builder::~html_builder()
{
}

string html_builder::build_http_ok()
{
	string response = 	string("HTTP/1.0 200 OK\r\n") + 
						string("Server: jdbhttpd/0.1.0\r\n") + 
						string("Content-Type: text/html\r\n") +
						string("\r\n");
	string test_html= "<HTML><TITLE>Index</TITLE><BODY><P>Welcome to chobits's webserver.<H1>CGI demo<FORM ACTION='color.cgi' METHOD='POST'>Enter a color: <INPUT TYPE='text' NAME='color'><INPUT TYPE='submit'></FORM></BODY></HTML>";
	return response + test_html;
}
string html_builder::build_http_not_found()
{
	return "";
}
string html_builder::build_http_server_error()
{
	return "";
}