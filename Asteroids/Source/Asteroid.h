//------------------------------------------------------------------------------
//
// File Name:	Asteroid.h
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
#include "Cutable.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

namespace Beta
{
	class Transform;
	class RigidBody;
	struct Event;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Asteroid : public Beta::Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Asteroid constructor
	// Params:
	//   speedMin = Minimum of range for asteroid movement speed.
	//   speedMax = Maximum of range for asteroid movement speed.
	//   basePointsValue = Point value for largest asteroid.
	//   sizePointsModifier = Multiplicative scale applied to points for smaller asteroids.
	//   spawnScaleModifier = Percentage of original asteroid's scale to use for new asteroids.
	Asteroid(float speedMin = 0.5f, float speedMax = 1.0f, float basePointsValue = 20,
		float sizePointsModifier = 0.5f, unsigned maxSplits = 3, float rotationRange = 3.0f);

	// Initialize this component (happens at object creation).
	void Initialize() override;

	// Get the value of this object for increasing the player's score.
	float GetPointValue() const;

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

	// The collision handling function for Asteroids.
	// Params:
	//	 event = The collision event object.
	void OnCollisionStarted(const Beta::Event& event);

	// set the asteroid position to a random corner of the screen
	void SetPosition();

	//------------------------------------------------------------------------------
	// Private Structures:
	//------------------------------------------------------------------------------

	enum corner {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Properties (save to/load from file)
	float speedMin;
	float speedMax;
	float basePointsValue;
	float sizePointsModifier;
	unsigned maxSplits;
	float rotationRange;

	unsigned m_numSplits;

	float m_pointValue;

	// Components
	Beta::Transform* m_transform;
	Beta::RigidBody* m_rigidBody;
	Cutable* m_cutable;

	COMPONENT_SUBCLASS_DECLARATION(Asteroid)
};

//------------------------------------------------------------------------------
