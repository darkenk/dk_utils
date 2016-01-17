#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception(const std::string& msg) noexcept;
    virtual const char* what() const noexcept;

private:
    std::string mMessage;
};

#endif /* EXCEPTIONS_H_ */
