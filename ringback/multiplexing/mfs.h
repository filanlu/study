#ifndef _MFS_H
#define _MFS_H
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <netinet/in.h>

#define MAXLINE 4096
#define bzero(ptr ,n) memset(ptr, 0,n);
#define	SA	struct sockaddr
#define	LISTENQ		1024
#define MAXLINE		4096
#define OPEN_MAX    1024/*1024采取保险大小，如果需要更大需要修改系统配置*/

typedef void (Sigfunc)(int);
/************iofunction************/
ssize_t readline(int fd, void *vptr, size_t n);
ssize_t writen(int fd, const void *vptr, size_t n);

/************sinalfunction*********/
Sigfunc *signal(int signo, Sigfunc *func);
void sig_chld(int signo);
#endif
