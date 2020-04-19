CFLAGS = -std=c++17 -Wall -Werror -Wextra -Iinclude 

all: hw_03

hw_03: obj obj/main.o obj/Huffman.o obj/HuffmanArchiver.o obj/HuffmanTree.o obj/HuffmanNode.o obj/Parser.o
	g++ -o  hw_03 obj/main.o obj/Huffman.o obj/HuffmanArchiver.o obj/HuffmanTree.o obj/HuffmanNode.o obj/Parser.o

obj:
	mkdir -p obj

obj/main.o: src/main.cpp obj/Parser.o  obj/Huffman.o include/Huffman.h | obj
	g++ -c -o obj/main.o $(CFLAGS) src/main.cpp

obj/Parser.o: src/Parser.cpp include/Huffman.h | obj
	g++ -c -o obj/Parser.o $(CFLAGS) src/Parser.cpp

obj/Huffman.o: src/Huffman.cpp include/Huffman.h | obj
	g++ -c -o obj/Huffman.o $(CFLAGS) src/Huffman.cpp

obj/HuffmanArchiver.o: src/HuffmanArchiver.cpp obj/HuffmanTree.o include/HuffmanTree.h | obj
	g++ -c -o obj/HuffmanArchiver.o $(CFLAGS) src/HuffmanArchiver.cpp

obj/HuffmanTree.o: src/HuffmanTree.cpp obj/HuffmanNode.o include/HuffmanNode.h | obj
	g++ -c -o obj/HuffmanTree.o $(CFLAGS) src/HuffmanTree.cpp

obj/HuffmanNode.o: src/HuffmanNode.cpp | obj
	g++ -c -o obj/HuffmanNode.o $(CFLAGS) src/HuffmanNode.cpp

clean:
	rm -rf hw_03 obj