all:	server.out client.out

client.out:mfs.o client.o
	g++ -g  mfs.o client.o -o client.out
server.out:mfs.o server.o
	g++ -g mfs.o server.o -o server.out

server.o:server.cpp
	g++ -g -c server.cpp
client.o:client.cpp
	g++  -g -c client.cpp

mfs.o:mfs.cpp
	g++ -g -c mfs.cpp

allclean= mfs.o server.o client.o server.out client.out
.PYONY:	clean
clean:
	rm  $(allclean)
