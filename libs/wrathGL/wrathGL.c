#include "wrathGL.h"

void wrathGLLoadResources()
{
    //Load textures
    resourceManagerLoadTexture("dirtTexture", "res/textures/wrathGL/Dirt.jpg"); 
    resourceManagerLoadTexture("stoneTexture", "res/textures/wrathGL/Stone.jpeg");   
    resourceManagerLoadTexture("snowTexture", "res/textures/wrathGL/Snow.jpeg");    
    resourceManagerLoadTexture("DuDvMap", "res/textures/wrathGL/DuDvMap.png");
    resourceManagerLoadTexture("waterNormalMap", "res/textures/wrathGL/WaterNormalMap.png");
    resourceManagerLoadTexture("sidebarTexture", "res/textures/sandbox/Sidebar.png"); 
    resourceManagerLoadTexture("keyboardTexture", "res/textures/wrathGL/Keyboard.png"); 
    resourceManagerLoadTexture("terrainTexture", "res/textures/wrathGL/Terrain.png"); 

    //Load shaders
    resourceManagerLoadShader("terrainShader", "res/shader/wrathGL/terrain_vs.glsl", "res/shader/wrathGL/terrain_fs.glsl");
    resourceManagerLoadShader("waterShader", "res/shader/wrathGL/water_vs.glsl", "res/shader/wrathGL/water_fs.glsl");
    resourceManagerLoadShader("batchTextShader", "res/shader/sandbox/batchText_vs.glsl", "res/shader/sandbox/batchText_fs.glsl");
    resourceManagerLoadShader("simpleTextShader", "res/shader/sandbox/simpleText_vs.glsl", "res/shader/sandbox/simpleText_fs.glsl");
    resourceManagerLoadShader("spriteShader", "res/shader/sandbox/standard_vs.glsl", "res/shader/sandbox/standard_fs.glsl");

    //Load sprite data
    resourceManagerLoadSpriteData(); 
}

void wrathGLAddText()
{
    textBatchRendererAddText("POSITION:", 7.5f, HEIGHT - 75.0f, 0.5f);
    textBatchRendererAddText("X:", 20.0f, HEIGHT - 100.0f, 0.5f);
    textBatchRendererAddText("Y:", 20.0f, HEIGHT - 125.0f, 0.5f);
    textBatchRendererAddText("Z:", 20.0f, HEIGHT - 150.0f, 0.5f);
    textBatchRendererAddText("ROTATION:" , 7.5f, HEIGHT - 175.0f, 0.5f);
    textBatchRendererAddText("YAW:" , 20.0f, HEIGHT - 200.0f, 0.5f);
    textBatchRendererAddText("PITCH:" , 20.0f, HEIGHT - 225.0f, 0.5f);
    textBatchRendererAddText("TERRAIN-VERTICES:" , 7.5f, HEIGHT - 250.0f, 0.5f);
    textBatchRendererAddText("-------------------------------", 7.5f, HEIGHT - 300.0f, 0.5f);
    textBatchRendererAddText("F1: TELEPORT NEAR", 7.5f, HEIGHT - 400.0f, 0.5f);
    textBatchRendererAddText("F2: TELEPORT FAR", 7.5f, HEIGHT - 425.0f, 0.5f);
    textBatchRendererAddText("F3: WIREFRAME ON", 7.5f, HEIGHT - 450.0f, 0.5f);
    textBatchRendererAddText("F4: WIREFRAME OFF", 7.5f, HEIGHT - 475.0f, 0.5f);
    textBatchRendererAddText("-------------------------------", 7.5, HEIGHT - 500.0f, 0.5f);
    textBatchRendererAddText("    GENERATE", 7.5f, HEIGHT - 615.0f, 0.5f);
    textBatchRendererAddText("F5:    NEW", 7.5f, HEIGHT - 635.0f, 0.5f);
    textBatchRendererAddText("    TERRAIN", 7.5f, HEIGHT - 655.0f, 0.5f);
}

void wrathGLRenderText()
{   
    //Create buffers
    char xBuffer[6];
    char yBuffer[6];
    char zBuffer[6];
    char yawBuffer[6];
    char pitchBuffer[5];
    char verticeBuffer[8];

    //Update buffers
    snprintf(&xBuffer[0], sizeof(xBuffer), "%4.f", camera->position[0]);   //X
    snprintf(&yBuffer[0], sizeof(yBuffer), "%4.f", camera->position[1]);   //Y
    snprintf(&zBuffer[0], sizeof(zBuffer), "%4.f", camera->position[2]);   //Z
    snprintf(&yawBuffer[0], sizeof(yawBuffer), "%3.f", camera->yaw);       //Yaw
    snprintf(&pitchBuffer[0], sizeof(pitchBuffer), "%2.f", camera->pitch); //Pitch
    snprintf(&verticeBuffer[0], sizeof(verticeBuffer), "%7d", vertices);   //Vertices

    //Render buffers
    textSimpleRendererDisplay(&xBuffer[0], 45.0f, HEIGHT - 100.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});     //X
    textSimpleRendererDisplay(&yBuffer[0], 45.0f, HEIGHT - 125.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});     //Y
    textSimpleRendererDisplay(&zBuffer[0], 45.0f, HEIGHT - 150.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});     //Z
    textSimpleRendererDisplay(&yawBuffer[0], 70.0f, HEIGHT - 200.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f});   //Yaw
    textSimpleRendererDisplay(&pitchBuffer[0], 90.0f, HEIGHT - 225.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f}); //Pitch
    textSimpleRendererDisplay(&verticeBuffer[0], 20.0f, HEIGHT - 275.0f, 0.5f, (vec3){0.8f, 0.8f, 0.8f}); //Vertices
}

