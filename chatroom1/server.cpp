#include "mfs.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
using namespace std;
void  str_serv(int sockfd){
    ssize_t n;
    char buf[MAXLINE];
    while((n = readline(sockfd, buf ,MAXLINE))> 0){
        buf[n]='\0';
        std::cout<<buf<<std::endl;
       writen(sockfd, buf, strlen(buf));      
    }
}

int main(int argc ,char **argv){
    int listenfd;
    int connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(2020);
    
    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    
    listen(listenfd, LISTENQ);
    signal(SIGCHLD, sig_chld);
    for(; ;){
        clilen = sizeof(cliaddr);
      	if(  (connfd = accept(listenfd, (SA*)&cliaddr, &clilen)) <0  ){
		if(errno == EINTR)
			continue; //restart
		else perror("accept error");	
	}
 
	if( (childpid = fork()) == 0){
        printf("connection from %s, port %d\n",
        inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff) ),ntohs(cliaddr.sin_port));
            close(listenfd);
            str_serv(connfd);
            exit(0);
        }
        close(connfd);
    }
}
