#include "exceptions.hpp"

Exception::Exception(const std::string& msg) noexcept {
    mMessage = msg;
}

const char* Exception::what() const noexcept {
    return mMessage.c_str();
}
