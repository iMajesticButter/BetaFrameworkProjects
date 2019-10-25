#include "stdafx.h"

#include "Lab1.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <Windows.h>

// Constructor
Lab1::Lab1() : Beta::BetaObject("Lab1"), pi((float)M_PI), lineLength(2.0f), rotationalVelocity(1.0f/60.0f) {

}

// Initialize the memory associated with the Lab1 level.
void Lab1::Initialize() {
	std::cout << "Lab1::Initialize" << std::endl;
	angle1 = pi / 2;
	angle2 = pi / 2;
	angle3 = pi / 2;

	//set background Color to white
	EngineGetModule(Beta::GraphicsEngine)->SetBackgroundColor(Beta::Colors::White);

	//set angles to match system time
	SYSTEMTIME lt = { 0 };
	GetLocalTime(&lt);

	angle1 -= (float)lt.wSecond * pi/30;
	angle2 -= (float)lt.wMinute * pi/30;
	angle3 -= (float)lt.wHour * pi/6;

}

// Update the Lab1 level.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Lab1::Update(float dt) {
	using namespace Beta;

	DebugDraw* debug = EngineGetModule(DebugDraw);
	GraphicsEngine* Graphics = EngineGetModule(GraphicsEngine);
	Camera* cam = &Graphics->GetDefaultCamera();

	debug->AddCircle(Vector2D(0, 0), lineLength+0.2f, *cam, Colors::Blue);

	//angles
	angle1 -= (rotationalVelocity*pi*2) * dt;
	angle2 -= ((rotationalVelocity*pi*2) / 60) * dt;
	angle3 -= (((rotationalVelocity*pi*2) / 60) / 12) * dt;


	//get line vectors
	//make second hand snap into place
	float sHandAngle = ((int)(angle1 * 30 / pi)) * pi / 30;

	//std::cout << sHandAngle * 57.2958 << std::endl;

	p = Vector2D(cos(sHandAngle), sin(sHandAngle)) * lineLength;
	q = Vector2D(cos(angle2), sin(angle2)) * lineLength/1.2f;
	r = Vector2D(cos(angle3), sin(angle3)) * lineLength/1.4f;

	//draw markings
	for (int i = 0; i < 60; ++i) {
		float length = lineLength / 8;
		if (i % 5 == 0) {
			length *= 2;
		}

		Vector2D start = Vector2D(cos(i * pi / 30), sin(i * pi / 30)) * (lineLength + 0.2f);
		Vector2D end = start.Normalized() * ((lineLength + 0.2f) - length);

		debug->AddLineToList(start, end, Colors::Blue);

	}

	//draw hands
	debug->AddLineToList(Vector2D(0), p, Colors::Red);
	debug->AddLineToList(Vector2D(0), q, Colors::Black);
	debug->AddLineToList(Vector2D(0), r, Colors::Grey);

	debug->EndLineList(*cam);

}

// Free memory associated with the Lab1 level.
void Lab1::Shutdown() {
	std::cout << "Lab1::Shutdown" << std::endl;
}
