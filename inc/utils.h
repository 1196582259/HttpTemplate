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

inline bool isNumber(const string& str) {
    istringstream iss(str);
    double value;
    if(!(iss >> value)) return false; 
    return true;
}


inline string jsonString(string &str)
{
    if (str.length() == 0)
    {
        throw UtilsException("字符个数太少");
    }


    if(isNumber(str)) {
        return str;
    } else {
        return "\"" + str + "\"";
    }

    return "123";
}
