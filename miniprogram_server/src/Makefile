all:	main 
vpath %.h ../include

main:main.o HttpServer.o Http.o Timer.o ThreadPool.o nsocket.o Epoll.o wolf.o
	g++ -g main.o HttpServer.o Http.o Timer.o ThreadPool.o nsocket.o Epoll.o wolf.o -lpthread -o main -std=c++11
main.o:main.cpp
	g++ -g -c main.cpp -o main.o -std=c++11
HttpServer.o:HttpServer.cpp 
	g++ -g -c HttpServer.cpp   -o HttpServer.o -std=c++11
Http.o:Http.cpp
	g++ -g -c Http.cpp -o Http.o -std=c++11
Timer.o:Timer.cpp
	g++ -g -c Timer.cpp -o Timer.o -std=c++11
ThreadPool.o:ThreadPool.cpp
	g++ -g -c ThreadPool.cpp -o ThreadPool.o -std=c++11
nsocket.o:nsocket.cpp
	g++ -g -c nsocket.cpp -o nsocket.o -std=c++11
Epoll.o:Epoll.cpp
	g++ -g -c Epoll.cpp -o Epoll.o -std=c++11
wolf.o:wolf.cpp
	g++ -g -c wolf.cpp -o wolf.o -std=c++11
allclean= HttpServer.o ThreadPool.o Timer.o nsocket.o Epoll.o main.o wolf.o Http.o
.PYONY: clean
clean:
	rm $(allclean)


