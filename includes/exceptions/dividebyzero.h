#ifndef DIVIDEBYZERO_H
#define DIVIDEBYZERO_H

#include <exception>
#include <string>

class DivideByZero : public std::exception
    {
    public:
        DivideByZero(const std::string& message) : _message(message) {}

        virtual const char* what() const noexcept override
            {
            return _message.c_str();
            }

    private:
        std::string _message;
    };

#endif // DIVIDEBYZERO_H


