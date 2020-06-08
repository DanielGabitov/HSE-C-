CFLAGS = -g -fsanitize=address -Iinclude 

all: lab_09

lab_09: obj obj/main.out obj/matrix.out obj/shared_ptr.out 
	g++ -o  lab_09 obj/main.out obj/matrix.out obj/shared_ptr.out -lasan

obj:
	mkdir -p obj

obj/main.out: src/main.cpp include/matrix.hpp include/shared_ptr.hpp | obj
	g++ -c -o obj/main.out $(CFLAGS) src/main.cpp

obj/matrix.out: src/matrix.cpp include/matrix.hpp include/shared_ptr.hpp | obj
	g++ -c -o obj/matrix.out $(CFLAGS) src/matrix.cpp

obj/shared_ptr.out: src/shared_ptr.cpp include/shared_ptr.hpp include/matrix.hpp | obj
	g++ -c -o  obj/shared_ptr.out $(CFLAGS) src/shared_ptr.cpp 

clean:
	rm  -rf lab_09 obj