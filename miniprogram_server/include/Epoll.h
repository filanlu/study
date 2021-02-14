#include <sys/epoll.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
enum
{
    LT,
    ET
};
class Epoll
{
private:
    epoll_event _ev;
    epoll_event *_events;
    int _epoll_fd;
    int _listenfd;
    int _max_events;
    bool _mod;
    int countfd;
    std::vector<int> _data; //存放数据

protected:
public:
    //create epollfd;
    Epoll(int max_events, bool mod);
    ~Epoll();
    int wait();
    int addSock(int sockfd, bool is_listenfd = false);
    // int delSock(int fd);
    int getListenfd();
    epoll_event &getEvent(int idx);
    void delcount();
    int get_epoll_fd();
};
