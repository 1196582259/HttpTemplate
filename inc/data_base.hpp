#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <mysql.h>
#pragma once
#pragma commet(lib, "libmysql.lib")
using namespace std;

class DataBase
{
private:
    bool _state;
    MYSQL *_mysql;
    MYSQL_FIELD *_fields; // 字段列数组
    char _field[32][32];  // 存字段名二维数组
    MYSQL_RES *_res;
    MYSQL_ROW _column;
    char _query[150];

public:
    DataBase();
    ~DataBase();
    bool connect(const char *ip, const char *name, const char *cypher, const char *database_name, const int port);
    // 获取表内的字段数
    int get_table_field(const char *table_name);
    // 查询表 参数为表名
    bool query(const char *table_name);
    // 自由执行指令
    bool implement(const char *sentence);
};

DataBase::DataBase()
{
    _state = false;
    _mysql = new MYSQL;
    _fields = nullptr;
    // memset(_field, NULL, sizeof(_field));
    _res = nullptr;
    _column = nullptr;
    // memset(_query, NULL, sizeof(_query));
}
bool DataBase::connect(const char *ip, const char *name, const char *cypher, const char *database_name, const int port)
{
    if (true == _state)
    {
        cout << "DataBase is connected !" << endl;
        return false;
    }
    mysql_init(_mysql);
    // 返回false则连接失败，返回true则连接成功
    if ((mysql_real_connect(_mysql, ip, name, cypher, database_name, port, NULL, 0)) == NULL) // 中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去
    {
        system("pause");
        cout << "hhh" << endl;
        printf("Error connecting to database:%s\n", mysql_error(_mysql));
        return false;
    }
    else
    {
        system("pause");

        _state = true;
        printf("Connected succeed\n\n");
        return true;
    }
    return true;
}
int DataBase::get_table_field(const char *table_name)
{
    if (false == _state)
    {
        printf("Database not connected\n");
        return -1;
    }
    // 查询内容
    sprintf_s(_query, "desc %s", table_name); // desc 语句获取字段数
    // 设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
    mysql_query(_mysql, "set names gbk");
    // 返回0 查询成功，返回1查询失败
    if (mysql_query(_mysql, _query)) // 执行SQL语句
    {
        printf("Query failed (%s)\n", mysql_error(_mysql));
        return false;
    }
    // 获取结果集
    if (!(_res = mysql_store_result(_mysql))) // 获得sql语句结束后返回的结果集
    {
        printf("Couldn't get result from %s\n", mysql_error(_mysql));
        return false;
    }
    // 数据行数即为字段个数
    return mysql_affected_rows(_mysql);
}

bool DataBase::query(const char *table_name)
{
    if (false == _state)
    {
        printf("Database not connected\n");
        return false;
    }
    // 获取字段数
    int field = get_table_field(table_name);
    // 查询内容
    sprintf_s(_query, "select * from %s", table_name); // 执行查询语句
    // 设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
    mysql_query(_mysql, "set names gbk");
    // 返回0 查询成功，返回1查询失败
    if (mysql_query(_mysql, _query)) // 执行SQL语句
    {
        printf("Query failed (%s)\n", mysql_error(_mysql));
        return false;
    }
    else
    {
        printf("query success\n");
    }
    // 获取结果集
    if (!(_res = mysql_store_result(_mysql))) // 获得sql语句结束后返回的结果集
    {
        printf("Couldn't get result from %s\n", mysql_error(_mysql));
        return false;
    }
    // 打印数据行数
    printf("number of dataline returned: %lld\n", mysql_affected_rows(_mysql));
    // 获取字段的信息
    char *str_field[32];            // 定义一个字符串数组存储字段信息
    for (int i = 0; i < field; i++) // 在已知字段数量的情况下获取字段名
    {
        str_field[i] = mysql_fetch_field(_res)->name;
    }
    for (int i = 0; i < field; i++) // 打印字段
    {
        printf("%10s\t", str_field[i]);
    }
    printf("\n");
    // 打印获取的数据
    while (_column = mysql_fetch_row(_res)) // 在已知字段数量情况下，获取并打印下一行
    {
        for (int i = 0; i < field; i++)
        {
            printf("%10s\t", _column[i]); // column是列数组
        }
        printf("\n");
    }
    return true;
}

bool DataBase::implement(const char *sentence)
{
    if (false == _state)
    {
        printf("Database not connected\n");
        return false;
    }
    // 查询内容
    sprintf_s(_query, "%s", sentence); // desc 语句获取字段数
    // 设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
    mysql_query(_mysql, "set names gbk");
    // 执行SQL语句
    if (mysql_query(_mysql, _query))
    {
        printf("Query failed (%s)\n", mysql_error(_mysql));
        return false;
    }
    return true;
}
