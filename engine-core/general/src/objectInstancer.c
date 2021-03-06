#include "objectInstancer.h"

instance_t* objectInstancerCreateInstance(unsigned int texture, float* color, float size, float mass)
{
    //Create and bind vao
    unsigned int vao = createVertexArray();
    bindVertexArray(vao);

    //Create data
    float vertices[] =
    {
        //Position  //Texture
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    //Create model buffer and set it to zero
    mat4 modelBuffer[MAX_INSTANCES];
    memset(&modelBuffer[0], 0, MAX_INSTANCES * 16 * sizeof(float));

    //Create vbos, send it data, configure vao and set the attrib divisors
    //vbo1 (vertice data)
    unsigned int vbo1 = createVertexBuffer(vertices, sizeof(vertices));
    defineVertexAttributes(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);  

    //vbo2 (model matrix buffer - maximum size for vertex attributes is a vec4 
    //so we need to send 4 consecutive vec4's to simulate a mat4) 
    unsigned int vbo2 = createDynamicVertexBuffer(&modelBuffer[0], MAX_INSTANCES * 16 * sizeof(float));

    defineVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);    
    defineVertexAttributes(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));    
    defineVertexAttributes(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));    
    defineVertexAttributes(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));  

    setAttributeDivisor(1, 1);
    setAttributeDivisor(2, 1);
    setAttributeDivisor(3, 1);
    setAttributeDivisor(4, 1);

    unbindVertexArray(vao);
    unbindVertexBuffer(vbo1);
    unbindVertexBuffer(vbo2);

    //Delete vertice data vbo -> not needed anymore and it will not get passed into the struct
    deleteVertexBuffer(vbo1);

    //Create struct and fill it with data
    instance_t instance;
    instance.instanceID = instanceID;
    instance.instanceAmount = 0;
    instance.vao = vao;
    instance.vboM = vbo2;
    memcpy(&instance.modelBuffer, &modelBuffer, MAX_INSTANCES * 16 * sizeof(float));
    instance.texture = texture;
    instance.shader = resourceManagerGetShader("instancedShader");
    instance.color[0] = color[0];
    instance.color[1] = color[1];
    instance.color[2] = color[2];
    instance.width = size;
    instance.height = size;
    instance.mass = mass;

    //Copy sprite onto the heap and return it
    void* mem = malloc(sizeof(instance_t));
    memcpy(mem, &instance, sizeof(instance_t));

    instanceID++;        

    return (instance_t*)mem;    
}

void objectInstancerAddInstance(instance_t* instance, float* position)
{
    if(instance->instanceAmount < MAX_INSTANCES)
    {
        //Create model matrix with new transformations
        mat4 model;
        glm_mat4_identity(model);
        glm_translate(model, (vec3){position[0], position[1], 1.0f});
        glm_scale(model, (vec3){100.0f, 100.0f, 1.0f});

        //Copy model matrix into model buffer
        memcpy(&instance->modelBuffer[instance->instanceAmount], &model, sizeof(mat4));
        
        //Send model buffer to the gpu
        bindVertexBuffer(instance->vboM);
        updateDynamicVertexBuffer(&instance->modelBuffer[0], MAX_INSTANCES * 16 * sizeof(float));
        unbindVertexBuffer();

        //Add object instance to physics simulation        
        unsigned int offset = instance->instanceID * 100; //Get offset => 0 for boxes & 100 for blocks
        unsigned int id = instance->instanceAmount + offset;
        physicsEngineAddBox(id, position[0], position[1], instance->width, instance->height, instance->mass);    

        instance->instanceAmount++;
    }
}

void objectInstancerSetWorldtransform(instance_t* instance)
{
    for(int i = 0; i < instance->instanceAmount; i++)
    {       
        //Get id       
        unsigned int offset = instance->instanceID * 100; //Get offset => 0 for boxes & 100 for blocks
        unsigned int id = i + offset;

        //Get world transform
        float newPosition[2];
        float newRotation[1];
        physicsEngineGetWorldtransform(id, newPosition, newRotation);

        //Create model matrix
        mat4 modelToChange;
        glm_mat4_identity(modelToChange);

        //Translate
        glm_translate(modelToChange, (vec3){newPosition[0], newPosition[1], 1.0f});

        //Rotate
        float size = 100;
        glm_translate(modelToChange, (vec3){size * 0.5f, size * 0.5f, 0.0f}); //Move origin of rotation to center of quad
        glm_rotate(modelToChange, newRotation[0], (vec3){0.0f, 0.0f, 1.0f}); //Then rotate
        glm_translate(modelToChange, (vec3){size * -0.5f, size * -0.5f, 0.0f}); //Move origin back   

        //Scale
        glm_scale(modelToChange, (vec3){100.0f, 100.0f, 1.0f});

        //Copy model matrix into model buffer
        memcpy(&instance->modelBuffer[i], &modelToChange, sizeof(mat4));
    }
        
    //Send model buffer to the gpu
    bindVertexBuffer(instance->vboM);
    updateDynamicVertexBuffer(&instance->modelBuffer[0], MAX_INSTANCES * 16 * sizeof(float));
    unbindVertexBuffer();
}

void objectInstancerDeletePhysicsInstance(instance_t* instance)
{
    unsigned int offset = instance->instanceID * 100; //Get offset => 0 for boxes & 100 for blocks

    //Delete all physics objects
    for(int i = 0; i < instance->instanceAmount; i++)
    {
        unsigned int id = i + offset;
        physicsEngineDeleteObject(i);
    } 

    //Recreate scene
    physicsEngineDeleteScene();
    physicsEngineInit();    
}

void objectInstancerDeleteInstance(instance_t* instance)
{
    deleteVertexBuffer(instance->vboM);
    deleteVertexArray(instance->vao);

    free(instance);
}