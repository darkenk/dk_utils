#include <gtest/gtest.h>
#include "windowx11.hpp"

TEST(test_windowx11, initialization)
{
    WindowX11 w(100, 100);
    sleep(3);
}
