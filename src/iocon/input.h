#pragma once
#include <X11/Xlib.h>

extern int right;
extern int left;
extern int up;
extern int down;

void HandleUserInput(Display *dpy);