#include "mfs.h"
#include <iostream>
using namespace std;
void str_cli(FILE *fp, int sockfd){
    int     maxfdp1, stdineof;
    fd_set  rset;
    char    buf[MAXLINE];
    int     n;
    
    stdineof = 0;
    FD_ZERO(&rset);
    for(; ;){
        if (!stdineof)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd,&rset);
        maxfdp1 = max(fileno(fp), sockfd)+1;
        select(maxfdp1, &rset, NULL, NULL, NULL);
        
        if(FD_ISSET(sockfd, &rset)){
            if( (n = read(sockfd, buf,MAXLINE)) == 0){
                if(stdineof == 1) 
                    return;   /*normal termination*/
                else {
                    perror("str_cli: server terminated prematurely");
                    exit(1);
                }
            }
            buf[n]='\0';
            cout<<"receive: "<<buf<<endl;
        }
        if(FD_ISSET(fileno(fp), &rset)){
            if( (n = read(fileno(fp), buf, MAXLINE)) == 0){
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);/*send FIN*/
                FD_CLR(fileno(fp), &rset);/*turn off*/
                continue;
            }
            writen(sockfd, buf, n);
        }
    }
}
int main (int argc, char **argv){
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
   cout << "connect error"<< endl;
    str_cli(stdin, sockfd);

    exit(0);
}
