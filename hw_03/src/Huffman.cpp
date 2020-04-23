#include <iostream>
#include "../include/Huffman.h"
#include <cassert>
const int BYTE_SIZE = 8;


void Huffman::save(std::istream &input_stream, std::ostream &output_stream){

    std::unordered_map<char, int32_t> frequency_table;
    std::vector<char> unique_bytes;
    int32_t number_of_bytes_to_compress = read_and_make_ftable(unique_bytes, frequency_table, input_stream);

    if (number_of_bytes_to_compress == 0){
        std::cout << 0 << '\n' << 0 << '\n' << 0 << '\n';
        return;
    }

    int32_t frequency_table_size = write_ftable(frequency_table, output_stream, unique_bytes);

    HuffmanTree tree(unique_bytes, frequency_table);
    HuffmanArchiver archiver;
    std::unordered_map<char, std::string> new_table = archiver.compress(tree);

    write_binary(number_of_bytes_to_compress, output_stream);
    int32_t written_bytes_amount = write_compressed_data(input_stream, output_stream, new_table);

    // print parameters. + 1 coz of writing amount of bytes to compress.
    std::cout << number_of_bytes_to_compress << '\n'
              << written_bytes_amount        << '\n'
              << frequency_table_size + 1    << '\n';

    input_stream.seekg(std::ios_base::beg);

    return; 
}

// Reads data and stores useful staff in given data structures.Return number of bytes.
int32_t Huffman::read_and_make_ftable(std::vector<char> &unique_bytes, std::unordered_map<char, int32_t> &frequency_table, std::istream &input_stream){
    char byte;
    int32_t number_of_bytes = 0;
    while (input_stream.read(&byte, sizeof(char))){
        number_of_bytes++;
        if (frequency_table.find(byte) == frequency_table.end()){
            unique_bytes.push_back(byte);
            frequency_table[byte] = 1;
        } else {
            frequency_table[byte]++;
        }
    }
    // Вернуть обратно указатель на начало файла.
    input_stream.clear();
    input_stream.seekg(std::ios_base::beg);
    return number_of_bytes;
}

template<typename T>
void Huffman::write_binary(const T &item, std::ostream &output_stream){
    output_stream.write(reinterpret_cast<const char *>(&item), sizeof(item));
}

template<typename T>
void Huffman::read_binary(T &item, std::istream &input_stream){
    input_stream.read(reinterpret_cast<char *>(&item), sizeof(item));
}

// Writes ftable to decode it if needed
int32_t Huffman::write_ftable(const std::unordered_map<char, int32_t> &frequency_table, std::ostream &output_stream,
            const std::vector<char> &unique_bytes){

    int32_t additional_data = 0;

    write_binary(static_cast<int32_t>(frequency_table.size()), output_stream);
    additional_data += sizeof(int32_t);

    for (size_t i = 0; i < unique_bytes.size(); i++){
        write_binary(unique_bytes[i], output_stream);
        write_binary(frequency_table.find(unique_bytes[i])->second, output_stream);

        additional_data += (sizeof(char) + sizeof(int32_t));
    }
    return additional_data;
}

int32_t Huffman::write_compressed_data(std::istream &input_stream,
            std::ostream &output_stream, const std::unordered_map<char, std::string> &new_bytes_table){

    char byte;
    int position = 0;
    char to_write = 0;
    int32_t bytes_amount = 0;
    while (input_stream.read(&byte, sizeof(char))){
        std::string new_byte = new_bytes_table.find(byte)->second;
        for (char symb : new_byte){
            to_write |= (int)(symb == '1') << position++;
            if (position == BYTE_SIZE){
                write_binary(to_write, output_stream);
                to_write = 0;
                position = 0;
                bytes_amount++;
            }
        }
    }
    // Если биты не делятся на BYTE_SIZE, записываем их набиваем остаток нулями. 
    if (position){
        write_binary(to_write, output_stream);
        bytes_amount++;
    }

    input_stream.seekg(std::ios::beg);
    input_stream.clear();

    return bytes_amount;
}

int32_t Huffman::read_ftable(std::vector<char> &unique_bytes, 
        std::unordered_map<char, int32_t> &frequency_table, std::istream &input_stream){

    int32_t amount_of_data = 0;
    int32_t table_size, frequency;
    char byte;
    input_stream.read((char *)&table_size, sizeof(int32_t));

    if (input_stream.eof()){
        return 0;
    }

    amount_of_data += sizeof(int32_t);
    for (int32_t i = 0; i < table_size; i++){
        input_stream.read((char *)&byte, sizeof(char));
        input_stream.read((char *)&frequency, sizeof(int32_t));

        frequency_table[byte] = frequency;
        unique_bytes.push_back(byte);

        amount_of_data += sizeof(char) + sizeof(int32_t);
    }
    return amount_of_data;
}

int32_t Huffman::write_extracted_data(std::unordered_map<std::string, char> &bytes_table, int32_t bytes_amount,
                std::istream &input_stream, std::ostream &output_stream){

    char byte;
    input_stream.read(&byte, sizeof(char));
    std::string code;
    int32_t bytes_written = 0;
    int32_t bytes_were_read = 1;
    int position = 0;
    while (true){
        if (position == BYTE_SIZE){
            input_stream.read(&byte, sizeof(char));
            position = 0;
            bytes_were_read++;
        }
        code.push_back(((byte >> position++) & 1) + '0') ;
        if (bytes_table.find(code) == bytes_table.end()){
            continue;
        }
        write_binary(bytes_table[code], output_stream);
        code = "";
        if (++bytes_written == bytes_amount){
            break;
        }
    }

    input_stream.seekg(std::ios::beg);
    input_stream.clear();

    return bytes_were_read;
}


void Huffman::load(std::istream &input_stream, std::ostream &output_stream){

    std::unordered_map<char, int32_t> frequency_table;
    std::vector<char> unique_bytes;
    int32_t fr_table_size = read_ftable(unique_bytes, frequency_table, input_stream);

    if (fr_table_size == 0){
        std::cout << 0 << '\n' << 0 << '\n' << 0 << '\n';
        return;
    }

    int32_t bytes_amount;
    read_binary(bytes_amount, input_stream);

    HuffmanTree tree(unique_bytes, frequency_table);
    HuffmanArchiver archiver;
    std::unordered_map<std::string, char> extracted_table = archiver.extract(tree);
    int32_t bytes_read = write_extracted_data(extracted_table, bytes_amount, input_stream, output_stream);

    // print parameters. + 1 coz of writing amount of bytes to compress.
    std::cout << bytes_read         << '\n'
              << bytes_amount       << '\n'
              << fr_table_size + 1  << '\n';

    input_stream.seekg(std::ios_base::beg);

    return;
}