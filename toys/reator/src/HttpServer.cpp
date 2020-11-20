#include "../include/HttpServer.h"

void HttpServer::ans_request(int sockfd)
{
    while (1)
    {   
        int n = recv(sockfd, buff, 1024, 0);
        
        if (n <= 0)
        {   
            if(n == 0)  break;
            //如果你连续做read操作而没有数据可读。
            //此时程序不会阻塞起来等待数据准备就绪返回，read函数会返回一个错误EAGAIN，提示你的应用程序现在没有数据可读请稍后再试。
            if (errno == EAGAIN) 
            {
                //printf("read later\n");
                break;
            }
            else exit(EXIT_FAILURE);
        }
        buff[n] = '\0';       
        std::cout << buff << std::endl;
        //memset(buff,0,1024);
        char response[512]="HTTP/1.0 200 ok\r\ncontent-type: text/html; charset=utf-8\r\nconnection: close\r\n\r\n";
        send(sockfd,response,sizeof(response),0);
        // std::cout << buff << std::endl;
       
       int fd = open("login.html",O_RDONLY);//消息体
        sendfile(sockfd,fd,NULL,2500);//零拷贝发送消息体
        close(fd);
        //  std::ifstream infile; 
        //  infile.open("login.html"); 
        //  while(infile.getline(buff,1024)){
            
        //     send(sockfd,buff,1024,0);
        //     //memset(buff,0, 1024);
        // }
        // infile.close();

    }
        std::cout<<"bk6"<<std::endl;


    //std::cout<< "我出来了"<<std::endl;
}
HttpServer::~HttpServer()
{
}
void HttpServer::run()
{
    int sockfd;
    
    ThreadPool threadPool(2);
    threadPool.start();

    epoll.addSock(serverSocket.fd, true); //添加监听描述符
    while (true)
    {   //std::cout<<"wait阻塞"<< std::endl;
        int nready = epoll.wait();
        //std::cout<<"我进来了"<< std::endl;
        for (int n = 0; n < nready; ++n)
        {   
            if (epoll.getEvent(n).data.fd == serverSocket.fd)
            {   sockaddr_in cliAddr;
                sockfd = serverSocket.accept(cliAddr);
                printf("来自 %s, port: %d 的连接\n",
                       inet_ntop(AF_INET, &cliAddr.sin_addr, buff, sizeof(buff)), ntohs(cliAddr.sin_port));
                fcntl(sockfd,F_SETFL,O_NONBLOCK);
                epoll.addSock(sockfd);
            }
            else{ 
                //std::cout<<(int)epoll.getEvent(n).data.fd<<std::endl;     
                Task task(std::bind(&HttpServer::ans_request, this, (int)epoll.getEvent(n).data.fd) ,(int)epoll.getEvent(n).data.fd);
                threadPool.push_task(task);
                epoll.delcount();
        }
    }
}
}