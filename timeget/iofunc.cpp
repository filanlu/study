#include "iofunc.h"
ssize_t readn(int fd, void *vptr, size_t n){
	size_t  nleft;
	ssize_t nread;
	char *  ptr;
	ptr = vptr;
	nleft = n;
	while(nleft > 0){
		if( (nread = read(fd, ptr, nleft)) < 0){
			if(errno == EINTR)//中断重新调用read
				nread = 0;
			else return (-1);
		}else if (nread == 0)
			break;
		nleft -= nread;
		ptr   += nread; 
	}
	return (n-left);
}

ssize_t writen(int fd, const void *vptr, size_t n){
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	ptr = vptr;
	nleft = n;
	while(nleft > 0){
		if( (nwritten = write(fd, ptr, nleft)) <=0){
		if(nwritten < 0 && errno == EINTR)
			nwritten = 0;
		else return(-1);
		}
		nleft -= nwritten;
		ptr +=nwritten;
	}
	return n;
}
