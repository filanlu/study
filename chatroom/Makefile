all:	server client
client:mfs.o client.o
	g++ -g  mfs.o client.o -o client
server:mfs.o server.o
	g++ -g mfs.o server.o -o server
server.o:server.cpp
	g++ -g -c server.cpp
client.o:client.cpp
	g++  -g -c client.cpp

mfs.o:mfs.cpp
	g++ -g -c mfs.cpp
allclean= mfs.o server.o client.o
.PYONY:	clean
clean:
	rm  $(allclean)
