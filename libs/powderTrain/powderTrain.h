#ifndef POWDERTRAIN
#define POWDERTRAIN

#include "../engine-core/2D/window2D.h"
#include "../engine-core/general/renderer.h"
#include "ui_powderTrain.h"
#include "../engine-core/general/textRenderer.h"
#include "../engine-core/general/monitoring.h"
#include "../engine-core/general/pixelRenderer.h"
#include "../engine-core/general/random.h"

// --- Functions ---
void powderTrainInit();
bool powderTrainIsRunning();
void powderTrainPerFrame();
void powderTrainCleanUp();

#endif