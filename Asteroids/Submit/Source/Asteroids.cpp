#include "stdafx.h"

#include "Asteroids.h"
#include "Level1.h"
#include "Level2.h"
#include "PlayerShip.h"

#include <sstream>


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Creates an instance of the Asteroids level.
Asteroids::Asteroids() : Beta::Level("Asteroids"), asteroidSpawnInitial(3), asteroidSpawnMaximum(20), asteroidHighScore(0), time(0) {

}

// Load the resources associated with the Asteroids level.
void Asteroids::Load() {
	EngineGetModule(Beta::GraphicsEngine)->SetBackgroundColor(Beta::Colors::Black);
}

// Initialize the memory associated with the Asteroids level.
void Asteroids::Initialize() {
	UpdateScore();
	asteroidWaveCount = 0;
	asteroidSpawnCount = asteroidSpawnInitial;

	Beta::GameObject* ship = new Beta::GameObject(Beta::ResourceGetArchetype("PlayerShip"));
	playerShip = ship->GetComponent<PlayerShip>();
	GetSpace()->GetObjectManager().AddObject(*ship);

	EdgeDetectEffect = new Beta::PostEffect("edgedetect.frag");
	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*EdgeDetectEffect);

	BloomEffect = new Beta::PostEffect("bloom.frag");
	BloomEffect->GetProgram().SetUniform("resolution", EngineGetModule(Beta::WindowSystem)->GetResolution());

	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*BloomEffect);

	ChromaticAberrationEffect = new Beta::PostEffect("chromaticaberration.frag");
	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*ChromaticAberrationEffect);

	ScanlineEffect = new Beta::PostEffect("scanline.frag");
	ScanlineEffect->GetProgram().SetUniform("in_time", time);

	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*ScanlineEffect);

	WarpEffect = new Beta::PostEffect("warp.frag");
	EngineGetModule(Beta::GraphicsEngine)->PushEffect(*WarpEffect);
}

// Update the Asteroids level.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Asteroids::Update(float dt) {
	time += dt;
	if (GetSpace()->GetObjectManager().GetObjectCount("Asteroid") == 0 || EngineGetModule(Beta::Input)->CheckTriggered('L')) {
		SpawnAsteroidWave();
	}

	auto input = EngineGetModule(Beta::Input);
	if (input->IsKeyDown('1')) {
		GetSpace()->SetLevel<Level1>();
	} else if (input->IsKeyDown('2')) {
		GetSpace()->SetLevel<Level2>();
	} else if (input->IsKeyDown('3')) {
		GetSpace()->RestartLevel();
	}

	ScanlineEffect->GetProgram().SetUniform("in_time", time);

}


void Asteroids::Shutdown() {
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	EngineGetModule(Beta::GraphicsEngine)->PopEffect();
	delete EdgeDetectEffect;
	delete BloomEffect;
	delete ChromaticAberrationEffect;
	delete ScanlineEffect;
	delete WarpEffect;

	if (playerShip->GetPoints() > asteroidHighScore) {
		asteroidHighScore = playerShip->GetPoints();
		UpdateScore();
	}
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Create a single asteroid object from the archetype
void Asteroids::SpawnAsteroid(void) {
	Beta::GameObject* asteroid = new Beta::GameObject(Beta::ResourceGetArchetype("Asteroid"));
	GetSpace()->GetObjectManager().AddObject(*asteroid);
}

// Create a group of asteroids
void Asteroids::SpawnAsteroidWave(void) {
	++asteroidWaveCount;
	for (unsigned i = 0; i < asteroidSpawnCount; ++i) {
		SpawnAsteroid();
	}
	asteroidSpawnCount = asteroidSpawnCount <= asteroidSpawnMaximum ? asteroidSpawnCount + 1 : asteroidSpawnMaximum;
}

// Update the score string
void Asteroids::UpdateScore() {
	std::stringstream strstm;
	strstm << "High Score: " << asteroidHighScore;
	EngineGetModule(Beta::WindowSystem)->SetWindowTitle(strstm.str());
}