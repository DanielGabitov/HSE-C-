#include "../include/ParserExceptions.h"

ParserExceptions::ParserExceptions(std::string error_message)
    : error_message(error_message)
    {}

const char * ParserExceptions::what() const noexcept{
    return error_message.c_str();
} 