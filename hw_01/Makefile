FLAGS = -c -Wall -Wextra -Werror -std=c99 -fsanitize=address

all: hw_01
	
hw_01: obj obj/main.o obj/bmp.o  
	gcc  -fsanitize=address obj/main.o  obj/bmp.o  -o hw_01

obj:
	mkdir obj

obj/main.o: src/main.c  include/bmp.h  | obj
	gcc $(FLAGS) src/main.c -o obj/main.o -Iinclude	

obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc $(FLAGS) src/bmp.c -o obj/bmp.o -Iinclude

clean:
	rm -rf new_lena.bmp hw_01 obj
