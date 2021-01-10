#ifndef SERVER_H
#define SERVER_H
#include "ThreadPool.h"
#include "nsocket.h"
#include "Epoll.h"
#include "wolf.h"
#include "Http.h"
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/sendfile.h>
#include <unordered_map>
#include <string.h>
using std:: cin;
using std:: cout;
using std:: endl;
using std:: unordered_map;
using std:: string;


const string WOLFCREATE = "WOLFCREATE";
const string WOLFENTER = "WOLFENTER";

class HttpServer
{
private:

    string status;
    ServerSocket serverSocket;
    char *buff;
    Epoll epoll;
    unordered_map<int ,wolf> room;//房间号，狼人房。
public:
   explicit HttpServer(int port = 80, const char* ip= nullptr): serverSocket(port,ip),epoll(10, ET){
       serverSocket.bind();
       serverSocket.listen();
       buff = new char[1024];
       memset(buff,0,sizeof(buff));
   };
   void run();
    
   //void ans_request(ClientSocket&);
    void do_request(int fd);
    unordered_map<string,int> json_parse(char *buf);
    int parse_request(int fd);
    
    ~HttpServer();
};








#endif