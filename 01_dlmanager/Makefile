objects = main.o link.o
link_libs= -lncurses -lcurl
name = main

all: $(objects)
	g++ -o $(name) $(link_libs) $(objects)
main.o: main.cpp main.hpp
	g++ -c main.cpp
link.o: link.cpp link.hpp
	g++ -c link.cpp
curs_handler.o: curs_handler.cpp curs_handler.hpp
clean:
	rm *.o $(name)
