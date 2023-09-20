#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <stdexcept>
using namespace std;

/**
 * @details json风格string
 *
 */

class UtilsException : public exception
{
public:
    UtilsException(const string &error_msg) : error_msg(error_msg){};
    const char *what() const noexcept override
    {
        return error_msg.c_str();
    }

private:
    string error_msg;
};

inline bool isNumber(const string &str)
{
    istringstream iss(str);
    double value;
    if (!(iss >> value))
        return false;
    return true;
}

inline string jsonString(string &str)
{
    if (str.length() == 0)
    {
        throw UtilsException("字符个数太少");
    }

    string left = "{[",
           right = "]}";
    if (isNumber(str) || (left.find(str[0]) != left.npos && right.find(str[str.length() -1]) != right.npos))
    {
        return str;
    }
    else
    {
        return "\"" + str + "\"";
    }
}

#endif