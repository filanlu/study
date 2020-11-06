#include "../include/Epoll.h"

Epoll::Epoll(int max_events, bool mod = true) : _max_events(max_events), _mod(mod), countfd(0)
{
    _epoll_fd = epoll_create1(0);
    if (_epoll_fd == -1)
    {
        perror("epoll creates error");
        exit(EXIT_FAILURE);
    }
    _events = new epoll_event[max_events];
}

int Epoll::wait()
{
    if (!countfd)
    {
        std::cout << "没有监听描述符" << std::endl;
        return -1;
    }
    int nready = epoll_wait(_epoll_fd, _events, _max_events, -1);
    if (nready == -1)
    {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }
    return nready;
}

int Epoll::addSock(int sockfd, bool is_listen)
{
    //std::cout << "addSock" << std::endl;
    if (is_listen)
    {
        _listenfd = sockfd;
        _ev.events = EPOLLIN;
    }
    else{
        //EPOLLONESHOT:触发事件后从epollfd里面删除，如果重复监听需要重置epoll_ctl
    _ev.events = _mod ? (EPOLLIN | EPOLLET | EPOLLONESHOT) : (EPOLLIN | EPOLLONESHOT);
    
    }
    _ev.data.fd = sockfd;
    
    if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, sockfd, &_ev) == -1)
    {
        perror("addsock when epoll_ctl a fd meet an error");
        exit(EXIT_FAILURE);
    }

    ++countfd;
}
// int Epoll:: delSock(int fd){
//     std::cout<<"delSock"<<std::endl;

// }   

int Epoll::getListenfd()
{
    return _listenfd;
}

epoll_event &Epoll::getEvent(int idx)
{
    return _events[idx];
}
void Epoll::delcount(){
    --countfd;
}
int Epoll:: get_epoll_fd(){
    return _epoll_fd;
}
Epoll::~Epoll()
{
    close(_epoll_fd);
}