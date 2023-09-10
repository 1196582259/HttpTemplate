#include "socket_server.h"
#include "mysql.h"
#include "data_base.hpp"
using namespace std;
#pragma commet(lib, "libmysql.lib")

/**
 * @param {int} a
 * @return int
 */
int test(int a)
{
    cout << a << endl;
    return a;
}

int main()
{
    DataBase* d1 = new DataBase;
    d1->connect("localhost", "root", "root", "test", 0);
    cout << endl;
    d1->query("user");
    printf("\n");
    return 1;
}