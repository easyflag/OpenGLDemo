#include "texture.h"

#include <stdio.h>

Texture::Texture(const char *filename)
{
    unsigned char *data = _load(filename);

    glGenTextures(1, &_textureId);
}

Texture::~Texture()
{
}

unsigned char *Texture::_load(const char *filename)
{
    unsigned char *buf = nullptr;

    FILE *file = fopen(filename, "rb");
    if (!file)
        return nullptr;

    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    if (len) {
        rewind(file);
        buf = new unsigned char[len];
        fread(buf, sizeof(unsigned char), len, file);
    }
    fclose(file);

    return buf;
}
