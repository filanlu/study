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

#define MAXLINE 4096
#define bzero(ptr ,n) memset(ptr, 0,n);
#define	SA	struct sockaddr
#define	LISTENQ		1024
#define MAXLINE		4096


typedef void (Sigfunc)(int);
/************iofunction************/
ssize_t readline(int fd, void *vptr, size_t n);
ssize_t writen(int fd, const void *vptr, size_t n);

/************sinalfunction*********/
Sigfunc *signal(int signo, Sigfunc *func);
void sig_chld(int signo);
#endif
