#include <iostream>
#include <unistd.h>
#include "mfs.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
int main(int argc, char **argv){
    int   sockfd, n;
    char  recvline[MAXLINE +1];
    struct sockaddr_in servaddr;
   //输入格式错误
    if(argc !=2){
	 cout<<"usage :a.out<IPaddress>"<<endl;
        return -1;
    }
    //申请sockfd
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0){
        perror("socket error");
        return -1;
    }
    //memset初始化地址空间
    bzero(&servaddr ,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port =htons(2020);
    //inet_pton是一个IP地址转换函数，可以在将点分文本的IP地址转换为二进制网络字节序”的IP地址,把 argv[1] 转换后存放在 servaddr.sin_addr
    if(inet_pton(AF_INET, argv[1],&servaddr.sin_addr) <=0){
       perror("inet_pton error for %s",argv[1]);
        return -1;
    }
    //参数sockfd 的socket 连至参数serv_addr 指定的网络地址。结构sockaddr请参考bind()。参数addrlen为sockaddr的结构长度。
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) <0){
        perror("connect error");
        return -1;
    }
    while( (n= read(sockfd, recvline, MAXLINE)) >0){
        recvline[n] =0;
        if(fputs(recvline, stdout) ==EOF)
            cout<<"fputs error"<<endl;
    }
    if(n<0)
    cout<<"read error"<<endl;
    exit(0);
}
