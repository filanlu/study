#include "mfs.h"
#include <iostream>
using namespace std;
int main()
{
    int i, maxi, listenfd, connfd, sockfd;
    socklen_t clilen;
    int nready;
    ssize_t n;
    char buff[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    struct pollfd client[OPEN_MAX];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2020);

    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;

    for (i = 1; i < OPEN_MAX; ++i) /*初始化其他空位*/
        client[i].fd = -1;
    maxi = 0; /*client 里的最大下标*/

    for (;;)
    {
        nready = poll(client, maxi + 1, -1);

        if (client[0].revents & POLLRDNORM)
        {

            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (SA *)&cliaddr, &clilen);

            for (i = 1; i < OPEN_MAX; ++i)
            {

                if (client[i].fd < 0)
                {
                    client[i].fd = connfd;
                    client[i].events = POLLRDNORM;
                    printf("connection from %s, port %d\n",
                           inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));

                    break;
                }
            }
            if (i == OPEN_MAX)
            {
                cout << "too many client" << endl;
                continue;
            }
            if (i > maxi)
                maxi = i;
            if (--nready <= 0)
                continue;
        }

        for (i = 1; i <= maxi; i++)
        { /*检查所有描述符是否有数据*/
            if ((sockfd = client[i].fd) < 0)
                continue;
            if (client[i].revents & (POLLRDNORM | POLLERR))
            {
               
                if ((n = read(sockfd, buff, MAXLINE)) < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        /*connection reset by client*/
                        close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                    {
                        perror("read error");
                        exit(1);
                    }
                }
                else if (n == 0)
                {
                    close(sockfd);
                }
                else
                {

                    buff[n] = '\0';
                    cout << buff << endl;
                    writen(sockfd, buff, n);
                }
                if (--nready <= 0)
                    break;
            }
        }
    }
}