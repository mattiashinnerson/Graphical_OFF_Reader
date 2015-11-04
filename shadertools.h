#ifndef SHADERTOOLS_H
#define SHADERTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

typedef struct {
        const char*  filename;
        GLenum       type;
        GLchar*      source;
} Shader;

char* readShaderSource(const char*);
extern GLuint initProgram(const char*, const char*);

#endif
