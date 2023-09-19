#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <string.h>
#include <sstream>
#include <string.h>
#include <ctype.h>
using namespace std;
#include "data_base.hpp"
#include "utils.h"

#pragma comment(lib, "ws2_32")
#define LINE_STATUS unsigned short
#define LINE_OK 0  // 读取的行完整
#define LINE_BAD 1 // 报文语法错误
#define LINE_BAD 2 // 读取的行不完整

class HttpServer
{
private:
    /* data */
    static int total;
    const int fd;
    std::string ipv4;
    DataBase* db;

private:
    int add_total();

public:
    HttpServer(unsigned short sv_port);
    ~HttpServer();
    string createHtmlResponse(string &data);
    string createJsonResponse(test_user * data);

    int routeUser(SOCKET &accept_fd);
};


#endif