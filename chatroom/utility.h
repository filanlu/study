#ifndef  UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include <iostream>
#include <sys/socket.h>
#include<fcntl.h>
#include<list>
using  namespace std;
//clients_list save all the clients`s socket
list<int> clients_list;
# define SERVER_IP "127.0.0.1"
#define  SERVER_PORT "8888"
#define EPOLL_SIZE 5000
#define BUF_SIZE 0xFFF
#define SEVER_WELCOME "Welcome you jion to the chat room! your chat ID is: Client #%d"
#define SERVER_MESSAGE "Client %d say >> %s"
#define EXIT "EXIT"
#define CAUTION "There is only one int chat room!"

/******************* function *******************/
int setnonblocking(int sockfd){//设置sock描述符为非阻塞
    fcntl(sockfd, F_SETFL,fcntl(sockfd,F_GETFD,0)|O_NONBLOCK);
    return 0;
}
#endif