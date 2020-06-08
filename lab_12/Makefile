CFLAGS=-c -std=c++17 -Wall -Wall -Wextra -Werror -Iinclude 
all: lab_12

lab_12: obj/main.o       
	g++ obj/main.o -o lab_12
obj: 
	mkdir obj

obj/main.o: src/main.cpp include/my_vector_impl.h | obj
	g++ $(CFLAGS) src/main.cpp -o obj/main.o 

clean:
	rm -rf obj lab_12