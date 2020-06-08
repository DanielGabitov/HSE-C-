#include <iostream>
#include <matrix.h>
#include <fstream>
#include <vector>

size_t get_index(){
    std::string line;
    std::cin >> line;
    return line[1] - '0';
}

void print_error(const char * error_command){
  std::cout << error_command << '\n';
}

int main(){
    std::vector<Matrix> data(10);
    while (1){
        std::string command;
        std::cin >> command;

        if (command == "load"){
            size_t index = get_index();
            std::string file_name;
            std::cin >> file_name;
            std::ifstream stream;
            stream.open(file_name);
            if (!stream.is_open()){
                std::cout << "LOAD: unable to open file.\n";
                continue;
            }
            try {
                Matrix matrix;
                stream >> data[index];
            }
            catch(const MatrixException &error){
                print_error(error.what());
            }
        }
        else if (command == "print"){
            size_t index = get_index();
            std::cout << data[index];
        }
        else if (command == "elem"){
            size_t index = get_index();
            size_t x, y;
            std::cin >> x >> y;
            try {
                std::cout << data[index].get_elem(x, y) << '\n'; 
            }
            catch(const MatrixException &error){
                print_error(error.what());
            }
        }
        else if (command == "add"){
            size_t index1 = get_index();
            size_t index2 = get_index();
            try {
                data[index1] += data[index2];
            }
            catch(const MatrixException &error){
                print_error(error.what());
            }   
        }
        else if (command == "mul"){
            size_t index1 = get_index();
            size_t index2 = get_index();
            try {
                data[index1] *= data[index2];
            }
            catch(const MatrixException &error){
                print_error(error.what());
            }
        } else if (command == "exit"){
            return 0;
        }
    }
}