#include <gtest/gtest.h>
#include "dk_opengl/windowx11.hpp"
#include "dk_opengl/eglwrapper.hpp"
#include <GLES2/gl2.h>

TEST(test_windowx11, initialization) {
    WindowX11 w(200, 300);
    w.show();

    EGLWrapper egl(w.getDisplay(), w.getWindow());
    int i = 120;
    while (i-- && w.processEvents()) {
        glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        egl.swap();
    }
}
