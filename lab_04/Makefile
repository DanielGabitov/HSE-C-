FLAGS = -c -Wall -Wextra -Werror -std=c99 -fsanitize=address -g

all: lab_04
	
lab_04: obj obj/main.o obj/mergesort.o
	gcc  -fsanitize=address obj/mergesort.o obj/main.o  -o lab_04

obj:
	mkdir obj

obj/main.o: src/main.c obj/mergesort.o include/mergesort.h  | obj
	gcc $(FLAGS) -o obj/main.o  src/main.c -Iinclude

obj/mergesort.o: src/mergesort.c include/mergesort.h | obj
	gcc $(FLAGS) -o obj/mergesort.o src/mergesort.c -Iinclude

clean:
	rm -rf lab_04 obj
