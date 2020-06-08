CFLAGS = -g -Wall -Wextra -Werror -Iinclude -std=c++11

all: lab_13

lab_13: obj obj/main.o include/my_array.h | obj
	g++ -o  lab_13  obj/main.o

obj:
	mkdir -p obj

obj/main.o: src/main.cpp include/my_array.h | obj
	g++ -c -o obj/main.o $(CFLAGS) src/main.cpp

clean:
	rm  -rf lab_13 obj