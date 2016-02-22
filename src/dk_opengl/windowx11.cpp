#include "windowx11.hpp"

WindowX11::WindowX11(unsigned short width, unsigned short height) :
    mWidth(width), mHeight(height), mConnection(nullptr)
{
    /* Open the connection to the X server */
    mConnection = xcb_connect (NULL, NULL);


    /* Get the first screen */
    const xcb_setup_t      *setup  = xcb_get_setup (mConnection);
    xcb_screen_iterator_t   iter   = xcb_setup_roots_iterator (setup);
    xcb_screen_t           *screen = iter.data;


    /* Create the window */
    mWindow = xcb_generate_id (mConnection);
    xcb_create_window (mConnection,                    /* mConnection          */
                       XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
                       mWindow,                        /* window Id           */
                       screen->root,                  /* parent window       */
                       0, 0,                          /* x, y                */
                       mWidth, mHeight,                      /* width, height       */
                       10,                            /* border_width        */
                       XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                       screen->root_visual,           /* visual              */
                       0, NULL );                     /* masks, not used yet */


    /* Map the window on the screen */
    xcb_map_window (mConnection, mWindow);


    /* Make sure commands are sent before we pause so that the window gets shown */
    xcb_flush (mConnection);


}

WindowX11::~WindowX11()
{
    xcb_disconnect (mConnection);
}
