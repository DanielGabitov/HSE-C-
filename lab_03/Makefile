FLAGS = -c -Wall -Wextra -Werror -std=c99 -fsanitize=address -g

all: lab_03
	
lab_03: obj obj/main.o obj/clist.o
	gcc  -fsanitize=address obj/clist.o obj/main.o  -o lab_03

obj:
	mkdir obj

obj/main.o: src/main.c obj/clist.o include/clist.h  | obj
	gcc $(FLAGS) -o obj/main.o  src/main.c -Iinclude

obj/clist.o: src/clist.c include/clist.h | obj
	gcc $(FLAGS) -o obj/clist.o src/clist.c -Iinclude

clean:
	rm -rf lab_03 obj
