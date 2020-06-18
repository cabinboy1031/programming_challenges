objects = main.o link.o
link_libs= -lncurses -lcurl
name = main

all: $(objects)
	g++ -o $(name) $(link_libs) $(objects)
main.o: main.cpp main.h
	g++ -c main.cpp
link.o: link.cpp link.h
	g++ -c link.cpp
clean:
	rm *.o $(name)
