#include "exceptions.hpp"
#include <gtest/gtest.h>

TEST(test_exception, correct_message) {
    std::string msg("Burp");
    try {
        throw Exception(msg);
    } catch (Exception& e) {
        EXPECT_STREQ(msg.c_str(), e.what());
    }
};