void wrathGLInit()
{
    //Init modules
    windowInit("RenderingEngine - WrathGL");   
    rendererInit(camera);
    initWaterRenderer(camera);

    //Load resources
    wrathGLLoadResources();

    //Get resources
    unsigned int dirtTexture = resourceManagerGetTexture("dirtTexture");
    unsigned int stoneTexture = resourceManagerGetTexture("stoneTexture");
    unsigned int snowTexture = resourceManagerGetTexture("snowTexture");
    unsigned int DuDvMap = resourceManagerGetTexture("DuDvMap");
    unsigned int waterNormalMap = resourceManagerGetTexture("waterNormalMap");
    unsigned int keyboardTexture = resourceManagerGetTexture("keyboardTexture");
    unsigned int terrainTexture = resourceManagerGetTexture("terrainTexture");

    unsigned int terrainShader = resourceManagerGetShader("terrainShader");
    unsigned int waterShader = resourceManagerGetShader("waterShader");
    unsigned int batchTextShader = resourceManagerGetShader("batchTextShader");
    unsigned int simpleTextShader = resourceManagerGetShader("simpleTextShader");
    unsigned int spriteShader = resourceManagerGetShader("spriteShader");

    unsigned int spriteData = resourceManagerGetSpriteData();

    //Create meshes   
    mesh_t* terrainMesh = meshCreatorTerrain(1000, 1.6f);   
    mesh_t* planeMesh = meshCreatorOneTile(1600.0f);

    //Create models
    unsigned int terrainTextures[3] = {dirtTexture, stoneTexture, snowTexture};
    terrainModel = createModel(terrainMesh, terrainShader, terrainTextures, 3);
    
    unsigned int waterTextures[5] = {DuDvMap, waterNormalMap, reflectionTexture, refractionTexture, refractionDepthTexture};
    waterModel = createModel(planeMesh, waterShader, waterTextures, 5); 

    //Create sprites
    keyboardSprite = createSprite(spriteData, keyboardTexture, spriteShader, (vec2){15.0f, 250.0f}, (vec2){175.0f, 150.0f}, 0.0f, (vec3){0.7f, 0.7f, 0.7f}, false);
    terrainSprite = createSprite(spriteData, terrainTexture, spriteShader, (vec2){40.0f, 495.0f}, (vec2){100.0f, 100.0f}, 0.0f, (vec3){1.0f, 1.0f, 1.0f}, false);

    // --- Init the whole text rendering system (batch and simple text renderer)
        //Batch text rendering system ONLY ALLOWS 32 different characters!
        textRenderingSystemsInit(batchTextShader, simpleTextShader);
        monitoringInit();  

        //Add static text
        monitoringAddText();
        wrathGLAddText();

        //After all text got added -> create one big buffer out of it, to render all batched text in one drawcall
        textBatchRendererUploadToGPU(); 
}

bool wrathGLIsRunning()
{
    return windowIsRunning();
}

void wrathGLPerFrame()
{
    // --- Pre render
        windowCalcFrametime();
        windowPollEvents();
        windowProcessEvents();
        windowPrepare();         

    // --- Do render
        // -- Reset stats for current frame
        drawcalls = 0; 
        vertices = 0;

        // -- Activate wireframe rendering if enabled
        if(wireframeMode == true){
            GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));}

        // -- Render scene to reflection and refraction framebuffers
        GLCall(glEnable(GL_CLIP_DISTANCE0)); 
        renderToReflectFramebuffer(terrainModel, resourceManagerGetShader("terrainShader"));
        renderToRefractFramebuffer(terrainModel, resourceManagerGetShader("terrainShader"));
        GLCall(glDisable(GL_CLIP_DISTANCE0)); //Doesn't work on every graphics driver
      
        // -- Render scene        
        renderModel(terrainModel);   
        renderWater(waterModel, deltaTime);

        // -- Deactivate wireframe rendering if enabled
        if(wireframeMode == true){
             GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));}  

        // -- Render sprites
        renderSprite(keyboardSprite);   
        renderSprite(terrainSprite);   

        // -- Render text
        GLCall(glDisable(GL_DEPTH_TEST));
        textBatchRendererDisplay(); 
        monitoringRenderText(deltaTime);
        wrathGLRenderText();
        GLCall(glEnable(GL_DEPTH_TEST));        

    // --- After render
        windowUpdateTitle(drawcalls);
        windowSwapBuffer(); 
}

void wrathGLCleanUp()
{
    //Clean up models and sprites
    deleteModel(terrainModel);
    deleteModel(waterModel);
    deleteSprite(keyboardSprite);
    deleteSprite(terrainSprite);

    //Clean up modules
    monitoringCleanUp();
    textRenderingSystemsCleanUp();
    resourceManagerCleanUp(); 
    cleanUpWaterRenderer();
    windowCleanUp();     
}