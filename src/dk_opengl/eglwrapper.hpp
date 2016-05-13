#ifndef EGLWRAPPER_HPP
#define EGLWRAPPER_HPP

#include <EGL/egl.h>
#include <mutex>
#include "../dk_utils/exceptions.hpp"
#include "../dk_utils/noncopyable.hpp"

class EGLWrapper : NonCopyable
{
public:
    EGLWrapper(EGLNativeDisplayType dsp, EGLNativeWindowType window,
               const EGLint configAttribs[] = nullptr, EGLContext shareContext = EGL_NO_CONTEXT);
    ~EGLWrapper();
    void swap();
    void makeCurrent();

    EGLDisplay display() const;
    EGLContext context() const;
    EGLSurface surface() const;

private:
    static const EGLint sConfigAttribs[];
    static const EGLint sContextAttribs[];
    static const EGLint sSurfaceAttribs[];
    static int sInstances;
    static std::mutex sMutexInit;
    EGLDisplay mDisplay;
    EGLContext mContext;
    EGLSurface mSurface;

    [[noreturn]] void throwError(const std::string& message);
    void init(EGLNativeDisplayType dsp, EGLNativeWindowType window, const EGLint configAttribs[],
              EGLContext shareContext);
    void deinit();
};

using EGLException = Exception<EGLWrapper>;

#endif  // EGLWRAPPER_HPP
