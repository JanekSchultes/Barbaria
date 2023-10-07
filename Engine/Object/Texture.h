#ifndef TEXTURE
#define TEXTURE

#include "../../Utils/math_utils.h"
#include <GL/glew.h>
#include <memory.h>
#include <map>
#include <string>

#define BITS_PER_PIXEL 3

#include "../../Lib/stb_image.h"

class Texture {
public:
    Texture();
    /* Generates a Texture object from a given texture path */
    Texture(const char* texturePath);
    void bind();
    void unbind();
    ~Texture();
protected:
private:
    GLuint bufferID;
    int textureWidth;
    int textureHeight;
    int bitsPerPixel;
    stbi_uc* textureBuffer;
};

#endif

