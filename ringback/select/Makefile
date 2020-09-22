all:	selectserv selectcli
selectcli:mfs.o selectcli.o
	g++ -g  mfs.o selectcli.o -o selectcli
selectserv:mfs.o selectserv.o
	g++ -g mfs.o selectserv.o -o selectserv
selectserv.o:selectserv.cpp
	g++ -g -c selectserv.cpp
selectcli.o:selectcli.cpp
	g++  -g -c selectcli.cpp

mfs.o:mfs.cpp
	g++ -g -c mfs.cpp
allclean= mfs.o selectserv.o selectcli.o
.PYONY:	clean
clean:
	rm  $(allclean)
