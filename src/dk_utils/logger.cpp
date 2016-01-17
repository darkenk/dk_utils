#include "logger.hpp"

const char* Logger::getColor() {
    switch (mLevel) {
        case Level::Verbose:
            return "\033[32m";
        case Level::Debug:
            return "\033[33m";
        case Level::Error:
            return "\033[31m";
    }
    return "";
}
