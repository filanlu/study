#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define CR '\r'
#define LF '\n'
#define LINE_END '\0'

namespace Http
{
    string response(const string &key, int _i);
    string response(const string &key, const string &str);

} // namespace Http