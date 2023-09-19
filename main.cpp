
#include "socket_server.h"
#include "thread_pool.hpp"
// #include "data_base.hpp"
using namespace std;
int i = 8082;
void *test2(void *)
{
    HttpServer(i++);
    return nullptr;
}

int main()
{
    HttpServer hs(8083);

    return 1;
}