FLAGS = -c -Wall -Wextra -Werror -std=c99 -fsanitize=address

all: lab_02
	
lab_02: obj obj/str.o obj/test_str.o obj/test.o
	gcc  -fsanitize=address obj/str.o obj/test_str.o obj/test.o -o lab_02

obj:
	mkdir obj

obj/str.o: src/str.c include/str.h| obj
	gcc $(FLAGS) -o obj/str.o  src/str.c -Iinclude

obj/test_str.o: src/test_str.c include/test_str.h include/str.h  | obj
	gcc $(FLAGS) -o obj/test_str.o  src/test_str.c -Iinclude

obj/test.o: src/test.c include/test_str.h  | obj
	gcc $(FLAGS) -o obj/test.o  src/test.c -Iinclude

clean:
	rm -rf lab_02 obj
