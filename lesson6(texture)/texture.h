#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Texture
{
public:
    Texture(const char *filename);
    ~Texture();

    GLuint texId() { return _texId; }

private:
    unsigned char *_loadData(const char *filename);
    void _decodeBmp(const unsigned char *data);

private:
    GLuint _texId = 0;
    int _width = 0;
    int _height = 0;
    unsigned char *_pixData = nullptr;
};
