#ifndef WINDOWX11_HPP
#define WINDOWX11_HPP

#include <xcb/xcb.h>

class WindowX11
{
public:
    WindowX11(unsigned short width, unsigned short height);
    virtual ~WindowX11();

private:
    unsigned short mWidth;
    unsigned short mHeight;
    xcb_connection_t* mConnection;
    xcb_window_t mWindow;
};

#endif // WINDOWX11_HPP
