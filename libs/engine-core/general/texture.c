#include "texture.h"

unsigned int* createTexture(const char* path)
{
    int width, height, BPP; 
    unsigned int* rendererID = (unsigned int*)malloc(sizeof(unsigned int));
    unsigned char* localBuffer = stbi_load(path, &width, &height, &BPP, 0);

    if(localBuffer)
    {
        GLenum format;
        if(BPP == 1)
            format = GL_RED;
        else if(BPP == 3)
            format = GL_RGB;
        else if(BPP == 4)
            format = GL_RGBA;
        else
        {
            log_error("Imageformat is not supported!");
            return NULL;
        }            

        GLCall(glGenTextures(1, rendererID));
        bindTexture(rendererID);
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        log_info("Successfully load texture at %s", path);
        stbi_image_free(localBuffer);

        return rendererID;
    }
    else
    {
        log_error("Failed to load texture at %s", path);
        stbi_image_free(localBuffer);

        return NULL;
    }
}

void deleteTexture(unsigned int* textureID)
{
    GLCall(glDeleteTextures(1, textureID));
    free(textureID);
}

void bindTexture(const unsigned int* textureID)
{
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, *textureID));
}

void bindTextureToSlot(const unsigned int* textureID, unsigned int slot)
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, *textureID));
}

void unbindTexture()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}