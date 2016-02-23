#include <gtest/gtest.h>
#include "windowx11.hpp"

TEST(test_windowx11, initialization) {
    WindowX11 w(200, 300);
    w.show();
    w.run();
}
