#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

/**
 * @details json风格string
 *
 */

class UtilsException : public exception
{
public:
    UtilsException(const string &error_msg) : error_msg(error_msg)
    {
        const char *wait() const noexcept override
        {
            return error_msg.c_str();
        }
    }

private:
    string error_msg;
};

string jsonString(string &str)
{
    if (str.length < 2)
    {
        throw UtilsException("字符个数太少");
    } 
    if(str[0] != "{" && str[str.length() -1 ] != "}") {
        throw UtilsException("字符串格式不正确");
    }
    return "123";
}
