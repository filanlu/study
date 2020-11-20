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
    if (type != CREATE && type != ENTER)
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
    if (type == CREATE)
    {   
        room[sockfd]=wolf(json_parse(buf));
        return 0;
    }
    //enter room
    else{
        cout <<"enter data"<<buf<<endl;
        int roomId = json_parse(buf)["roomId"];

        return roomId;
    }
    
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
            string response = "HTTP/1.1 200 OK\r\n";
            response += " Accept-Control-Allow-Origin:*\r\n";
            //response += " Content-Encoding:deflate\r\n";
            response += "Cache-Control:no-cache\r\n";
            response += "Content-Type: application/json\r\n"; 
            string content_length ="Content-Length: "+ std::to_string( std::to_string(sockfd).size()+11) +CR+LF+CR+LF;
            response += content_length+ "{\"roomId\":"+std::to_string(sockfd)+"}";
            cout<<endl<<"响应报文："<<endl<<response<<endl;
            send(sockfd, response.c_str(), response.size(), 0);
        }
        //enter room
        else{
            string response = "HTTP/1.1 200 OK\r\n";
            response += " Accept-Control-Allow-Origin:*\r\n";
            //response += " Content-Encoding:deflate\r\n";
            response += "Cache-Control:no-cache\r\n";
            response += "Content-Type: application/json\r\n";    
            cout<<"1"<<endl;
            string shenfen = room[pr].get_card();
            string content_length = "Content-Length: "+ std::to_string(15 + shenfen.size()) +CR+LF+CR+LF;
            cout<<"2"<<endl;
            response += content_length +"{\"shenfen\": \"" + shenfen + "\"}";
            cout<<endl<<"响应报文："<<endl<<response<<endl;
            send(sockfd, response.c_str(), response.size(), 0);
        }
        // char response[512] = "HTTP/1.1 200 OK\r\ncontent-length: 2160\r\ncontent-type: text/html\r\ncharset=utf-8\r\nconnection: close\r\n\r\n";

        // int fd = open("login.html", O_RDONLY); //消息体
        // sendfile(sockfd, fd, NULL, 2160);      //零拷贝发送消息体
        // close(fd);
        //  std::ifstream infile;
        //  infile.open("login.html");
        //  while(infile.getline(buff,1024)){

        //     send(sockfd,buff,1024,0);
        //     //memset(buff,0, 1024);
        // }
        // infile.close();
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
    { //std::cout<<"wait阻塞"<< std::endl;
        int nready = epoll.wait();
        //std::cout<<"我进来了"<< std::endl;
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
                //std::cout<<(int)epoll.getEvent(n).data.fd<<std::endl;
                Task task(std::bind(&HttpServer::do_request, this, (int)epoll.getEvent(n).data.fd), (int)epoll.getEvent(n).data.fd);
                threadPool.push_task(task);
                epoll.delcount();
            }
        }
    }
}