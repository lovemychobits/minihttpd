#ifndef MINIHTTP_FILEMNG_H
#define MINIHTTP_FILEMNG_H

#include "header.h"

class file_mng {
public:
	file_mng();
	~file_mng();
	
	// send file
	void send_file(int client_fd, const char* file_name);
	
protected:
	bool is_exist(const char* file_path);
	int open_file(const char* file_path);
};

#endif