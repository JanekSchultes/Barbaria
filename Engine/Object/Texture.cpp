
#include "Texture.h"


Texture::Texture() {
    bufferID = 0;
}

Texture::Texture(const char* texturePath) {
    stbi_set_flip_vertically_on_load(true);
    textureBuffer = stbi_load(texturePath, &textureWidth, &textureHeight, &bitsPerPixel, 4);
    glGenTextures(1, &bufferID);
    glBindTexture(GL_TEXTURE_2D, bufferID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bufferID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    //glDeleteTextures(1, &bufferID);
    //stbi_image_free(textureBuffer);
}
