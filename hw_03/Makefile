CFLAGS = -std=c++17 -Wall -Werror -Wextra -Iinclude 

all: hw_03 test_hw_03


hw_03: obj obj/main.o obj/Huffman.o obj/HuffmanArchiver.o obj/HuffmanTree.o obj/HuffmanNode.o obj/Parser.o obj/ParserExceptions.o
	g++ -O3 -o  hw_03 obj/main.o obj/Huffman.o obj/HuffmanArchiver.o obj/HuffmanTree.o obj/HuffmanNode.o obj/Parser.o obj/ParserExceptions.o

obj:
	mkdir -p obj

obj/main.o: src/main.cpp obj/Parser.o  obj/Huffman.o include/Huffman.h | obj
	g++ -O3 -c -o obj/main.o $(CFLAGS) src/main.cpp

obj/Parser.o: src/Parser.cpp obj/ParserExceptions.o include/ParserExceptions.h include/Huffman.h | obj
	g++ -O3 -c -o obj/Parser.o $(CFLAGS) src/Parser.cpp

obj/ParserExceptions.o: src/ParserExceptions.cpp | obj
	g++ -O3 -c -o obj/ParserExceptions.o $(CFLAGS) src/ParserExceptions.cpp

obj/Huffman.o: src/Huffman.cpp include/Huffman.h | obj
	g++ -O3 -c -o obj/Huffman.o $(CFLAGS) src/Huffman.cpp

obj/HuffmanArchiver.o: src/HuffmanArchiver.cpp obj/HuffmanTree.o include/HuffmanTree.h | obj
	g++ -O3 -c -o obj/HuffmanArchiver.o $(CFLAGS) src/HuffmanArchiver.cpp

obj/HuffmanTree.o: src/HuffmanTree.cpp obj/HuffmanNode.o include/HuffmanNode.h | obj
	g++ -O3 -c -o obj/HuffmanTree.o $(CFLAGS) src/HuffmanTree.cpp

obj/HuffmanNode.o: src/HuffmanNode.cpp | obj
	g++ -O3 -c -o obj/HuffmanNode.o $(CFLAGS) src/HuffmanNode.cpp


test_hw_03: obj obj/TestMain.o obj/TestEndToEnd.o obj/TestCompression.o obj/TestHuffmanTree.o obj/Huffman.o obj/HuffmanArchiver.o obj/HuffmanTree.o obj/HuffmanNode.o include/doctest.h
	g++ -O3 -o test_hw_03 $(CFLAGS) obj/TestMain.o obj/TestEndToEnd.o obj/TestHuffmanTree.o obj/TestCompression.o obj/Huffman.o obj/HuffmanArchiver.o obj/HuffmanTree.o obj/HuffmanNode.o

obj/TestMain.o: obj test/TestMain.cpp include/doctest.h | obj
	g++ -O3 -c -o obj/TestMain.o $(CFLAGS) test/TestMain.cpp

obj/TestEndToEnd.o: obj test/TestEndToEnd.cpp include/Huffman.h include/doctest.h | obj
	g++ -O3 -c -o obj/TestEndToEnd.o $(CFLAGS) test/TestEndToEnd.cpp

obj/TestHuffmanTree.o: obj test/TestHuffmanTree.cpp include/HuffmanTree.h include/doctest.h | obj
	g++ -O3 -c -o obj/TestHuffmanTree.o $(CFLAGS) test/TestHuffmanTree.cpp

obj/TestCompression.o: obj test/TestCompression.cpp include/HuffmanArchiver.h include/doctest.h | obj
	g++ -O3 -c -o obj/TestCompression.o $(CFLAGS) test/TestCompression.cpp

clean:
	rm -rf hw_03 test_hw_03 obj