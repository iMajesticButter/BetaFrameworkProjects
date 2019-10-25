//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Level1.h"
#include "MonkeyAnimation.h"
#include "MonkeyMovement.h"

#include <memory>

//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 1.
Level1::Level1() : Beta::Level("Level1"), pressed(false) {
	
}

// Load the resources associated with the Level1 game state.
void Level1::Load() {
	textureMonkey = Beta::ResourceGetTexture("Monkey.png");
	spriteSourceMonkey = std::make_shared<Beta::SpriteSource>(textureMonkey, "MonkeyTexture", 3, 5);
	
	animationIdle = std::make_shared<Beta::Animation>("mIdle", spriteSourceMonkey, 1, 12, 1.0f);
	animationWalk = std::make_shared<Beta::Animation>("mWalk", spriteSourceMonkey, 8, 0, 0.1f);
	animationJump = std::make_shared<Beta::Animation>("mJump", spriteSourceMonkey, 1, 9, 1.0f);
}

// Initialize the memory associated with the Level1 game state.
void Level1::Initialize() {
	std::cout << "Level1::Initialize" << std::endl;
	EngineGetModule(Beta::GraphicsEngine)->SetBackgroundColor(Beta::Colors::White);
	GetSpace()->GetObjectManager().AddObject(*CreateMonkey());
	Beta::PostEffect* effect = new Beta::PostEffect("postEffectScanline.frag");
	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*effect);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Level1::Update(float dt) {
	UNREFERENCED_PARAMETER(dt);
	if (EngineGetModule(Beta::Input)->IsKeyDown('1')) {
		if (!pressed) {
			pressed = true;
			GetSpace()->RestartLevel();
		}
	} else {
		pressed = false;
	}
}

// Shutdown any memory associated with the Level1 game state.
void Level1::Shutdown() {
	std::cout << "Level1::Shutdown" << std::endl;
}

// Unload the resources associated with the Level1 game state.
void Level1::Unload() {
	std::cout << "Level1::Unload" << std::endl;
}

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

// Create a game object that uses the Monkey sprite source.
// Returns:
//	 A pointer to the newly constructed game object
Beta::GameObject* Level1::CreateMonkey() {
	Beta::GameObject* Monkey = new Beta::GameObject("Monkey");

	Beta::Transform* transform = new Beta::Transform;
	transform->SetScale(Beta::Vector2D(2.0f, 2.0f));

	Beta::Sprite* sprite = new Beta::Sprite;
	sprite->SetSpriteSource(spriteSourceMonkey);

	Beta::Animator* animator = new Beta::Animator;
	animator->AddAnimation(animationIdle);
	animator->AddAnimation(animationWalk);
	animator->AddAnimation(animationJump);

	Beta::RigidBody* rigidBody = new Beta::RigidBody;

	MonkeyAnimation* mAnim = new MonkeyAnimation;

	MonkeyMovement* mMove = new MonkeyMovement;

	Monkey->AddComponent(transform);
	Monkey->AddComponent(sprite);
	Monkey->AddComponent(animator);
	Monkey->AddComponent(rigidBody);
	Monkey->AddComponent(mAnim);
	Monkey->AddComponent(mMove);
	
	return Monkey;
}