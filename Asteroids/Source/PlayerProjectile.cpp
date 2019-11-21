//------------------------------------------------------------------------------
//
// File Name:	PlayerProjectile.cpp
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
#include "PlayerProjectile.h"
#include "PlayerShip.h"
#include "Asteroid.h"

//------------------------------------------------------------------------------

using namespace Beta;


// STUDENT CODE GOES HERE


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default constructor
PlayerProjectile::PlayerProjectile() : Beta::Component("PlayerProjectile") {

}

// Initialize this component (happens at object creation).
void PlayerProjectile::Initialize() {
	RegisterEventHandler(GetOwner(), "CollisionStarted", &PlayerProjectile::OnCollisionStarted);
}

// Set the object that spawned this object
void PlayerProjectile::SetSpawner(PlayerShip* player) {
	m_spawner = player;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// The collision handling function for Asteroids.
// Params:
//	 event = The collision event object.
void PlayerProjectile::OnCollisionStarted(const Beta::Event& event) {
	if (((CollisionEvent&)event).otherObject.GetName() == "Asteroid") {
		//hit an asteroid, increment points by the asteroids point value
		m_spawner->AddPoints(((CollisionEvent&)event).otherObject.GetComponent<Asteroid>()->GetPointValue());
		GetOwner()->Destroy();
		UnregisterEventHandlers();
	}
}



//------------------------------------------------------------------------------

// Extra component stuff - DO NOT REMOVE
COMPONENT_SUBCLASS_DEFINITION(PlayerProjectile)
