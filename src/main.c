#include <stdio.h>
#include <stdlib.h>
#include "entrance.h"
#include <X11/XKBlib.h>

int main() {

    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Could not open display\n");
        return 1;
    }
    Bool supported;
    XkbSetDetectableAutoRepeat(dpy, True, &supported);

    printf("Connected to X server\n");

    int scr = DefaultScreen(dpy);
    printf("Found Default Screen\n");

    static int visattb[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
    XVisualInfo *vi = glXChooseVisual(dpy, scr, visattb);

    if(!vi) {
        fprintf(stderr, "No approporta evisual found\n");
        return 1;
    }

    Window root = RootWindow(dpy, scr);
    printf("Found root window\n");

    Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;

    Window win = XCreateWindow(
        dpy, root,
        50, 50,
        800, 600,
        0,
        vi->depth, InputOutput,
        vi->visual,
        CWColormap | CWEventMask,
        &swa
    );
    printf("Created a simple window\n");

    GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    XMapWindow(dpy, win);
    printf("Mapped Window\n");

    MainLoad(dpy, win);

    while (1){
        MainGameLoop(dpy, win);
    }

    printf("Closing window\n");
    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, glc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    return 0;
}
