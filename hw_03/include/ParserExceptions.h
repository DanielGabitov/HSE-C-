#pragma once

#include <exception>
#include <string>

class ParserExceptions : public std::exception {
public:
    ParserExceptions(std::string error_message);
    const char * what() const noexcept override;
private:
    const std::string error_message;
};