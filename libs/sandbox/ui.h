#ifndef UI
#define UI

#include "../engine-core/window.h"
#include "../engine-core/sprite.h"
#include "../engine-core/resourceManager.h"
#include "../engine-core/renderer.h"
#include "../sandbox/objectManager.h"

// --- Variables ---
#define UI_ELEMENTS 7

static Sprite* sprites[UI_ELEMENTS];
static Sprite* highlighter = NULL;
static Sprite* activeElement = NULL;
static bool elementActive;
extern bool placementMode;

// --- Functions ---
void uiInit();
void uiRenderElements();
void uiRenderHighlighter();
int uiGetBlockmode();
void uiCleanUp();
bool uiButtonHover(int* x, int* y, Sprite* sprite);
int uiGetButtonState(Sprite* sprite);
void uiChangeButtonState(Sprite* sprite, int result, int count);
void uiDeleteButtonPressed();

#endif