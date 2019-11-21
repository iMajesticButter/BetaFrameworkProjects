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
#include "Level2.h"
#include "Asteroids.h"

#include "MonkeyAnimation.h"
#include "MonkeyMovement.h"

#include <memory>

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Creates an instance of Level 1.
Level1::Level1() : Beta::Level("Level1"), time(0) {
	
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


	ScanlineEffect = new Beta::PostEffect("scanline.frag");
	ScanlineEffect->GetProgram().SetUniform("in_time", time);

	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*ScanlineEffect);

	WarpEffect = new Beta::PostEffect("warp.frag");
	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*WarpEffect);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Level1::Update(float dt) {
	Beta::Input* in = EngineGetModule(Beta::Input);

	if (in->IsKeyDown('1')) {
		GetSpace()->RestartLevel();
	} else if (in->IsKeyDown('2')) {
		GetSpace()->SetLevel<Level2>();
	} else if (in->IsKeyDown('3')) {
		GetSpace()->SetLevel<Asteroids>();
	}

	
	time += dt;
	ScanlineEffect->GetProgram().SetUniform("in_time", time);

}

// Shutdown any memory associated with the Level1 game state.
void Level1::Shutdown() {
	std::cout << "Level1::Shutdown" << std::endl;

	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	delete ScanlineEffect;
	delete WarpEffect;
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