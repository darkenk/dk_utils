#include "logger.hpp"
#include <gtest/gtest.h>

TEST(test_logger, log_ints) {
    LOGVP("DK %d", 12);
}
