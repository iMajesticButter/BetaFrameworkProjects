//------------------------------------------------------------------------------
//
// File Name:	ScreenWrap.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ScreenWrap.h"

//------------------------------------------------------------------------------

using namespace Beta;


// STUDENT CODE GOES HERE


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default constructor
ScreenWrap::ScreenWrap() : Beta::Component("ScreenWrap") {

}

// Initialize this component (happens at object creation).
void ScreenWrap::Initialize() {
	transform = GetOwner()->GetComponent<Beta::Transform>();
	rigidBody = GetOwner()->GetComponent<Beta::RigidBody>();
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void ScreenWrap::Update(float dt) {
	UNREFERENCED_PARAMETER(dt);

	Vector2D velocity = rigidBody->GetVelocity();
	Vector2D pos = transform->GetTranslation();
	Vector2D scale = transform->GetScale();

	Vector2D screenSize = GetSpace()->GetCamera().GetScreenWorldDimensions().extents;

	if (velocity.x > 0 && pos.x > screenSize.x + scale.x) {
		transform->SetTranslation(Vector2D(-screenSize.x - scale.x, pos.y));
	} else if (velocity.x < 0 && pos.x < -screenSize.x - scale.x) {
		transform->SetTranslation(Vector2D(screenSize.x + scale.x, pos.y));
	}

	if (velocity.y > 0 && pos.y > screenSize.y + scale.y) {
		transform->SetTranslation(Vector2D(pos.x, -screenSize.y - scale.y));
	}
	else if (velocity.y < 0 && pos.y < -screenSize.y - scale.y) {
		transform->SetTranslation(Vector2D(pos.x, screenSize.y + scale.y));
	}
}



//------------------------------------------------------------------------------

// Extra component stuff - DO NOT REMOVE
COMPONENT_SUBCLASS_DEFINITION(ScreenWrap)
