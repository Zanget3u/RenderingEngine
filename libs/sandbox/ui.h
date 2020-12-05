#ifndef UI
#define UI

#include "../engine-core/window.h"
#include "../engine-core/texture.h"
#include "../engine-core/shader.h"
#include "../engine-core/sprite.h"

// --- Variables ---
static unsigned int* blockTexture, *blockSolidTexture, *pickaxeTexture, *bgTexture, *sbTexture;
static unsigned int* shader;
static unsigned int* spriteData;

// --- Functions ---
void uiInit();
void uiRender();
void uiCleanUp();

#endif