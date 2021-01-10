#include<iostream>
#include<string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

#define CR '\r'
#define LF '\n'
#define LINE_END '\0'

namespace Http{
    string response(const string &key, int _i);
    string response(const string &key, const string &str);

}