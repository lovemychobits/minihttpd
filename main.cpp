#include <iostream>
#include <stdlib.h>

#include "http_server.h"

int main(int argc, char **argv) {
	// default http server port
	int port = 8081;
	if (argc >= 2) {
		port = atoi(argv[1]);
	}
    http_server server;
	if (!server.init(port)) {
		return 1;
	}
	
	cout << "server start" << endl;
	server.start();
    return 0;
}
