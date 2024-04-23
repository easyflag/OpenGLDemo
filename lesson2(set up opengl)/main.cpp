#include <Windows.h>
#include <gl/GL.h>

// #pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nShowCmd)
{
    // register window
    WNDCLASSEX wndClass;
    memset(&wndClass, 0, sizeof(WNDCLASSEX));
    wndClass.cbClsExtra = 0;
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = NULL;
    wndClass.hCursor = NULL;
    wndClass.hIcon = NULL;
    wndClass.hIconSm = NULL;
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = wndProc;
    wndClass.lpszClassName = "GLWindow";
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_VREDRAW | CS_HREDRAW;

    ATOM atom = RegisterClassEx(&wndClass);
    if (!atom) {
        return 1;
    }

    // create window
    HWND hwnd = CreateWindowEx(NULL, "GLWindow", "OpenGL Window", WS_OVERLAPPEDWINDOW,
                               100, 100, 800, 600,
                               NULL, NULL, hInstance, NULL);
    if (!hwnd) {
        return 1;
    }

    // create opengl render context
    HDC hdc = GetDC(hwnd);
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nVersion = 1;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

    int pixFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixFormat, &pfd);

    HGLRC hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc); // create opengl render context complete

    // init opengl
    glClearColor(0.1, 0.5, 0.1, 0.1);

    // show window
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // handle msg loop
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // draw scene
        glClear(GL_COLOR_BUFFER_BIT);

        // present scene
        SwapBuffers(hdc); 
    }

    return 0;
}
