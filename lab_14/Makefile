CFLAGS = -g -Wall -Wextra -Werror -Iinclude -std=c++11

all: lab_14

lab_14: obj obj/main.out obj/matrix.out
	g++ -o  lab_14 obj/main.out obj/matrix.out

obj:
	mkdir -p obj

obj/main.out: src/main.cpp include/matrix.h | obj
	g++ -c -o obj/main.out $(CFLAGS) src/main.cpp

obj/matrix.out: src/matrix.cpp include/matrix.h | obj
	g++ -c -o obj/matrix.out $(CFLAGS) src/matrix.cpp

clean:
	rm  -rf lab_14 obj