project(minihttpd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wextra -Wall -pthread")

add_executable(minihttpd file_mng.cpp request_parser.cpp http_server.cpp http_builder.cpp cgi_mng.cpp main.cpp)

install(TARGETS minihttpd RUNTIME DESTINATION bin)
