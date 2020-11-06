#include "mfs.h"
#include <list>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;
void str_serv(int sockfd){

}
int main(){
    int     nready, sockfd, listenfd, epollfd;
    char    buff[MAXLINE];
    socklen_t   socklen,clilen;
    sockaddr_in servaddr,cliaddr;
    epoll_event ev,events[MAXEVENTS];
    list<unordered_map<int, string>> user;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2020);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen = sizeof(servaddr);
    clilen = sizeof(cliaddr);


    bind(listenfd, (SA *)&servaddr, socklen);

    listen(listenfd, LISTENQ);

    epollfd = epoll_create1(0);
    if(epollfd == -1){
        perror("epoll_create1 error");
        exit(EXIT_FAILURE);
    }
    
    ev.events = EPOLLRDNORM;
    ev.data.fd = listenfd;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&ev) == -1){
        perror("epoll_ctl: listenfd");
        exit(EXIT_FAILURE);
    }
    while(1){
        nready = epoll_wait(epollfd, events, MAXEVENTS, -1);
        
        if(nready == -1){
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        for(int n = 0 ;n < nready; ++n){
            if(events[n].data.fd == listenfd){
                sockfd = accept(listenfd,(SA *)&cliaddr, &clilen);
                printf("connection from %s, port %d\n",
                           inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));
            }
            /*setnonblocking(conn_sock);*/
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = sockfd;
            if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&ev) == -1){
                perror("epoll_ctl: listenfd");
                exit(EXIT_FAILURE);
            }
            str_serv(events[n].data.fd);
            
        }
    }

    
    
}
