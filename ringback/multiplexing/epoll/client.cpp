#include "mfs.h"
#include <iostream>
#include <string>
using namespace std;
void str_cli(int sockfd);
void loginName(string &name);
int main(int argc, char **argv){
    int         sockfd;
    string      nameid;
    socklen_t   socklen;
    sockaddr_in servaddr;
    
    
    if(argc != 2){
        perror ("using client <Ipaddress>");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2020);

    if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr))){
        perror("connect error");
        exit(1);
    }
    cout<<"welcome to chat, press ctrl+d to exit"<<endl;
    loginName(nameid);
    
     
    writen(sockfd, ("id"+nameid).c_str(),nameid.size());
    str_cli(sockfd);
    
}
void loginName(string &name){
    cout<<"please cin you name:";
    cout.flush();
    cin >> name;
}
void str_cli(string  name, int sockfd){
    int     n,maxfd1;
    fd_set  rset;   
    char    buff[MAXLINE]; 

    bool stdineof = false;
    FD_ZERO(&rset);
    
    while(1){
        if(!stdineof){
            FD_SET(fileno(stdin),&rset);
        }
        FD_SET(sockfd, &rset);
        maxfd1 = max(sockfd, fileno(stdin))+1;

        select(maxfd1, &rset, NULL, NULL, NULL);
        
        if(FD_ISSET(sockfd, &rset)){
            if( (n = read(sockfd, buff,MAXLINE)) == 0){
                if(stdineof == 1) 
                    return;   /*normal termination*/
                else {
                    perror("str_cli: server terminated prematurely");
                    exit(1);
                }
            }
            buff[n]='\0';
            cout<<" "<<buff<<endl;
        }
        
         if(FD_ISSET(fileno(stdin), &rset)){
             
            if( (n = read(fileno(stdin), buff+2, MAXLINE)) == 0){
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);/*send FIN*/
                FD_CLR(fileno(stdin), &rset);/*turn off*/
                continue;
            }
            buff[0]= 'm';
            buff[1]= 'g';
            writen(sockfd, buff, n);
        }

    }
}
