#include "../include/Http.h"
string Http::response(const string &key, int _i)
{
    string response_message = "HTTP/1.1 200 OK\r\n";
    response_message += " Accept-Control-Allow-Origin:*\r\n";
    response_message += "Cache-Control:no-cache\r\n";
    response_message += "Content-Type: application/json\r\n";
    string content_length = "Content-Length: " + std::to_string(std::to_string(_i).size() + 5 + key.size()) + CR + LF + CR + LF;
    response_message += content_length + "{\"" + key + "\":" + std::to_string(_i) + "}";

    cout << endl
         << "响应报文：" << endl
         << response_message << endl;
    return response_message;
}
string Http::response(const string &key, const string &str)
{
    string response_message = "HTTP/1.1 200 OK\r\n";
    response_message += "Accept-Control-Allow-Origin:*\r\n";
    response_message += "Cache-Control:no-cache\r\n";
    response_message += "Content-Type: application/json\r\n";
    string content_length = "Content-Length: " + std::to_string(7 + key.size() + str.size()) + CR + LF + CR + LF;
    response_message += content_length + "{\"" + key + "\":\"" + str + "\"}";

    cout << endl
         << "响应报文：" << endl
         << response_message << endl;
    return response_message;
}
