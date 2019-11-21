//------------------------------------------------------------------------------
//
// File Name:	PlayerPointsDisplay.h
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework Project 1: Asteroids
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Component.h"

class PlayerShip;

namespace Beta
{
	struct Event;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class PlayerPointsDisplay : public Beta::Component {
public:

	// Default constructor
	PlayerPointsDisplay();

	// Initialize this component (happens at object creation).
	void Initialize() override;

	// set what player this component belongs to
	void SetPlayer(unsigned player);

	// set update the points text with the new points value
	void UpdatePoints(float points);

private:

	//private variables
	unsigned m_playerNum;
	
	Beta::GameObject* m_text;

	bool m_initialized;

	COMPONENT_SUBCLASS_DECLARATION(PlayerPointsDisplay)

};