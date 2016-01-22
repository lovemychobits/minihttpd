#include "file_mng.h"
#include "html_builder.h"

file_mng::file_mng()
{

}

file_mng::~file_mng()
{

}

void file_mng::send_file(int client_fd, const char* file_name)
{
	string file_path = string("html/") + string(file_name);
	cout << "begin to send file=" << file_path << endl;
	
	if (!is_exist(file_path.c_str())) {
		// to send file not found
		cout << file_path << " not found" << endl;
		return;
	}
	
	int fd = open_file(file_path.c_str());
	if (fd < 0) {
		// to send server error
		cout << "cannot open file:" << file_path << endl;
		return;
	}
	
	// send http header
	html_builder builder;
	string header = builder.build_http_ok();
	send(client_fd, header.c_str(), header.size(), 0);
	
	char buf[1024] = {0};
	while (true) {
		int ret = read(fd, buf, sizeof(buf)-1);
		cout << "ret=" << ret << endl;
		if (ret <= 0) {
			break;
		}
		
		send(client_fd, buf, ret, 0);
	}
	return;
}

int file_mng::open_file(const char* file_path)
{
	int fd = open(file_path, O_RDONLY);			// read only to open
	if (fd <= 0) {
		return -1;
	}
	return fd;
}

bool file_mng::is_exist(const char* file_path)
{
	struct stat st;
	if (stat(file_path, &st) == -1) {
		return false;
	}
	
	return true;
}

