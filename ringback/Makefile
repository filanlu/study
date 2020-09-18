all:	ringbackserv ringbackcli
ringbackcli:mfs.o ringbackcli.o
	g++ -g  mfs.o ringbackcli.o -o ringbackcli
ringbackserv:mfs.o ringbackserv.o
	g++ -g mfs.o ringbackserv.o -o ringbackserv
ringbackserv.o:ringbackserv.cpp
	g++ -g -c ringbackserv.cpp
ringbackcli.o:ringbackcli.cpp
	g++  -g -c ringbackcli.cpp

mfs.o:mfs.cpp
	g++ -g -c mfs.cpp
allclean= mfs.o ringbackserv.o ringbackcli.o
.PYONY:	clean
clean:
	rm  $(allclean)
