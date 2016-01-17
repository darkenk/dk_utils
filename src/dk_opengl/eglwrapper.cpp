#include "eglwrapper.hpp"
#include <cassert>
#include <sstream>

using namespace std;

// clang-format off
const EGLint EGLWrapper::sConfigAttribs[] = {
    EGL_COLOR_BUFFER_TYPE,     EGL_RGB_BUFFER,
    EGL_BUFFER_SIZE,           32,
    EGL_RED_SIZE,              8,
    EGL_GREEN_SIZE,            8,
    EGL_BLUE_SIZE,             8,
    EGL_ALPHA_SIZE,            8,

    EGL_DEPTH_SIZE,            24,
    EGL_STENCIL_SIZE,          8,

    EGL_SAMPLE_BUFFERS,        0,
    EGL_SAMPLES,               0,

    EGL_SURFACE_TYPE,          EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE,       EGL_OPENGL_ES2_BIT,

    EGL_NONE,
};

const EGLint EGLWrapper::sContextAttribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE,
};

const EGLint EGLWrapper::sSurfaceAttribs[] = {
   EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
   EGL_NONE,
};
// clang-format on

int EGLWrapper::sInstances = 0;
mutex EGLWrapper::sMutexInit;

EGLWrapper::EGLWrapper(EGLNativeDisplayType display, EGLNativeWindowType window,
                       const EGLint configAttribs[], EGLContext shareContext)
    : mDisplay(EGL_NO_DISPLAY), mContext(EGL_NO_CONTEXT), mSurface(EGL_NO_SURFACE) {
    if (configAttribs == nullptr) {
        configAttribs = sConfigAttribs;
    }
    init(display, window, configAttribs, shareContext);
}

EGLWrapper::~EGLWrapper() {
    deinit();
}

void EGLWrapper::swap() {
    EGLBoolean ret = eglSwapBuffers(mDisplay, mSurface);
    assert(ret);
}

void EGLWrapper::makeCurrent() {
    EGLBoolean ret = eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);
    assert(ret);
}

EGLDisplay EGLWrapper::display() const {
    return mDisplay;
}

EGLContext EGLWrapper::context() const {
    return mContext;
}

EGLSurface EGLWrapper::surface() const {
    return mSurface;
}

void EGLWrapper::throwError(const string &message) {
    ostringstream oss;
    oss << std::hex << eglGetError();
    throw EGLException("Error: " + oss.str() + ". " + message);
}

void EGLWrapper::init(EGLNativeDisplayType display, EGLNativeWindowType window,
                      const EGLint configAttribs[], EGLContext shareContext) {
    lock_guard<mutex> l(sMutexInit);
    EGLint numConfigs = 0;
    EGLConfig config = 0;
    EGLint noOfRequestedConfigs = 1;
    if (not eglBindAPI(EGL_OPENGL_ES_API)) {
        throwError("Cannot bind to GLES API");
    }
    mDisplay = eglGetDisplay(display);
    if (mDisplay == EGL_NO_DISPLAY) {
        throwError("EGL_NO_DISPLAY");
    }
    if (sInstances == 0 && not eglInitialize(mDisplay, nullptr, nullptr)) {
        throwError("Cannot initialize egl");
    }
    sInstances++;
    eglChooseConfig(mDisplay, configAttribs, &config, noOfRequestedConfigs, &numConfigs);
    if (numConfigs == 0) {
        throwError("Failed to get config");
    }
    mContext = eglCreateContext(mDisplay, config, shareContext, sContextAttribs);
    if (mContext == EGL_NO_CONTEXT) {
        throwError("Can't create context");
    }
    if (window != 0) {
        mSurface = eglCreateWindowSurface(mDisplay, config, window, sSurfaceAttribs);
        if (mSurface == EGL_NO_SURFACE) {
            throwError("Can't create surface");
        }
    }
    makeCurrent();
}

void EGLWrapper::deinit() {
    lock_guard<mutex> l(sMutexInit);
    eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (mSurface != EGL_NO_SURFACE) {
        eglDestroySurface(mDisplay, mSurface);
    }
    if (mContext != EGL_NO_CONTEXT) {
        eglDestroyContext(mDisplay, mContext);
    }
    eglReleaseThread();
    if (--sInstances == 0 && mDisplay != EGL_NO_DISPLAY) {
        eglTerminate(mDisplay);
    }
}
