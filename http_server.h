#ifndef MINIHTTPD_HTTPSERVER_H
#define MINIHTTPD_HTTPSERVER_H

#include "header.h"

class http_server {
public:
	http_server();
	~http_server();
	
	bool init(int port, const char* ip=NULL);
	void start();
	
private:
	int server_sock;
};

#endif