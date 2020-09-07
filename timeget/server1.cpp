#include "mfs.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char **argv){
    int     listenfd,connfd;
    struct  sockaddr_in servaddr,cliaddr;
    char    buff[MAXLINE];
    time_t  ticks;
    socklen_t len;

    listenfd =socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr =htonl(INADDR_ANY);//host to net 32位long
    servaddr.sin_port=htons(2020);//host to net 16位

   bind(listenfd, ( struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd ,LISTENQ);
    for( ; ; ){
	    len= sizeof(cliaddr);
        connfd =accept(listenfd, (struct sockaddr *)&cliaddr,&len);
        ticks =time(NULL);
       //替代sprintf函数，第二个参数设置的缓冲区大小范围
       printf("connection from %s, port %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff) ),ntohs(cliaddr.sin_port));
       	snprintf(buff, sizeof(buff), "%.24s\r\n",ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}
