#ifndef OBJECTMANAGER
#define OBJECTMANAGER

#include "ui.h"
#include "../engine-core/window.h"
#include "../engine-core/renderer.h"

// --- Variables ---
#define OBJECT_COUNT_MAX 100

typedef struct{
    vec2 position;
    int type;
} object;

static object objects[OBJECT_COUNT_MAX];
static int objectCount = 0;
static Sprite* blockObject, *solidBlockObject;
static int last_x = 0, last_y = 0; //Keep track of the last added position, to avoid duplicate entries

// --- Functions ---
void objectManagerInit();
void objectManagerRenderObjects();
void objectManagerDeleteAllObjects();
void objectManagerCheckForPlacement();
void objectManagerCleanUp();

#endif