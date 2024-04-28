#include "texture.h"

#include <stdio.h>

Texture::Texture(const char *filename)
{
    unsigned char *data = _loadData(filename);
    if (!data)
        return;

    if (data[0] == 'B' && data[1] == 'M')
    {
        _decodeBmp(data);
    }
    delete[] data;

    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _pixData);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    if (_pixData)
        delete[] _pixData;
}

unsigned char *Texture::_loadData(const char *filename)
{
    unsigned char *buf = nullptr;

    FILE *file = fopen(filename, "rb");
    if (!file)
        return nullptr;

    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    if (len)
    {
        rewind(file);
        buf = new unsigned char[len];
        fread(buf, sizeof(unsigned char), len, file);
    }
    fclose(file);

    return buf;
}

void Texture::_decodeBmp(const unsigned char *data)
{
    int pixelDataOffset = *(int *)(data + 10);
    _width = *(int *)(data + 18);
    _height = *(int *)(data + 22);
    int size = _width * _height * 3;
    _pixData = new unsigned char[size];
    // bgr to rgb
    for (int i = pixelDataOffset; i < size + pixelDataOffset; i += 3)
    {
        int idx = i - pixelDataOffset;
        _pixData[idx] = data[i + 2];
        _pixData[idx + 1] = data[i + 1];
        _pixData[idx + 2] = data[i];
    }
}
