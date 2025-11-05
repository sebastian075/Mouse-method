#include "mouse.h"
#include <Windows.h>
#include <iostream>

void mouse_c::InitMouse() {
    g_pointerDevice = CreateSyntheticPointerDevice( PT_PEN, 1, POINTER_FEEDBACK_DEFAULT );
    if (!g_pointerDevice) {
        std::cerr << "Failed to create pen.\n";
        g_pointerDevice = NULL;
    }
    else {
        std::cout << "pen initialized.\n";
    }
}

bool mouse_c::MoveMouse_Synthetic( int x, int y, bool pressed ) {
    if (!g_pointerDevice) return false;

    POINTER_TYPE_INFO pointerInfo = {};
    pointerInfo.type = PT_PEN;

    pointerInfo.penInfo.pointerInfo.pointerType = PT_PEN;
    pointerInfo.penInfo.pointerInfo.pointerId = 0;
    pointerInfo.penInfo.pointerInfo.ptPixelLocation.x = x;
    pointerInfo.penInfo.pointerInfo.ptPixelLocation.y = y;

    pointerInfo.penInfo.pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE;

    if (pressed)
        pointerInfo.penInfo.pointerInfo.pointerFlags |= POINTER_FLAG_DOWN | POINTER_FLAG_INCONTACT;
    else
        pointerInfo.penInfo.pointerInfo.pointerFlags |= POINTER_FLAG_UP;

    pointerInfo.penInfo.penFlags = PEN_FLAG_NONE;
    pointerInfo.penInfo.penMask = PEN_MASK_PRESSURE | PEN_MASK_ROTATION ;
    pointerInfo.penInfo.rotation = 0;
    pointerInfo.penInfo.pressure = pressed ? 32000 : 0;

    bool result = InjectSyntheticPointerInput( g_pointerDevice, &pointerInfo, 1 );
    if (!result)
        std::cerr << "InjectSyntheticPointerInput failed.\n";
    return result;
}

void mouse_c::SmoothMoveTo( int targetX, int targetY, int steps ) {
    POINT currentPos;
    GetCursorPos( &currentPos );

    for (int i = 1; i <= steps; i++) {
        int x = currentPos.x + ((targetX - currentPos.x) * i) / steps;
        int y = currentPos.y + ((targetY - currentPos.y) * i) / steps;
        MoveMouse_Synthetic( x, y, false );
        Sleep( 5 );
    }
}

