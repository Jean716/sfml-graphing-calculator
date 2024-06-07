#ifndef MISSINGPARAN_H
#define MISSINGPARAN_H

#include <exception>
#include <string>

class MissingParan : public exception
    {
    public:
        MissingParan(const string& message) : _message(message) {}

        virtual const char* what() const noexcept override
            {
            return _message.c_str();
            }

    private:
        string _message;
    };

#endif // MISSINGPARAN_H