//------------------------------------------------------------------------------
//
// File Name:	Lab1.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Lab1
// Course:		MAT140
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "BetaObject.h" // BetaObject
#include "Vector2D.h"   // Vector2D

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Lab1 : public Beta::BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	Lab1();

	// Initialize the memory associated with the Lab1 level.
	void Initialize();

	// Update the Lab1 level.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt);

	// Free memory associated with the Lab1 level.
	void Shutdown();

private:
	//------------------------------------------------------------------------------
	// Private Consts:
	//------------------------------------------------------------------------------

	const float pi;
	const float lineLength;
	const float rotationalVelocity;
	const Beta::Vector2D origin;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Angles
	float angle1;
	float angle2;
	float angle3;

	// Points
	Beta::Vector2D p, q, r;
};
