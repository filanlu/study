#include"../include/HttpServer.h"

#include <string>
#include <unistd.h>
#include <iostream>

int main(int argc, char**argv){
    // char *buff;
    // if((buff = getcwd(NULL, 0)) == NULL){
    //     perror("getcwd error");
    // }
    // else {
    //     printf("%s", buff);
    //     free(buff);

    // }
    HttpServer httpServer(2020);
    httpServer.run();
}