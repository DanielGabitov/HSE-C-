CFLAGS = -std=c++11 -Wall -Werror -Wextra -Iinclude 

all: hw_02 test_hw_02

hw_02: obj obj/main.o obj/Board.o obj/StdioBoardView.o
	g++ -o  hw_02 obj/main.o obj/Board.o obj/StdioBoardView.o

obj:
	mkdir -p obj

obj/main.o: src/main.cpp include/Board.h include/StdioBoardView.h| obj
	g++ -c -o obj/main.o $(CFLAGS) src/main.cpp

obj/Board.o: src/Board.cpp include/Board.h include/StdioBoardView.h| obj
	g++ -c -o obj/Board.o $(CFLAGS) src/Board.cpp

obj/StdioBoardView.o: src/StdioBoardView.cpp include/StdioBoardView.h include/Board.h | obj
	g++ -c -o  obj/StdioBoardView.o $(CFLAGS) src/StdioBoardView.cpp 

clean:
	rm  -rf hw_02 obj test_hw_02

test_hw_02: obj obj/test.o obj/BoardTest.o obj/Board.o obj/Test.o
	g++ -o  test_hw_02 obj/test.o obj/BoardTest.o obj/Board.o obj/Test.o

obj/test.o: test/test.cpp include/BoardTest.h include/Board.h include/Test.h| obj
	g++ -c -o obj/test.o $(CFLAGS) test/test.cpp

obj/Test.o: test/Test.cpp include/Test.h| obj
	g++ -c -o obj/Test.o $(CFLAGS) test/Test.cpp

obj/BoardTest.o: test/BoardTest.cpp include/BoardTest.h include/Board.h include/Test.h| obj
	g++ -c -o obj/BoardTest.o $(CFLAGS) test/BoardTest.cpp

