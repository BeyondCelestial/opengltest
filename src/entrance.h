#pragma once

#include "X11/Xlib.h"
#include "GL/gl.h"
#include "GL/glx.h"

void MainGameLoop(Display *dpy, Window win);
void MainLoad(Display *dpy, Window win);