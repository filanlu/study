#include "mfs.h"
#include <iostream>
using namespace std;

/************iofunction***********/ 
ssize_t readline(int fd, void *vptr, size_t n){
           size_t  nleft;
           ssize_t nread;
           char *  ptr;
           ptr =(char*) vptr;
           nleft = n;
           while(nleft > 0){
                   if( (nread = read(fd, ptr, nleft)) < 0){
                           cout<<nread<<endl;
                          if(errno == EINTR)//中断重新调用read
                                  nread = 0;
                          else return (-1);
                  }else if (!nread)//EOF
                          break;
                  
                  nleft -= nread;
                  ptr   += nread;
                if(ptr[nread-1]='\n')break;//readline function return when meet '\n'
          }
          return (n-nleft);
  }
 ssize_t writen(int fd, void const *vptr, size_t n){
       
          size_t nleft;
          ssize_t nwritten;;
          const char *ptr;
          ptr = (const char *)vptr;
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

/**********Signal function***********/
Sigfunc *signal(int signo, Sigfunc*func){
	struct sigaction act, oact;
        /*
        If  SA_SIGINFO  is specified in sa_flags, then sa_sigaction (instead of
        sa_handler) specifies the signal-handling function  for  signum.   This
        function receives three arguments, as described below.
        */ 
        act.sa_handler =func;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        if(signo == SIGALRM){
                #ifdef SA_INTERRUPT
                act.sa_flags |= SA_INTERRUPT;
                #endif
        }else{
                #ifdef SA_RESTART
                act.sa_flags |= SA_RESTART;
                #endif
        }
        if (sigaction(signo, &act, &oact) < 0)
                return (SIG_ERR);
        return (oact.sa_handler);//返回发生信号时的前一个动作
}
void sig_chld(int signo){
        pid_t pid;
        int stat;
        while( (pid = waitpid(-1, &stat,WNOHANG)) >0 )
        printf ("chaild %d terminated\n", pid);
        return ;
}
