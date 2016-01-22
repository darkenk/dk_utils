#include <gtest/gtest.h>
#include "eglwrapper.hpp"

TEST(test_eglwrapper, initialization) {
    {
        EGLWrapper eg(nullptr, 0);
        EXPECT_EQ(eglGetCurrentContext(), eg.context());
        EXPECT_EQ(eglGetCurrentDisplay(), eg.display());
    }
    EXPECT_EQ(EGL_NO_CONTEXT, eglGetCurrentContext());
    EXPECT_EQ(EGL_NO_DISPLAY, eglGetCurrentDisplay());
}
