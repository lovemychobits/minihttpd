#ifndef MINIHTTP_CGIMNG_H
#define MINIHTTP_CGIMNG_H

#include "header.h"

class cgi_mng {
public:
	cgi_mng();
	~cgi_mng();
	
	void execute_cgi(int client_fd, const char* cgi_name, const char* param);			// run the special cgi
};

#endif
