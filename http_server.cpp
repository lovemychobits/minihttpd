#include "http_server.h"
#include "request_parser.h"
#include "html_builder.h"
#include "file_mng.h"
#include "cgi_mng.h"

http_server::http_server()
{

}

http_server::~http_server()
{

}

bool http_server::init(int port, const char* ip)
{
	struct sockaddr_in addr;
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		cout << "create server sock failed." << endl;
		return false;
	}
	
	int option = 1;
	if (setsockopt (server_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
	{
		cout << "set sockopt failed" << endl;
		return false;
	}
	
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	socklen_t addr_len = sizeof(addr);
	
	if (bind(server_sock, (struct sockaddr*)&addr, addr_len) < 0) {
		cout << "bind server sock failed" << endl;
		return false;
	}
	
	if (listen(server_sock, 10) < 0) {
		cout << "listen failed" << endl;
		return false;
	}
	
	return true;
}

void* client_thread(void* args) {
	cout << "begin client request" << endl;
	
	int client_fd = *(int*)args;
	char buf[1024] = {0};
	size_t len = 0;
	while (len < sizeof(buf)-1
		&& buf[len] != '\r'
		&& buf[len-1] != '\n'
	) {
		int ret = read(client_fd, buf + len, sizeof(buf) - len);
		if (ret <= 0) {
			break;
		}
		len += ret;
	}
	
	// to parse request
	cout << "parse client request" << endl;
	request_parser parser;
	if (!parser.parse_http_request(buf)) {
		cout << "parse http request failed." << endl;
		cout << "request=[" << buf << "]" << endl;
		return NULL;
 	}
 	
 	cout << "client request methond=" << parser.get_method() << endl;
 	if (strcasecmp(parser.get_method(), "GET") == 0) {
		file_mng filemng;
		filemng.send_file(client_fd, "index.html");
	}
	else if (strcasecmp(parser.get_method(), "POST") == 0) {
		cgi_mng cgimng;
		cgimng.execute_cgi(client_fd, "color.cgi");
	}
	
	return NULL;
}

void http_server::start()
{
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	while (true) {
		memset(&client_addr, 0, sizeof(client_addr));
		int client_sock = accept(server_sock, (sockaddr*)&client_addr, &addr_len);
		if (client_sock < 0) {
			cout << "accept error" << endl;
			continue;
		}
		
		pthread_t client_id;
		if (pthread_create(&client_id, NULL, client_thread, (void*)&client_sock) != 0) {
			cout << "create thread failed" << endl;
			continue;
		}
	}
}


