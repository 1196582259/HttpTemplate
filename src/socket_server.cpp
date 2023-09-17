#include "socket_server.h"

char response[] = "HTTP/1.1 200 OK\r\n"
                  "Access-Control-Allow-Origin: *\r\n"
                  "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                  "<!DOCTYPE html>"
                  "<html lang=\"zh-CN\">"
                  "<head>"
                  "<meta charset=\"utf-8\">"
                  //   "<link rel=\"shortcut icon\" href=\"https://www.bilibili.com/favicon.ico\">"
                  "<title>Hello World</title>"
                  "<style>body {width: 35em;margin: 200px auto;font-family: Tahoma, Verdana, Arial, sans-serif;}"
                  "</style>"
                  "</head>"
                  "<body><h1>Hello World!</h1>"
                  "<p>If you see this page, the JJWebserver is successfully"
                  " working. </p>"
                  "<p><em>Thank you for using JJWebserver</em></p>"
                  "</body></html>\r\n";
int HttpServer::total = 0;
HttpServer::HttpServer(unsigned short sv_port) : fd(add_total())
{
    db = new DataBase();
    db->connect("127.0.0.1", "root", "root", "test", 3306);


    WSADATA wsa_data;
    SOCKET server_fd, // 总服务器进程
        acpt_fd;      // 服务器与客户端之间通信进程
    struct sockaddr_in server_addr, client_addr;
    unsigned short port = sv_port;
    int result = 0;
    int addr_len = sizeof(struct sockaddr_in);
    char recv_buf[2048];
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    result = bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (result == SOCKET_ERROR)
    {
        std::cout << "127.0.0.1:" << port << " bind error: " << WSAGetLastError << std::endl;
        closesocket(server_fd);
    }
    listen(server_fd, 10);
    std::cout << "127.0.0.1:" << port << " is running ... ..." << std::endl;

    while (1)
    {
        acpt_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (acpt_fd == INVALID_SOCKET)
        {
            printf("[Server] accept error: %d\n", WSAGetLastError());
            break;
        }

        // memset(recv_buf, 0, sizeof(recv_buf));
        result = recv(acpt_fd, recv_buf, 2048, 0);
        string request(recv_buf);
        if (request.find("GET /user") != string::npos)
        {
            result = routeUser(acpt_fd);
        }
        else
        {
            cout << response << endl;
            result = send(acpt_fd, response, sizeof(response), 0);
        }

        closesocket(acpt_fd);
    }
    closesocket(server_fd);
    WSACleanup();
}

int HttpServer::add_total()
{
    if (total == INT_MIN)
    {
        total = 1;
    }
    else
    {
        total += 1;
    }
    return total;
}
HttpServer::~HttpServer()
{
}

string HttpServer::createHtmlResponse(string &data)
{
    string response = "HTTP/1.1 200 OK\r\n"
                  "Access-Control-Allow-Origin: *\r\n"
                  "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                  "{\"message\":\"Hello, user!\"}";
    return response;
}

int HttpServer::routeUser(SOCKET &accept_fd)
{
    string data = "hhh";
    string str = createHtmlResponse(data);
    // db->query("user");
    test_user * tmp;
    db->query("user", tmp);
    return send(accept_fd, str.c_str(), sizeof(char) * strlen(str.c_str()), 0);
}
