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
	int content_len = strlen(param);
	int fd[2];			// for the pipe
	int fd2[2];
	if (pipe(fd) < 0) {
		cout << "pipe failed." << endl;
		return;
	}
	if (pipe(fd2) < 0) {
		cout << "pipe failed" << endl;
		return;
	}

	pid_t id = fork();
	if (id == -1) {
		cout << "fork failed." << endl;
		return;
	}

	html_builder builder;
	string header = builder.build_http_ok();		
	send(client_fd, header.c_str(), header.size(), 0);
	
	if (id == 0) {				// child process
		dup2(fd[1], 1);
		dup2(fd2[0], 0);
		
		char method_env[1024] = {0};
		char query_env[1024] = {0};
		char content_len_env[1024] = {0};

		sprintf(method_env, "REQUEST_METHOD=POST");
		putenv(method_env);
		//sprintf(query_string, "QUERY_STRING=%s", param);   
		sprintf(content_len_env, "CONTENT_LENGTH=%d", content_len);   
		putenv(content_len_env);
		
		string cgi_path = string("html/") + string(cgi_name);

		execl(cgi_path.c_str(), cgi_path.c_str(), NULL);
		exit(0);
	}
	else {						// parent process
		sleep(5);
		write(fd2[1], param, strlen(param));
	
		char buf[1024] = {0};
		while (true) {
			int ret = read(fd[0], buf, sizeof(buf)-1);
			cout << "ret=" << ret << endl;
			if (ret <= 0) {
				break;
			}
		
			send(client_fd, buf, ret, 0);
			break;
		}
	}
	
	return;
}
