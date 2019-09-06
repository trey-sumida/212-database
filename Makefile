all: project2

project2: llistmain.o llist.o
	g++ -o project2 llistmain.o llist.o

llistmain.o: llistmain.cpp
	g++ -ansi -pedantic-errors -Wall -c llistmain.cpp

llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall -c llist.cpp
