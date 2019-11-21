//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class

#include "Vector2D.h" // Vector2D

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

namespace Beta
{
	class Transform;
	class RigidBody;
	typedef std::shared_ptr<const GameObject> Archetype;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class PlayerShip : public Beta::Component
{
public:
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
	PlayerShip(Beta::Archetype bulletArchetype = Beta::Archetype(), float forwardThrust = 3.0f, 
		float maximumSpeed = 2.0f, float rotationSpeed = 6.28318f, float bulletSpeed = 4.0f, float angularDrag = 0.9f);

	// Initialize this component (happens at object creation).
	void Initialize() override;

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void Update(float dt) override;

	// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
	void Serialize(Beta::FileStream& parser) const override;

	// Read object data from a file
	// Params:
	//   parser = The parser that is reading this object's data from a file.
	void Deserialize(Beta::FileStream& parser) override;

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Move forward when up arrow is pressed
	void Move() const;

	// Rotate when left or right arrow key is pressed
	void Rotate(float dt) const;

	// Shoot projectiles when space is pressed
	void Shoot() const;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Movement properties
	float forwardThrust;
	float maximumSpeed;
	float rotationSpeed;
	float bulletSpeed;
	float angularDrag;

	// Bullet archetype
	Beta::Archetype bulletArchetype;

	// Components
	Beta::Transform* transform;
	Beta::RigidBody* rigidBody;

	COMPONENT_SUBCLASS_DECLARATION(PlayerShip)
};

//------------------------------------------------------------------------------
