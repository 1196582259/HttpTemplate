#include "socket_server.h"
#include "mysql.h"
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
    cout << "-------------"<<endl;
    MYSQL *conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "127.0.0.1", "root", "root", "test", 3306, NULL, CLIENT_FOUND_ROWS) == NULL)
    {
        cout << "-------------"<<endl;
        fprintf(stderr, "mysql_real_connect failed: Error %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
        cout << "-------------"<<endl;


    /*进行查询*/
    int res;
    if (res = mysql_query(conn, "SELECT * FROM user"))
    {
        fprintf(stderr, "mysql_query failed: Error %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    cout << res <<endl;
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(result))!= NULL) {
        printf("%s %s", row[0], row[1]);
    }

    mysql_close(conn);
    return 1;
}