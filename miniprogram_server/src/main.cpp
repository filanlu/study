#include"../include/HttpServer.h"

#include <string>
#include <unistd.h>
#include <iostream>

int main(int argc, char**argv){
    HttpServer httpServer(2020);
    httpServer.run();
}