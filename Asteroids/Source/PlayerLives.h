//------------------------------------------------------------------------------
//
// File Name:	PlayerLives.h
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework Project 1: Asteroids
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include <Component.h>

namespace Beta {
	class Sprite;
	struct Event;
}

class PlayerLives : public Beta::Component {
public:

	// default contructor
	PlayerLives();

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

	friend class PlayerShip;

private:

	// The collision handling function for Player.
	// Params:
	//	 event = The collision event object.
	void OnCollisionStarted(const Beta::Event& event);

	//! change the number of ship icons in the lives display
	/*!
	  /param lives the number of ship icons to display
	*/
	void UpdateLivesDisplay(int lives);

	//properties
	float m_deathTime;
	unsigned m_maxlives;

	//variables
	float m_timer;
	unsigned m_lives;
	bool m_dead;

	Beta::Sprite* m_sprite;

	Beta::PostEffect* m_grayscale;

	std::vector<Beta::GameObject*> m_shipIcons;

	COMPONENT_SUBCLASS_DECLARATION(PlayerLives)

};