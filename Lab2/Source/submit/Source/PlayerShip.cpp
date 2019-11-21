//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.cpp
// Author(s):	
// Project:		
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PlayerShip.h"

//------------------------------------------------------------------------------

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Default constructor
	// Params:
	//   bulletArchetype = The archetype for the bullet.
	//   forwardThrust = Amount of force added to the ship when thrusters are activated.
	//   maximumSpeed  = Maximum attainable speed of the ship.
	//   rotationSpeed = Speed at which the ship rotates.
	//   bulletSpeed   = Speed at which bullets move when fired by ship.
PlayerShip::PlayerShip(Beta::Archetype _bulletArchetype, float _forwardThrust,
	float _maximumSpeed, float _rotationSpeed, float _bulletSpeed, float _angularDrag) : Beta::Component("PlayerShip"),
	forwardThrust(_forwardThrust), maximumSpeed(_maximumSpeed), rotationSpeed(_rotationSpeed),
	bulletSpeed(_bulletSpeed), angularDrag(_angularDrag), bulletArchetype(_bulletArchetype) {

}

// Initialize this component (happens at object creation).
void PlayerShip::Initialize() {
	transform = GetOwner()->GetComponent<Beta::Transform>();
	rigidBody = GetOwner()->GetComponent<Beta::RigidBody>();
	bulletArchetype = Beta::ResourceGetArchetype("Bullet");
}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void PlayerShip::Update(float dt) {
	Move();
	Rotate(dt);
	Shoot();
}

// Write object data to file
// Params:
//   parser = The parser that is writing this object to a file.
void PlayerShip::Serialize(Beta::FileStream& parser) const {
	parser.WriteVariable<float>("forwardThrust", forwardThrust);
	parser.WriteVariable<float>("maximumSpeed", maximumSpeed);
	parser.WriteVariable<float>("rotationSpeed", rotationSpeed);
	parser.WriteVariable<float>("bulletSpeed", bulletSpeed);
	parser.WriteVariable<float>("angularDrag", angularDrag);
}
// Read object data from a file
// Params:
//   parser = The parser that is reading this object's data from a file.
void PlayerShip::Deserialize(Beta::FileStream& parser) {
	parser.ReadVariable<float>("forwardThrust", forwardThrust);
	parser.ReadVariable<float>("maximumSpeed", maximumSpeed);
	parser.ReadVariable<float>("rotationSpeed", rotationSpeed);
	parser.ReadVariable<float>("bulletSpeed", bulletSpeed);
	parser.ReadVariable<float>("angularDrag", angularDrag);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Move forward when up arrow is pressed
void PlayerShip::Move() const {
	Beta::Input* in = EngineGetModule(Beta::Input);

	float force = 0.0f;

	if (in->IsKeyDown('W')) {
		++force;
	}
	if (in->IsKeyDown('S')) {
		--force;
	}

	float angle = transform->GetRotation();
	Beta::Vector2D forceVec = Beta::Vector2D(cos(angle), sin(angle));

	rigidBody->AddForce(forceVec * force * forwardThrust);

	float mag = rigidBody->GetVelocity().Magnitude();

	if (mag > maximumSpeed) {
		rigidBody->SetVelocity(rigidBody->GetVelocity().Normalized()*maximumSpeed);
	}

}

// Rotate when left or right arrow key is pressed
void PlayerShip::Rotate(float dt) const {
	Beta::Input* in = EngineGetModule(Beta::Input);
	
	float angForce = 0.0f;

	if (in->IsKeyDown('A')) {
		++angForce;
	}
	if (in->IsKeyDown('D')) {
		--angForce;
	}


	//this rotate system is better, 
	//in space you dont stop rotating when you stop 
	//applying angular force!
	rigidBody->SetAngularVelocity(rigidBody->GetAngularVelocity() + (angForce * rotationSpeed)*dt);

	//angular drag
	if ((angForce >= 0 && rigidBody->GetAngularVelocity() < 0) ||
		(angForce <= 0 && rigidBody->GetAngularVelocity() > 0)) {
		rigidBody->SetAngularVelocity(rigidBody->GetAngularVelocity()*angularDrag);
	}
}

// Shoot projectiles when space is pressed
void PlayerShip::Shoot() const {
	Beta::Input* in = EngineGetModule(Beta::Input);

	if (in->CheckTriggered(VK_SPACE)) {
		Beta::GameObject* bullet = new Beta::GameObject(*bulletArchetype);

		float angle = transform->GetRotation();
		Beta::Vector2D velVec = Beta::Vector2D(cos(angle), sin(angle));

		Beta::Transform* bTransform = bullet->GetComponent<Beta::Transform>();

		bTransform->SetTranslation(transform->GetTranslation() + velVec*0.25f);
		bTransform->SetRotation(transform->GetRotation());

		velVec *= bulletSpeed;
		velVec += rigidBody->GetVelocity();

		bullet->GetComponent<Beta::RigidBody>()->SetVelocity(velVec);

		GetOwner()->GetSpace()->GetObjectManager().AddObject(*bullet);
	}
}

// Extra component functionality - DO NOT REMOVE
COMPONENT_SUBCLASS_DEFINITION(PlayerShip)

//------------------------------------------------------------------------------
