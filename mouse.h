#pragma once
#include <Windows.h>

class mouse_c {
public:
	HSYNTHETICPOINTERDEVICE g_pointerDevice = NULL;
	void InitMouse();
	bool MoveMouse_Synthetic( int x, int y, bool pressed = false );
	void SmoothMoveTo( int targetX, int targetY, int steps = 20 );
};
inline mouse_c Mouse;