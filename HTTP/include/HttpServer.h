#ifndef SERVER_H
#define SERVER_H
#include "ThreadPool.h"
#include "nsocket.h"
#include "Epoll.h"
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/sendfile.h>
#define CR '\r'
#define LF '\n'
#define LINE_END '\0'
// struct HttpMessage{
//     char * method;
//     char * version;
//     char * path;   
// };

// struct HttpResponse{
//     char * version;
//     char * code;
//     char * status;
//     char * server;
//     char 

// };

class HttpServer
{
private:
    ServerSocket serverSocket;
    char *buff;
    Epoll epoll;
public:
   explicit HttpServer(int port = 80, const char* ip= nullptr): serverSocket(port,ip),epoll(10, ET){
       serverSocket.bind();
       serverSocket.listen();
       buff = new char[1024];
       memset(buff,0,sizeof(buff));
   };
   void run();
    
   //void ans_request(ClientSocket&);
    void ans_request(int fd);
    ~HttpServer();
};








#endif