#ifndef WINDOWX11_HPP
#define WINDOWX11_HPP

#include <EGL/egl.h>
#include <functional>
#include <map>
#include <string>
#include <xcb/xcb.h>

class WindowX11
{
public:
    WindowX11(unsigned short width, unsigned short height, const std::string& title = "");
    virtual ~WindowX11();

    virtual void show(bool show = true);

    virtual EGLNativeDisplayType getDisplay();
    virtual EGLNativeWindowType getWindow();

    virtual bool processEvents();

private:
    unsigned short mWidth;
    unsigned short mHeight;
    bool mRunning;
    xcb_connection_t* mConnection;
    xcb_window_t mWindow;
    xcb_intern_atom_reply_t* mAtomReplyDeleteWindow;
    std::map<int, std::function<void(xcb_generic_event_t*)>> mEventHandler;

    void setAtomDeleteWindow();
    void setFixedWindowSize();
    void registerHandlers();
    void handleXcbClientMessage(xcb_generic_event_t* event);
};

#endif  // WINDOWX11_HPP
