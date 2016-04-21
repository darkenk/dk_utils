#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <cstdio>
#include <iostream>
#include <string>

class Logger
{
public:
    enum Level { Verbose, Debug, Error };

    Logger(Level level) : mLevel(level) {}
    ~Logger() {
        std::cerr << std::endl;
    }

    template <class T> Logger& operator<<(T var) {
        std::cerr << getColor() << var << "\033[0m";
        return *this;
    }

private:
    Level mLevel;
    const char* getColor();
};

#define LOG(level) Logger(level) << __BASE_FILE__ << ':' << __LINE__ << ' '
#define LOGV LOG(Logger::Level::Verbose)
#define LOGD LOG(Logger::Level::Debug)
#define LOGE LOG(Logger::Level::Error)

#define LOGP(color, fmt, ...) \
    fprintf(stderr, color "%s:%d " fmt "\n\033[0m", __FUNCTION__, __LINE__, ##__VA_ARGS__)
//#define LOGVP(fmt, ...) LOGP("\033[32m", fmt, ##__VA_ARGS__)
#define LOGP_INTERNAL(color, ...) LOGP(color, ##__VA_ARGS__)
#define LOGVP(...) LOGP_INTERNAL("\033[32m", ##__VA_ARGS__)
#define LOGVD(...) LOGP_INTERNAL("\033[33m", ##__VA_ARGS__)
#define LOGVE(...) LOGP_INTERNAL("\033[31m", ##__VA_ARGS__)

#endif  // LOGGER_HPP
