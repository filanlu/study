#ifndef SERVER_H
#define SERVER_H

#include "ThreadPool.h"
#include "nsocket.h"
#include "Epoll.h"
#include "Timer.h"
#include "wolf.h"
#include "Http.h"
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/sendfile.h>
#include <unordered_map>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

const string WOLFCREATE = "WOLFCREATE";
const string WOLFENTER = "WOLFENTER";

class HttpServer
{
private:
    string m_status;
    ServerSocket m_serverSocket;
    char *m_buff;
    Epoll m_epoll;
    unordered_map<int, wolf> m_room; //房间号，狼人房。
    TimerManager M_timerManager;
    std::thread timerThread;
public:
    explicit HttpServer(int port = 80, const char *ip = nullptr);
    void run();

    //void ans_request(ClientSocket&);
    void do_request(int fd);
    unordered_map<string, int> json_parse(char *buf);
    int parse_request(int fd);
    void room_pop(int id);
    ~HttpServer();
};

#endif