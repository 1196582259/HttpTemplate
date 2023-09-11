
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
    d1->connect("127.0.0.1", "root", "root", "sys", 3306);
    cout << endl;
    system("pause");
    d1->query("metrics");
    printf("\n");
    return 1;

}