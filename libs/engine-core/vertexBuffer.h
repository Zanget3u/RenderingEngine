#ifndef VERTEXBUFFER
#define VERTEXBUFFER

#include "../../vendor/loading/glad.h"
#include "errorManager.h"
#include <stdlib.h>

//--- Functions ---
unsigned int* createVertexBuffer(const void* data, unsigned int size);
void deleteVertexBuffer(unsigned int* vboID);
void bindVertexBuffer(const unsigned int* vboID);
void unbindVertexBuffer();

#endif