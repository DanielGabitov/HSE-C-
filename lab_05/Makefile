FLAGS = -c -Wall -Wextra -Werror -std=c99 -fsanitize=address

all: lab_05
	
lab_05: obj obj/main.o obj/point_list.o obj/clist.o 
	gcc  -fsanitize=address obj/main.o  obj/point_list.o obj/clist.o  -o lab_05

obj:
	mkdir obj

obj/main.o: src/main.c  include/clist.h include/point_list.h    | obj
	gcc $(FLAGS) -o obj/main.o  src/main.c -Iinclude	

obj/clist.o: src/clist.c include/clist.h | obj
	gcc $(FLAGS) -o obj/clist.o src/clist.c -Iinclude

obj/point_list.o: src/point_list.c include/point_list.h include/clist.h | obj
	gcc $(FLAGS) -o obj/point_list.o src/point_list.c  -Iinclude

clean:
	rm -rf lab_05 out.txt out.bin obj
