//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
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

// Levels
#include "Level1.h"
#include "Level2.h"

// Components
#include "PlayerShip.h"
#include "TimedDeath.h"
#include "ScreenWrap.h"
#include "Cutable.h"
#include "Asteroid.h"
#include "PlayerProjectile.h"
#include "PlayerPointsDisplay.h"
#include "PlayerLives.h"

#include "Asteroids.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Main function
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR command_line, _In_ int show)
{
	// Enable memory leak checking
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	// Unused parameters
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(show);
	UNREFERENCED_PARAMETER(instance);

	// Add additional modules to engine
	using namespace Beta;
	EngineCore& engine = EngineCore::GetInstance();
	SpaceManager& spaceManager = *engine.AddModule<SpaceManager>();
	GameObjectFactory& factory = *engine.AddModule<GameObjectFactory>();
	EventManager& eventManager = *engine.AddModule<EventManager>();

	UNREFERENCED_PARAMETER(eventManager);

	// Set initial game state to the second level.
	spaceManager.GetDefaultSpace().SetLevel<Asteroids>();

	// TO DO: Register PlayerShip and TimedDeath
	factory.RegisterComponent<PlayerShip>();
	factory.RegisterComponent<TimedDeath>();
	factory.RegisterComponent<ScreenWrap>();
	factory.RegisterComponent<Cutable>();
	factory.RegisterComponent<Asteroid>();
	factory.RegisterComponent<PlayerProjectile>();
	factory.RegisterComponent<PlayerPointsDisplay>();
	factory.RegisterComponent<PlayerLives>();

	// Game engine goes!
	StartupSettings settings;
	settings.windowWidth = 1920;
	settings.windowHeight = 1080;
	settings.fullscreen = false;
	engine.Start(settings);

	return 0;
}
