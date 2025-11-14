// main_game.c
#include <GL/glew.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glx.h>
#include "file.h"

float array[6] = {
   -0.5f, -0.5f,
    0.0f,  0.5f,
    0.5f, -0.5f
};

//VBO and VAO ID variables
unsigned int buffer;
unsigned int VAO;

//Fragment and vertex shader pointer variables
char* frag;
char* vert;

//Universal Offser variables
int offsety = 0;
int offsetx = 0;

//Shader related ID variables
GLuint shaderProgram;
GLuint offUloc;


// --- Forward declaration ---
void LoopDraw(Display *dpy, Window win);

// ---------------- MainLoad ----------------
void MainLoad(Display *dpy, Window win) {
    // Initialize GLEW (after GLX context is current!)
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    }
    shaderProgram = glCreateProgram();

    //load shaders
    frag = getFile("shaders/main.frag");
    vert = getFile("shaders/main.vert");

    //create shader objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* src[1];


    //link shader objects with the shaders
    src[0] = vert;
    glShaderSource(vertexShader, 1, src, NULL);
    src[0] = frag;
    glShaderSource(fragmentShader, 1, src, NULL);

    //compile shaders
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    //check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "Vertex shader compilation failed:\n%s\n", infoLog);
    }

    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check linking
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "Shader linking failed:\n%s\n", infoLog);
    }

    //delete shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), array, GL_STATIC_DRAW);

    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    

    glVertexAttribPointer(
        0,        // location 0
        2,        // 2 floats per vertex (vec2)
        GL_FLOAT, // type
        GL_FALSE, // not normalized
        0,        // stride (tightly packed)
        (void*)0  // offset
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    offUloc = glGetUniformLocation(shaderProgram, "offU");

}

// ---------------- MainGameLoop ----------------
void MainGameLoop(Display *dpy, Window win) {
    // Process events
    XEvent event;
    while (XPending(dpy)) {
        XNextEvent(dpy, &event);
        if (event.type == KeyPress) {
            KeySym key = XLookupKeysym(&event.xkey, 0);



            if (key == XK_Right) {
                offsetx += 5;
            }
        } 
    }
    // Draw
    LoopDraw(dpy, win);

    // Swap buffers
    glXSwapBuffers(dpy, win);
}

// ---------------- LoopDraw ----------------
void LoopDraw(Display *dpy, Window win) {
    glClear(GL_COLOR_BUFFER_BIT); //clear last image

    glUseProgram(shaderProgram); // use shader program
    glUniform2f(offUloc, (float)offsetx/100, (float)offsety/100); 
    // pass in the offU the uniform shader variable

    //binf vertex array and draw, unbind vertex array.
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

}
