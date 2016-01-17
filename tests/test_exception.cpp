#include "exceptions.hpp"
#include <gtest/gtest.h>

TEST(test_exception, correct_message) {
    class T
    {};
    std::string msg("Burp");
    try {
        throw Exception<T>(msg);
    } catch (Exception<T>& e) {
        EXPECT_STREQ(msg.c_str(), e.what());
    }
};
