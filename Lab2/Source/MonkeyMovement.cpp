//------------------------------------------------------------------------------
//
// File Name:	MonkeyMovement.cpp
// Author(s):	Student name here
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"				// Precompiled header
#include "MonkeyMovement.h"	// Class file

using namespace Beta;

// STUDENT CODE GOES HERE

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
MonkeyMovement::MonkeyMovement() : Beta::Component("MonkeyMovement"),
monkeyWalkSpeed(3.0f), monkeyWalkSpeedAirMultiplier(0.5f),
monkeyJumpSpeed(8.0f), groundHeight(-1.5f), gravity(0.0f, -9.81f) {

}

// Initialize this component (happens at object creation).
void MonkeyMovement::Initialize() {
	transform = GetOwner()->GetComponent<Beta::Transform>();
	rigidBody = GetOwner()->GetComponent<Beta::RigidBody>();
	transform->SetTranslation(Beta::Vector2D(transform->GetTranslation().x, groundHeight));
}

// Fixed update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void MonkeyMovement::Update(float dt) {
	UNREFERENCED_PARAMETER(dt);

	MoveHorizontal();
	MoveVertical();

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Moves horizontally based on input
void MonkeyMovement::MoveHorizontal() const {

	Beta::Input* in = EngineGetModule(Beta::Input);
	float vel = 0;


	if (in->IsKeyDown('A')) {
		vel -= 1;
	}
	if (in->IsKeyDown('D')) {
		vel += 1;
	}

	//change movement to applying forces in mid air
	if (transform->GetTranslation().y > groundHeight) {
		vel *= monkeyWalkSpeedAirMultiplier;
		rigidBody->AddForce(Beta::Vector2D(vel * monkeyWalkSpeed, 0));
		vel = rigidBody->GetVelocity().x/monkeyWalkSpeed;
		if (vel > 1)
			vel = 1;
		else if (vel < -1)
			vel = -1;
		else
			return;
	}

	//set lateral velocity
	rigidBody->SetVelocity(Beta::Vector2D(vel * monkeyWalkSpeed, rigidBody->GetVelocity().y));
}

// Moves vertically based on input
void MonkeyMovement::MoveVertical() const {
	
	Beta::Input* in = EngineGetModule(Beta::Input);
	float vel = 0;

	if (transform->GetTranslation().y <= groundHeight) {
		if (in->IsKeyDown(VK_SPACE)) {
			vel = monkeyJumpSpeed;
		} else {
			vel = 0;
			transform->SetTranslation(Vector2D(transform->GetTranslation().x, groundHeight));
		}
		rigidBody->SetVelocity(Beta::Vector2D(rigidBody->GetVelocity().x, vel));
	} else {
		rigidBody->AddForce(gravity);
	}

}


// Create extra component functions - DO NOT REMOVE
COMPONENT_SUBCLASS_DEFINITION(MonkeyMovement)
