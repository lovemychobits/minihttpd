#include "request_parser.h"

request_parser::request_parser() : is_cgi(false), content_length(0), content(NULL)
{

}

request_parser::~request_parser()
{

}

bool request_parser::parse_http_request(int client_fd)
{
	char head[1024] = {0};
	size_t len = 0;
	int line_size = get_line(client_fd, head, sizeof(head));
	
	// get the request method first
	int index = 0;
	while (head[index] != ' ') {			// until find the space
		method.append(1, head[index++]);
	}
	++index;
	
	// get the url
	while (head[index] != ' ') {			// until find the space
		url.append(1, head[index++]);
	}
	if (url == "/") {
		url = "index.html";
	}
	
	// find the content length
	line_size = get_line(client_fd, head, sizeof(head));
	while (line_size > 0 && strcmp("\n", head)) {
		head[15] = '\0';			// convert ':' to '\0'
		if (strcasecmp("Content-Length:", head) == 0) {
			content_length = atoi(&head[16]);
		}
		line_size = get_line(client_fd, head, sizeof(head));
	}

	// get the content
	content = new char[content_length];
	if (!content) {
		return false;
	}
	int recvd = 0;
	while (recvd < content_length) {
		int ret = read(client_fd, content + recvd, content_length - recvd);
		if (ret <= 0) {
			return false;
		}
		recvd += ret;
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

const char* request_parser::get_content() {
	return content;
}

// http head line end with "\r\n"
int request_parser::get_line(int client_fd, char * buf, int buf_len) {
	int i = 0; 
	char c = '\0'; 
	int n; 
	while ((i < buf_len - 1) && (c != '\n')) {  
		n = recv(client_fd, &c, 1, 0);  
		if (n > 0)  {
			if (c == '\r')   {    
				n = recv(client_fd, &c, 1, MSG_PEEK);    
				if ((n > 0) && (c == '\n')) {
					recv(client_fd, &c, 1, 0);    
				}
				else {
					c = '\n';   
				}
			}   
			buf[i] = c;   
			i++;  
		}  
		else {
			c = '\n'; 
		}
	} 
	buf[i] = '\0';  
	return(i);
}