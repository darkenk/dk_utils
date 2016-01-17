#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>

template <typename T> class Exception : public std::logic_error
{
public:
    Exception(const std::string& msg) : std::logic_error(msg) {}
};

#endif /* EXCEPTIONS_H_ */
