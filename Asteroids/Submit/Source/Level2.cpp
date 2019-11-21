//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Level1.h"
#include "Level2.h"
#include "Asteroids.h"

#include "PlayerShip.h"
#include "TimedDeath.h"
#include "ScreenWrap.h"

#include <sstream>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Creates an instance of Level 2.
Level2::Level2() : Beta::Level("Level2"), time(0) {

}

// Load the resources associated with Level 2.
void Level2::Load() {
	std::cout << "Level2::Load" << std::endl;

	EngineGetModule(Beta::GraphicsEngine)->SetBackgroundColor(Beta::Colors::Black);

	shipTexture = Beta::ResourceGetTexture("ship.png");
	//shipSpriteSource = std::make_shared<Beta::SpriteSource>(shipTexture, "Ship", 1, 1);

	bulletTexture = Beta::ResourceGetTexture("bullet.png");
	//bulletSpriteSource = std::make_shared<Beta::SpriteSource>(shipTexture, "Bullet", 1, 1);

	//bulletArchetype = Beta::Archetype(CreateBulletArchetype());

	//bulletArchetype = Beta::ResourceGetArchetype("Bullet");

}

// Initialize the memory associated with the Level 2.
void Level2::Initialize() {
	std::cout << "Level2::Initialize" << std::endl;
	//GetSpace()->GetObjectManager().AddObject(*CreateShip());
	Beta::GameObject* ship = new Beta::GameObject(Beta::ResourceGetArchetype("PlayerShip"));
	GetSpace()->GetObjectManager().AddObject(*ship);


	ScanlineEffect = new Beta::PostEffect("scanline.frag");
	ScanlineEffect->GetProgram().SetUniform("in_time", time);

	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*ScanlineEffect);

	WarpEffect = new Beta::PostEffect("warp.frag");
	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*WarpEffect);
}

// Update the Level 2.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Level2::Update(float dt) {
	std::stringstream windowTitle;

	windowTitle << "Bullets alive: " << GetSpace()->GetObjectManager().GetObjectCount("Bullet");

	EngineGetModule(Beta::WindowSystem)->SetWindowTitle(windowTitle.str());

	Beta::Input* in = EngineGetModule(Beta::Input);

	if (in->IsKeyDown('1')) {
		GetSpace()->SetLevel<Level1>();
	} else if (in->IsKeyDown('2')) {
		GetSpace()->RestartLevel();
	} else if (in->IsKeyDown('3')) {
		GetSpace()->SetLevel<Asteroids>();
	}

	time += dt;
	ScanlineEffect->GetProgram().SetUniform("in_time", time);
}

// shutdown level 2
void Level2::Shutdown() {
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	delete ScanlineEffect;
	delete WarpEffect;
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Create a game object that uses the Ship sprite source.
// Returns:
//	 A pointer to the newly constructed game object
Beta::GameObject* Level2::CreateShip(void) {
	Beta::GameObject* ship = new Beta::GameObject("PlayerShip");
	
	Beta::Transform* transform = new Beta::Transform;
	transform->SetScale(Beta::Vector2D(0.5f, 0.5f));

	Beta::Sprite* sprite = new Beta::Sprite;
	sprite->SetSpriteSource(shipSpriteSource);
	sprite->SetColor(Beta::Colors::Blue);

	Beta::RigidBody* rigidBody = new Beta::RigidBody;

	PlayerShip* playership = new PlayerShip(bulletArchetype);

	ScreenWrap* wrap = new ScreenWrap();

	Beta::ColliderCircle* col = new Beta::ColliderCircle(0.25f);

	ship->AddComponent(transform);
	ship->AddComponent(sprite);
	ship->AddComponent(rigidBody);
	ship->AddComponent(playership);
	ship->AddComponent(wrap);
	ship->AddComponent(col);

	EngineGetModule(Beta::GameObjectFactory)->SaveObjectToFile(ship);

	return ship;
}

// Create a game object archetype that uses the Bullet sprite source.
// Returns:
//	 A pointer to the newly constructed game object
Beta::GameObject* Level2::CreateBulletArchetype(void) {
	Beta::GameObject* bullet = new Beta::GameObject("Bullet");

	Beta::Transform* transform = new Beta::Transform;
	transform->SetScale(Beta::Vector2D(0.07f, 0.07f));

	Beta::Sprite* sprite = new Beta::Sprite;
	sprite->SetSpriteSource(bulletSpriteSource);
	sprite->SetColor(Beta::Colors::Yellow);

	Beta::RigidBody* rigidBody = new Beta::RigidBody;

	TimedDeath* timedDeath = new TimedDeath(5);

	bullet->AddComponent(transform);
	bullet->AddComponent(sprite);
	bullet->AddComponent(rigidBody);
	bullet->AddComponent(timedDeath);

	EngineGetModule(Beta::GameObjectFactory)->SaveObjectToFile(bullet);

	return bullet;
}

	


//----------------------------------------------------------------------------
