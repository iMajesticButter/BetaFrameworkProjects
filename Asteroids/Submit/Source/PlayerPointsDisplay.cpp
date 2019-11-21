//------------------------------------------------------------------------------
//
// File Name:	PlayerPointsDisplay.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework Project 1: Asteroids
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"

#include "PlayerPointsDisplay.h"
#include <Area.h>

#include <sstream>

using namespace Beta;

// Default constructor
PlayerPointsDisplay::PlayerPointsDisplay() : Beta::Component("PlayerPointsDisplay"), m_initialized(false) {

}

// Initialize this component (happens at object creation).
void PlayerPointsDisplay::Initialize() {

	m_text = new GameObject("PointsText");

	Area* transform = new Area(0, 0);
	
	SpriteText* textComponent = new SpriteText("TEST", ResourceGetFont("Arial.ttf 24"), false, 50u);
	textComponent->SetColor(Colors::Aqua);

	m_text->AddComponent(transform);
	m_text->AddComponent(textComponent);

	GetSpace()->GetObjectManager().AddObject(*m_text);

	m_initialized = true;

	UpdatePoints(0);

}

// set what player this component belongs to
void PlayerPointsDisplay::SetPlayer(unsigned player) {
	m_playerNum = player;
	UpdatePoints(0);
}

// set update the points text with the new points value
void PlayerPointsDisplay::UpdatePoints(float points) {
	if (!m_initialized)
		return;
	std::stringstream strstm;
	strstm << "Player " << m_playerNum << " points: " << points;
	m_text->GetComponent<SpriteText>()->SetText(strstm.str());

	//set the text position
	//have to hard-code things because thay are broken....
	Vector2D windowExtents = GetSpace()->GetCamera().GetScreenWorldDimensions().extents;
	Area* textArea = m_text->GetComponent<Area>();

	textArea->SetSize(Vector2D(0.01f, 0.01f));

	textArea->SetScale(Vector2D(0.2f, 0.2f));

	float offset = 0.3f;

	textArea->SetTranslation(Vector2D(-windowExtents.x-(strstm.str().size()*0.25f) + offset, windowExtents.y - (0.26f * (m_playerNum-1))));
}

COMPONENT_SUBCLASS_DEFINITION(PlayerPointsDisplay)