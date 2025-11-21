#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>

int left = 0;
int right = 0;
int up = 0;
int down = 0;


void HandleUserInput(Display *dpy) {
    XEvent event;
    while (XPending(dpy)) {
        XNextEvent(dpy, &event);
        switch (event.type) {
            case KeyPress: {
                KeySym key = XLookupKeysym(&event.xkey, 0);
                if (key == XK_Right) right = 1;
                if (key == XK_Left)  left  = 1;
                if (key == XK_Up)    up    = 1;
                if (key == XK_Down)  down  = 1;
                break;
            }
            case KeyRelease: {
                KeySym key = XLookupKeysym(&event.xkey, 0);
                if (key == XK_Right) right = 0;
                if (key == XK_Left)  left  = 0;
                if (key == XK_Up)    up    = 0;
                if (key == XK_Down)  down = 0;
                break;
    }

        } 
    }
}