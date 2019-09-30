#include "stdafx.h";

#include "level1.h"

namespace levels {

	using Beta::DebugDraw;
	using Beta::Vector2D;
	using Beta::Vector3D;

	Level1::Level1() : Beta::BetaObject("Level1") {

	}
	Level1::~Level1() {

	}


	void Level1::Load() {

	}
	void Level1::Initialize() {

	}
	void Level1::Update(float dt) {
		//UNREFERENCED_PARAMETER(dt);
		std::cout << "Update dt: " << 1/dt << std::endl;
		DebugDraw* debug = EngineGetModule(DebugDraw);
		//debug->AddCircle(Vector2D(0, 0), 20, EngineGetModule(Beta::GraphicsEngine)->GetDefaultCamera(), Beta::Colors::Blue);
		debug->AddLineToList(Vector2D(0, 0), Vector2D(1, 1), Beta::Colors::Blue);
	}
	void Level1::FixedUpdate(float dt) {
		//UNREFERENCED_PARAMETER(dt);
		std::cout << "FixedUpdate dt: " << dt << std::endl;
	}
	void Level1::Shutdown() {

	}
	void Level1::Unload() {

	}
}