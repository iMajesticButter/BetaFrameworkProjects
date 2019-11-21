//------------------------------------------------------------------------------
//
// File Name:	PlayerLives.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework Project 1: Asteroids
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "PlayerLives.h"

#define BLINK_SPEED 27

using namespace Beta;

// default contructor
PlayerLives::PlayerLives() : Component("PlayerLives") {

}

// Initialize this component (happens at object creation).
void PlayerLives::Initialize() {
	RegisterEventHandler(GetOwner(), "CollisionStarted", &PlayerLives::OnCollisionStarted);

	m_lives = m_maxlives;
	UpdateLivesDisplay(m_lives-1);

	m_sprite = GetOwner()->GetComponent<Sprite>();

	m_grayscale = new Beta::PostEffect("grayscale.frag");
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void PlayerLives::Update(float dt) {
	if (m_dead) {
		m_timer -= dt;
		if (m_lives > 0) {
			m_sprite->SetAlpha(round(sin(m_timer * BLINK_SPEED)+0.5f));
		}

		if (m_timer <= 0) {
			m_dead = false;
			m_sprite->SetAlpha(1);
			if (m_lives <= 0) {
				//game over
				EngineGetModule(Beta::GraphicsEngine)->PopEffect();
				delete m_grayscale;
				GetSpace()->RestartLevel();
			}
		}
	}
}

// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
void PlayerLives::Serialize(Beta::FileStream& parser) const {
	parser.WriteVariable<float>("deathTime", m_deathTime);
	parser.WriteVariable<unsigned>("maxLives", m_maxlives);
}

// Read object data from a file
// Params:
//   parser = The parser that is reading this object's data from a file.
void PlayerLives::Deserialize(Beta::FileStream& parser) {
	parser.ReadVariable<float>("deathTime", m_deathTime);
	parser.ReadVariable<unsigned>("maxLives", m_maxlives);
}

//private funcs

// The collision handling function for Player.
// Params:
//	 event = The collision event object.
void PlayerLives::OnCollisionStarted(const Beta::Event& event) {
	if (m_dead)
		return;
	if (((CollisionEvent&)event).otherObject.GetName() == "Asteroid") {
		//hit an asteroid, lose a life and start flashing
		m_dead = true;
		m_timer = m_deathTime;
		--m_lives;
		UpdateLivesDisplay(m_lives-1);
		if (m_lives <= 0) {
			//graysale post effect
			EngineGetModule(Beta::GraphicsEngine)->PushEffect(*m_grayscale);
		}
	}
}

//! change the number of ship icons in the lives display
/*!
	/param lives the number of ship icons to display
*/
void PlayerLives::UpdateLivesDisplay(int lives) {

	//remove old icons
	for (unsigned i = 0; i < m_shipIcons.size(); ++i) {
		m_shipIcons[i]->Destroy();
	}

	if (lives < 0)
		return;

	//screen world coordinates
	Vector2D worldSize = GetSpace()->GetCamera().GetScreenWorldDimensions().extents;

	//icon scale
	Vector2D iconScale(0.25f, 0.25f);

	//add new icons
	for (int i = 0; i < lives; ++i) {
		GameObject* icon = new GameObject("LivesIcon");

		//determine icon position
		Vector2D iconPos = worldSize - iconScale;
		iconPos.x -= iconScale.x * i;

		//set the icon position
		Transform* transform = new Transform(iconPos);
		//set the icon scale
		transform->SetScale(iconScale);
		//point up
		transform->SetRotation((float)M_PI / 2);

		Sprite* sprite = new Sprite();
		sprite->SetSpriteSource(ResourceGetSpriteSource("Ship"));
		sprite->SetColor(GetOwner()->GetComponent<Sprite>()->GetColor());

		icon->AddComponent(transform);
		icon->AddComponent(sprite);

		GetSpace()->GetObjectManager().AddObject(*icon);

		m_shipIcons.emplace_back(icon);
	}

}

COMPONENT_SUBCLASS_DEFINITION(PlayerLives)