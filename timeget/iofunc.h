#ifndef _IOFUNC_H
#define _IOFUNC_H
#include<sys/types.h>
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t writen(int fd,const void *vptr, size_t n);
#endif
