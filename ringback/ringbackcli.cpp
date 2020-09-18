#include "mfs.h"
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>


void str_cli(int sockfd){
    std::string sendline;
    char recvline[MAXLINE];
    int nread;
    while(std::cin>>sendline){
        sendline+="\r\n";
        int fuck = writen(sockfd, sendline.c_str(), sendline.size());
        std::cout<<"等待信息返回"<<std::endl;
        if( (nread=readline(sockfd, recvline, MAXLINE)) >0){
            recvline[nread]=0;
          
        }    
            if(nread < 0) {
            std::cout<<"nread <0"<<std::endl;
            exit(1);
            }
        std::cout<<recvline<<std::endl;
    }
}

int main (int argc, char **argv){
    std::cout<<1<<std::endl;
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc != 2){
        perror ("usage: tcpcli<IPaddress>");
        exit(1);
    }
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port =htons(2020);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);  

    if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr) ))
    std::cout<<"connect error"<<std::endl;
    str_cli(sockfd);

    exit(0);
}
