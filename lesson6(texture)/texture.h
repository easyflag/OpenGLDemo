#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Texture
{
public:
    Texture(const char *filename);
    ~Texture();

private:
    unsigned char *_load(const char *filename);

private:
    GLuint _textureId;
};
