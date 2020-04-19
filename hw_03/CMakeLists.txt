cmake_minimum_required(VERSION 3.15)
project(hw_03)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw_03 src/Parser.cpp include/Parser.h src/main.cpp include/HuffmanTree.h include/HuffmanNode.h src/HuffmanNode.cpp src/HuffmanTree.cpp src/Huffman.cpp include/Huffman.h src/HuffmanArchiver.cpp include/HuffmanArchiver.h )