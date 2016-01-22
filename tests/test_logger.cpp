#include <gtest/gtest.h>
#include "logger.hpp"

TEST(test_logger, log_ints) {
    LOGVP("DK %d", 12);
}
