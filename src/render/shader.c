
#include "shader.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include "../file/file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int CreateShaderPrograms(char* fragment[], char* vertex[]) {
    GLuint shaderProgram;


    shaderProgram = glCreateProgram();



    //create shader objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    int ivert = 0;

    while (vertex[ivert] != NULL && strcmp(vertex[ivert], "END") != 0) {
        ivert++;
    }

    char** srcvert = (char**)malloc(ivert * sizeof(char*));

    int ifrag = 0;

    while (fragment[ifrag] != NULL && strcmp(fragment[ifrag], "END") != 0) {
        ifrag++;
    }

    char** srcfrag = (char**)malloc(ifrag * sizeof(char*));

    //link shader objects with the shaders
    int file;
    file = 0;

    while (vertex[file] != NULL && strcmp(vertex[file], "END") != 0) {
        char* srci = getFile(vertex[file]);
        srcvert[file] = srci;
        file++;
    }

    glShaderSource(vertexShader, file, (const char * const *)srcvert, NULL);
    glCompileShader(vertexShader);

    
    for (int ii = 0; ii < ivert; ii++) {
        free(srcvert[ii]);
    }

    free(srcvert);

    file = 0;
    while (fragment[file] != NULL && strcmp(fragment[file], "END") != 0) {
        char* srci = getFile(fragment[file]);
        srcfrag[file] = srci;
        file++;
    }
    
    glShaderSource(fragmentShader, file, (const char * const *)srcfrag, NULL);
    glCompileShader(fragmentShader);
    
    for (int ii = 0; ii < ifrag; ii++) {
        free(srcfrag[ii]);
    }
    free(srcfrag);
    //compile shaders

    

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

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}