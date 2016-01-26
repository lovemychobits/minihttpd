#include "cgi_mng.h"
#include "html_builder.h"

cgi_mng::cgi_mng()
{

}

cgi_mng::~cgi_mng()
{

}

void cgi_mng::execute_cgi(int client_fd, const char* cgi_name, const char* param)
{
	int fd[2];			// for the pipe
	if (pipe(fd) < 0) {
		cout << "pipe failed." << endl;
		return;
	}
	
	pid_t id = fork();
	if (id == -1) {
		cout << "fork failed." << endl;
		return;
	}
	
	if (id == 0) {				// child process
		string cgi_path = string("html/") + string(cgi_name);
		dup2(fd[1], 1);
		execl(cgi_path.c_str(), "");
		
	}
	else {						// parent process
		html_builder builder;
		string header = builder.build_http_ok();
		send(client_fd, header.c_str(), header.size(), 0);
	
		char buf[1024] = {0};
		while (true) {
			int ret = read(fd[0], buf, sizeof(buf)-1);
			cout << "ret=" << ret << endl;
			if (ret <= 0) {
				break;
			}
		
			send(client_fd, buf, ret, 0);
		}
	}
	
	return;
}
