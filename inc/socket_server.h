#pragma once
#include<iostream>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <sstream>
#include <string.h>
#pragma comment(lib, "ws2_32")
class HttpServer
{
private:
    /* data */
    static int total;
    const int fd;
    std::string ipv4;
    
    

private:
    int add_total();

public:
    HttpServer(unsigned short sv_port);
    ~HttpServer();

};
