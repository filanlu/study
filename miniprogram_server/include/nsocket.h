#ifndef  SSOCKET_H
#define  SSOCKET_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

class ServerSocket
{
public:
    sockaddr_in mAddr;
    int fd;
    int mPort;
    const char* mIp;
public:
    ServerSocket(int port = 2020, const char* ip = nullptr);
    ~ServerSocket();
    void bind();
    void listen(int listenQ = 1024);
    int accept(sockaddr_in &);
    
};


void setReusePort(int fd);




#endif