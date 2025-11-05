#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "mouse.h"

int main() {
    Mouse.InitMouse();
    if (!Mouse.g_pointerDevice) return 1;

    int screenWidth = GetSystemMetrics( SM_CXSCREEN );
    int screenHeight = GetSystemMetrics( SM_CYSCREEN );
    std::srand( static_cast<unsigned int>(std::time( nullptr )) );

    while (true) {
        if (GetAsyncKeyState( VK_XBUTTON2 ) & 0x8000) {
            int x = std::rand() % screenWidth;
            int y = std::rand() % screenHeight;

            Mouse.SmoothMoveTo( x, y, 30 );
            Mouse.MoveMouse_Synthetic( x, y, false );
        }
        Sleep( 10 );
    }

    if (Mouse.g_pointerDevice) {
        DestroySyntheticPointerDevice( Mouse.g_pointerDevice );
        Mouse.g_pointerDevice = NULL;
    }

    return 0;
}
