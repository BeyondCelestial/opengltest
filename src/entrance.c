// main_game.c
#include <GL/glew.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glx.h>
#include "file/file.h"
#include "render/shader.h"
#include "iocon/input.h"

float array[12] = {
   -0.5f, -0.5f,
   -0.5f,  0.5f,
    0.5f, -0.5f,
    0.5f,  0.5f,
   -0.5f,  0.5f,
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

//user input variables
int movex = 0;
int movey = 0;
int speed = 5;
//Shader related ID variables
GLuint shaderProgram;
GLuint offUloc;


// --- Forward declaration ---
void LoopDraw(Display *dpy, Window win);
void UpdateVariables();


// ---------------- MainLoad ----------------
void MainLoad(Display *dpy, Window win) {
    // Initialize GLEW (after GLX context is current!)
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    }
    
    char* frag[] = {"shaders/main.frag", "END"};
    char* vert[] = {"shaders/main.vert", "END"};

    shaderProgram = CreateShaderPrograms(frag, vert);


    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), array, GL_STATIC_DRAW);

    
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
    HandleUserInput(dpy);
    //Update Varibles
    UpdateVariables();
    // Draw
    LoopDraw(dpy, win);

    // Swap buffers
    glXSwapBuffers(dpy, win);
}


// ---------------- LoopDraw ----------------
void LoopDraw(Display *dpy, Window win) {
    glClear(GL_COLOR_BUFFER_BIT); //clear last image

    glUseProgram(shaderProgram); // use shader program
    glUniform2f(offUloc, (float)offsetx/200, (float)offsety/200); 
    // pass in the offU the uniform shader variable

    //binf vertex array and draw, unbind vertex array.
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}


void UpdateVariables() {
    movex = 0;
    movey = 0;
    if (right && !left) movex = 1;
    if (left  && !right) movex = -1;
    if (up    && !down)  movey = 1;
    if (down  && !up)    movey = -1;

    offsetx += speed * movex;
    offsety += speed * movey;
}