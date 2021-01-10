#include "../include/HttpServer.h"

 unordered_map<string, int> HttpServer::json_parse(char *buf)
{
    unordered_map<string, int> res;
    while (*buf != '}')
    {
        buf += 2;
        string key;
        while (*buf != '}' && *buf != '"')
        {
            key += *(buf++);
        }
        // cout<<"key:" <<key<<endl;
        buf += 2;
        string value;
        while (*buf != '}' && *buf != ',')
        {
            value += *(buf++);
        }
        // if(key == "min") cout<<" flag:"<< *buf<<endl;
        res[key] = std::stoi(value);
        // cout<<"value:" <<value<<endl;
    }
    for (auto r : res)
    {
        cout << r.first << ":" << r.second << endl;
    }
    return res;
}
int HttpServer::parse_request(int sockfd)
{
    char *buf = buff;
    string type;
    while (*buf != '/')
    {
        ++buf;
    }
    ++buf;
    while (*buf != ' ')
    {
        type += *buf;
        ++buf;
    }
    cout << "type: " << type << endl;
    if (type != WOLFCREATE && type != WOLFENTER)
    {
        status = "404 Not Found";
        return -1;
    }
    else
    {
        status = "200 OK";
    }
    while (*buf != LINE_END)
    {
        if (*buf == '\r' && *(buf + 1) == '\n')
        {
            if (*(buf + 2) == '\r' && *(buf + 3) == '\n')
                break;
        }
        ++buf;
    }

    buf = buf + 4;
    //create room
    if (type == WOLFCREATE)
    {   
        
        room[sockfd] = wolf(json_parse(buf));
        return 0;
    }
    //enter room
    else if(type == WOLFENTER){
        cout <<"enter data"<<buf<<endl;
        int roomId = json_parse(buf)["roomId"];

        return roomId;
    }else return -1; 
    
}
void HttpServer::do_request(int sockfd)
{
    while (1)
    {
        int n = recv(sockfd, buff, 1024, 0);

        if (n <= 0)
        {
            if (n == 0)
                break;
            //如果你连续做read操作而没有数据可读。
            //此时程序不会阻塞起来等待数据准备就绪返回，read函数会返回一个错误EAGAIN，提示你的应用程序现在没有数据可读请稍后再试。
            if (errno == EAGAIN)
            {
                break;
            }
            else
                exit(EXIT_FAILURE);
        }
        buff[n] = LINE_END;
        std::cout << buff << std::endl;
    
        int pr = parse_request(sockfd);

        

        if(pr == -1) {
            cout<<"error request"<<endl;
            close(sockfd);
        }
        //create room 
        else if(pr == 0){
            
            string message =  Http:: response("roomId", sockfd);
            send(sockfd, message.c_str(), message.size(), 0);
        }
        //enter room
        else{          
            string shenfen = room[pr].get_card();
            if(!room[pr].size()){
                delete_room(pr, room);
            }
            string message = Http:: response("shenfen", shenfen);
            
            send(sockfd, message.c_str(), message.size(), 0);
        }
        
    }
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
    { 
        int nready = epoll.wait();
      
        for (int n = 0; n < nready; ++n)
        {
            if (epoll.getEvent(n).data.fd == serverSocket.fd)
            {
                sockaddr_in cliAddr;
                sockfd = serverSocket.accept(cliAddr);

                printf("来自 %s, port: %d 的连接\n",
                       inet_ntop(AF_INET, &cliAddr.sin_addr, buff, sizeof(buff)), ntohs(cliAddr.sin_port));

                fcntl(sockfd, F_SETFL, O_NONBLOCK);
                epoll.addSock(sockfd);
            }
            else
            {                
                Task task(std::bind(&HttpServer::do_request, this, (int)epoll.getEvent(n).data.fd), (int)epoll.getEvent(n).data.fd);
                threadPool.push_task(task);
                epoll.delcount();
            }
        }
    }
}