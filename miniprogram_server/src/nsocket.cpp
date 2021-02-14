#include "../include/nsocket.h"

//(1)如果在已经处于 ESTABLISHED状态下的socket(一般由端口号和标志符区分）
//调用close(socket)（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket：
void setReusePort(int fd)
{
    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&reuse, sizeof(reuse));
}

ServerSocket::ServerSocket(int port, const char *ip) : mPort(port), mIp(ip)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        std::cout << "creat socket error in file <" << __FILE__ << "> "
                  << "at " << __LINE__ << std::endl;
        exit(0);
    }
    memset(&mAddr, 0, sizeof(mAddr));
    mAddr.sin_family = AF_INET;
    mAddr.sin_port = htons(port);
    if (ip != nullptr)
    {
        inet_pton(AF_INET, ip, &mAddr.sin_addr);
    }
    else
    {
        mAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    setReusePort(fd);
}

void ServerSocket::bind()
{
    int ret = ::bind(fd, (sockaddr *)&mAddr, sizeof(mAddr));
    if (ret == -1)
    {
        std::cout << "bind error in file " << std::endl;
        exit(0);
    }
}

void ServerSocket::listen(int listenQ)
{
    int ret = ::listen(fd, listenQ);
    if (ret == -1)
    {
        std::cout << "listen error in file " << std::endl;
        exit(0);
    }
}

int ServerSocket::accept(sockaddr_in &cliAddr)
{
    socklen_t len = sizeof(cliAddr);
    int clientfd = ::accept(fd, (sockaddr *)&cliAddr, &len);
    if (clientfd < 0)
    {
        std::cout << "accept error in file " << std::endl;
        exit(0);
    }
    return clientfd;
}

ServerSocket::~ServerSocket()
{
    ::close(fd);
}
