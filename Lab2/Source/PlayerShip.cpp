//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.cpp
// Author(s):	
// Project:		
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PlayerShip.h"

//------------------------------------------------------------------------------

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default constructor
	// Params:
	//   bulletArchetype = The archetype for the bullet.
	//   forwardThrust = Amount of force added to the ship when thrusters are activated.
	//   maximumSpeed  = Maximum attainable speed of the ship.
	//   rotationSpeed = Speed at which the ship rotates.
	//   bulletSpeed   = Speed at which bullets move when fired by ship.
PlayerShip::PlayerShip(Beta::Archetype bulletArchetype, float forwardThrust,
	float maximumSpeed, float rotationSpeed, float bulletSpeed) : Beta::Component("PlayerShip") {

}

// Initialize this component (happens at object creation).
void PlayerShip::Initialize() {

}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void PlayerShip::Update(float dt) {

}

// Write object data to file
// Params:
//   parser = The parser that is writing this object to a file.
void PlayerShip::Serialize(Beta::FileStream& parser) const {

}

// Read object data from a file
// Params:
//   parser = The parser that is reading this object's data from a file.
void PlayerShip::Deserialize(Beta::FileStream& parser) {

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Move forward when up arrow is pressed
void PlayerShip::Move() const {

}

// Rotate when left or right arrow key is pressed
void PlayerShip::Rotate() const {

}

// Shoot projectiles when space is pressed
void PlayerShip::Shoot() const {

}

// Extra component functionality - DO NOT REMOVE
COMPONENT_SUBCLASS_DEFINITION(PlayerShip)

//------------------------------------------------------------------------------
