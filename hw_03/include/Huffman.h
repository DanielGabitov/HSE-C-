#pragma once

#include "../include/HuffmanArchiver.h"

class Huffman{
public:
    void save(std::ifstream &input_stream, std::ofstream &output_stream);
    void load(std::ifstream &input_stream, std::ofstream &output_stream);
private:
    int32_t read_and_make_ftable(std::vector<char> &unique_bytes, 
        std::unordered_map<char, int32_t> &table, std::ifstream &input_stream);

    int32_t write_ftable(std::unordered_map<char, int32_t> &frequency_table, std::ofstream &output_stream,
                         std::vector<char> &unique_bytes);

    int32_t write_compressed_data(std::ifstream &input_stream,
            std::ofstream &output_stream, std::unordered_map<char, std::string> &new_bytes_table);

    template<typename T>
    void write_binary(const T &item, std::ofstream &output_stream);

    template<typename T>
    void read_binary(T &item, std::ifstream &output_stream);

    int32_t read_ftable(std::vector<char> &unique_bytes, 
        std::unordered_map<char, int32_t> &table, std::ifstream &input_stream);
    
    int32_t write_extracted_data(std::unordered_map<std::string, char> &bytes_table,
            int32_t bytes_amount, std::ifstream &input_stream, std::ofstream &output_stream);
};

