//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
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
#include "Level1.h"

#include "PlayerController.h"

//------------------------------------------------------------------------------

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Creates an instance of Level 1.
Level1::Level1()
	: Level("Level 1"), testObject(nullptr), walkIndex(0), jumpIndex(0), idleIndex(0)
{
}

// Initialize the memory associated with the Level1 game state.
void Level1::Initialize()
{
	std::cout << "Level1: Initialize" << std::endl;

	// Create a new game object
	testObject = new GameObject("TestObject");

	// Create a transform component at 0,0 with scale 300,300
	Transform* transform = new Transform(2.0f, 0.0f);
	transform->SetRotation(0.5f);
	transform->SetScale(Vector2D(2.0f, 6.0f));
	testObject->AddComponent(transform);

	// Create a sprite component
	Sprite* sprite = new Sprite();
	sprite->SetColor(Color(1.0f,0.5f,0.1f));
	testObject->AddComponent(sprite);

	// Load a texture and sprite source
	TexturePtr texture = ResourceGetTexture("Monkey.png");
	// NOTE: SpriteSource requires the following:
	// texture, name, numCols, numRows
	SpriteSourcePtr spriteSource
		= std::make_shared<SpriteSource>(texture, "Monkey", 3, 5);

	// Set sprite's sprite source
	sprite->SetSpriteSource(spriteSource);

	// Create an animator component, add to object
	Animator* animator = new Animator();
	testObject->AddComponent(animator);

	// Load animations
	// NOTE: Animation requires the following:
	// name, spriteSource, frameCount, frameStart, frameDuration
	AnimationPtr walkAnimation 
		= std::make_shared<Animation>("MonkeyWalk", spriteSource,
			8, 0, 0.15f);

	// Add animations to animator
	walkIndex = animator->AddAnimation(walkAnimation);

	// Add player controller component to Monkey
	testObject->AddComponent(new PlayerController());

	// Add the object to the object manager
	GetSpace()->GetObjectManager().AddObject(*testObject);

	// Play animation
	animator->Play(walkIndex);

	scanline = new Beta::PostEffect("scanline.frag");
	scanline->GetProgram().SetUniform("in_time", time);

	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*scanline);

	effect = new Beta::PostEffect("testPost.frag");
	effect->GetProgram().SetUniform("WARP_FACTOR", warp);
	effect->GetProgram().SetUniform("SCALE_FACTOR", scale);

	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*effect);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Level1::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	Input* input = EngineGetModule(Input);

	// If the user presses the '1' key, restart the current level
	if (input->CheckTriggered('1'))
		GetSpace()->RestartLevel();

	if (input->IsKeyDown('W')) {
		scale += 1*dt;
	}
	if (input->IsKeyDown('S')) {
		scale -= 1 * dt;
	}
	if (input->IsKeyDown('Q')) {
		warp += 1 * dt;
	}
	if (input->IsKeyDown('A')) {
		warp -= 1 * dt;
	}

	time += dt;

	scanline->GetProgram().SetUniform("in_time", time);
	effect->GetProgram().SetUniform("WARP_FACTOR", warp);
	effect->GetProgram().SetUniform("SCALE_FACTOR", scale);
}

// Shutdown any memory associated with the Level1 game state.
void Level1::Shutdown()
{
	std::cout << "Level1::Shutdown" << std::endl;

	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	delete effect;
	delete scanline;

	//delete testObject;
}
