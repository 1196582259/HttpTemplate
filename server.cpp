#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <string.h>
#include <sstream>
#pragma comment(lib, "ws2_32")
using namespace std;

#define ECHO_DEF_PORT 8082
#define ECHO_BUF_SIZE 256

char response[] = "HTTP/1.1 200 OK\r\n"
                  "Access-Control-Allow-Origin: *\r\n"
                  "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                  "<!DOCTYPE html>"
                  "<html lang=\"zh-CN\">"
                  "<head>"
                  "<meta charset=\"utf-8\">"
                  "<title>Hello World</title>"
                  "<style>body {width: 35em;margin: 200px auto;font-family: Tahoma, Verdana, Arial, sans-serif;}"
                  "</style>"
                  "</head>"
                  "<body><h1>Hello World!</h1>"
                  "<p>If you see this page, the JJWebserver is successfully"
                  " working. </p>"
                  "<p><em>Thank you for using JJWebserver</em></p>"
                  "</body></html>\r\n";

stringstream generateHTTPResponse(string body)
{
    stringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << body.length() << "\r\n";
    response << "Access-Control-Allow-Origin: *";
    response << "\r\n";
    response << body;
    return response;
}

int main(int argc, char **argv)
{
    WSADATA wsa_data;
    SOCKET server_fd = 0,
           acpt_fd = 0;
    struct sockaddr_in serv_addr, clnt_addr;
    unsigned short port = ECHO_DEF_PORT;
    int result = 0;
    int addr_len = sizeof(struct sockaddr_in);
    char recv_buf[ECHO_BUF_SIZE];
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    result = bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (result == SOCKET_ERROR)
    {
        printf("[Server] bind error: %d\n", WSAGetLastError());
        closesocket(server_fd);
        return -1;
    }

    listen(server_fd, 10);
    printf("[Server] is running ... ...\n");

    while (1)
    {
        acpt_fd = accept(server_fd, (struct sockaddr *)&clnt_addr, &addr_len);
        if (acpt_fd == INVALID_SOCKET)
        {
            printf("[Server] accept error: %d\n", WSAGetLastError());
            break;
        }
        // memset(recv_buf, 0, sizeof(recv_buf));
        result = recv(acpt_fd, recv_buf, ECHO_BUF_SIZE, 0);
        string request(recv_buf, result);
        if (request.find("/user") != string::npos)
        {
            cout<< " user" << endl;
        }
        printf("[Server] receives: \"%s\", from %s\r\n", recv_buf, inet_ntoa(clnt_addr.sin_addr));
        result = send(acpt_fd, response, sizeof(response) - 1, 0);
        closesocket(acpt_fd);
    }
    closesocket(server_fd);
    WSACleanup();
    return 0;
}