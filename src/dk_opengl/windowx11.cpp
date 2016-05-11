#include "windowx11.hpp"
#include <xcb/xcb_atom.h>
#include <xcb/xcb_icccm.h>
#include "../dk_utils/logger.hpp"

using namespace std;

WindowX11::WindowX11(unsigned short width, unsigned short height, const string& title)
    : mWidth(width), mHeight(height), mRunning(false), mConnection(nullptr),
      mAtomReplyDeleteWindow(nullptr) {
    /* Open the connection to the X server */
    mConnection = xcb_connect(NULL, NULL);

    /* Get the first screen */
    const xcb_setup_t* setup = xcb_get_setup(mConnection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t* screen = iter.data;

    /* Create the window */
    mWindow = xcb_generate_id(mConnection);
    xcb_create_window(mConnection,                   /* mConnection          */
                      XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
                      mWindow,                       /* window Id           */
                      screen->root,                  /* parent window       */
                      0, 0,                          /* x, y                */
                      mWidth, mHeight,               /* width, height       */
                      2,                             /* border_width        */
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                      screen->root_visual,           /* visual              */
                      0, NULL);                      /* masks, not used yet */

    /* Set the title of the window */
    xcb_change_property(mConnection, XCB_PROP_MODE_REPLACE, mWindow, XCB_ATOM_WM_NAME,
                        XCB_ATOM_STRING, 8, static_cast<uint>(title.size()), title.c_str());

    setFixedWindowSize();
    setAtomDeleteWindow();
    registerHandlers();
}

WindowX11::~WindowX11() {
    xcb_disconnect(mConnection);
}

void WindowX11::setAtomDeleteWindow() {
    // wtf is that?
    auto cookie = xcb_intern_atom(mConnection, 1, 12, "WM_PROTOCOLS");
    auto reply = xcb_intern_atom_reply(mConnection, cookie, 0);

    auto atomDeleteWindow = xcb_intern_atom(mConnection, 0, 16, "WM_DELETE_WINDOW");
    mAtomReplyDeleteWindow = xcb_intern_atom_reply(mConnection, atomDeleteWindow, 0);
    xcb_change_property(mConnection, XCB_PROP_MODE_REPLACE, mWindow, reply->atom, 4, 32, 1,
                        &mAtomReplyDeleteWindow->atom);
}

void WindowX11::setFixedWindowSize() {
    xcb_size_hints_t hints;
    xcb_icccm_size_hints_set_min_size(&hints, mWidth, mHeight);
    // if there is no 1, then window is not shown
    xcb_icccm_size_hints_set_max_size(&hints, mWidth, mHeight + 1);
    xcb_icccm_set_wm_size_hints(mConnection, mWindow, XCB_ATOM_WM_NORMAL_HINTS, &hints);
}

void WindowX11::registerHandlers() {
    mEventHandler[XCB_CLIENT_MESSAGE] =
        bind(&WindowX11::handleXcbClientMessage, this, placeholders::_1);
}

void WindowX11::handleXcbClientMessage(xcb_generic_event_t* event) {
    auto t = reinterpret_cast<xcb_client_message_event_t*>(event);
    if (t->data.data32[0] == mAtomReplyDeleteWindow->atom) {
        mRunning = false;
    }
}

void WindowX11::show(bool show) {
    if (show) {
        /* Map the window on the screen */
        xcb_map_window(mConnection, mWindow);
    } else {
        xcb_unmap_window(mConnection, mWindow);
    }

    /* Make sure commands are sent before we pause so that the window gets shown */
    xcb_flush(mConnection);
}

EGLNativeDisplayType WindowX11::getDisplay() {
    return EGL_DEFAULT_DISPLAY;
}

EGLNativeWindowType WindowX11::getWindow() {
    return mWindow;
}

bool WindowX11::processEvents() {
    mRunning = true;
    auto event = xcb_poll_for_event(mConnection);
    if (event) {
        auto fn = mEventHandler[event->response_type & ~0x80];
        if (fn != nullptr) {
            fn(event);
        }
        free(event);
    }
    return mRunning;
}
