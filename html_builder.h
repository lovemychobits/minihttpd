#ifndef MINIHTTP_HTMLBUILDER_H
#define MINIHTTP_HTMLBUILDER_H

#include "header.h"

class html_builder {
public:
	html_builder();
	~html_builder();
	
	string build_http_ok();
	string build_http_not_found();
	string build_http_server_error();
};

#endif