//------------------------------------------------------------------------------
//
// File Name:	Asteroid.cpp
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
#include "Asteroid.h"
#include "PlayerLives.h"

#include <tuple>

//------------------------------------------------------------------------------

using namespace Beta;


// STUDENT CODE GOES HERE

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Asteroid constructor
// Params:
//   speedMin = Minimum of range for asteroid movement speed.
//   speedMax = Maximum of range for asteroid movement speed.
//   basePointsValue = Point value for largest asteroid.
//   sizePointsModifier = Multiplicative scale applied to points for smaller asteroids.
//   spawnScaleModifier = Percentage of original asteroid's scale to use for new asteroids.
Asteroid::Asteroid(float _speedMin, float _speedMax, float _basePointsValue,
	float _sizePointsModifier, unsigned _maxSplits, float _rotationRange) : Beta::Component("Asteroid"),
	speedMin(_speedMin), speedMax(_speedMax), basePointsValue(_basePointsValue), sizePointsModifier(_sizePointsModifier), maxSplits(_maxSplits), rotationRange(_rotationRange), m_numSplits(0), m_pointValue(_basePointsValue) {

}

// Initialize this component (happens at object creation).
void Asteroid::Initialize() {
	m_transform = GetOwner()->GetComponent<Beta::Transform>();
	m_rigidBody = GetOwner()->GetComponent<Beta::RigidBody>();
	m_cutable = GetOwner()->GetComponent<Cutable>();
	
	RegisterEventHandler(GetOwner(), "CollisionStarted", &Asteroid::OnCollisionStarted);

	m_pointValue = basePointsValue;

	Vector2D velDir = Vector2D(cos(Random::Range(0, 360) * (float)M_PI/180.0f), sin(Random::Range(0, 360) * (float)M_PI / 180.0f));

	m_rigidBody->SetVelocity(velDir * Random::Range(speedMin, speedMax));

	SetPosition();

}

// Get the value of this object for increasing the player's score.
float Asteroid::GetPointValue() const {
	return m_pointValue;
}

// Write object data to file
		// Params:
		//   parser = The parser that is writing this object to a file.
void Asteroid::Serialize(Beta::FileStream& parser) const {
	parser.WriteVariable("speedMin", speedMin);
	parser.WriteVariable("speedMax", speedMax);
	parser.WriteVariable("basePointsValue", basePointsValue);
	parser.WriteVariable("sizePointsModifier", sizePointsModifier);
	parser.WriteVariable("maxSplits", maxSplits);
}

// Read object data from a file
// Params:
//   parser = The parser that is reading this object's data from a file.
void Asteroid::Deserialize(Beta::FileStream& parser) {
	parser.ReadVariable("speedMin", speedMin);
	parser.ReadVariable("speedMax", speedMax);
	parser.ReadVariable("basePointsValue", basePointsValue);
	parser.ReadVariable("sizePointsModifier", sizePointsModifier);
	parser.ReadVariable("maxSplits", maxSplits);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// The collision handling function for Asteroids.
// Params:
//	 event = The collision event object.
void Asteroid::OnCollisionStarted(const Beta::Event& event) {

	if (((CollisionEvent&)event).otherObject.GetName() == "Bullet") {

		((CollisionEvent&)event).otherObject.Destroy();

		if (m_numSplits >= maxSplits) {
			GetOwner()->Destroy();
		} else {
			auto newObjects = m_cutable->PsudoSliceObject();

			Beta::GameObject* obj1 = std::get<0>(newObjects);
			Beta::GameObject* obj2 = std::get<1>(newObjects);

			Beta::Vector2D vec = obj1->GetComponent<Beta::Transform>()->GetTranslation() - obj2->GetComponent<Beta::Transform>()->GetTranslation();

			vec = vec.Normalized() * Random::Range(speedMin, speedMax);

			obj1->GetComponent<Beta::RigidBody>()->SetVelocity(vec + m_rigidBody->GetVelocity());
			obj2->GetComponent<Beta::RigidBody>()->SetVelocity(-vec + m_rigidBody->GetVelocity());

			obj1->GetComponent<Beta::RigidBody>()->SetAngularVelocity(Random::Range(-rotationRange, rotationRange));
			obj2->GetComponent<Beta::RigidBody>()->SetAngularVelocity(Random::Range(-rotationRange, rotationRange));

			obj1->GetComponent<Asteroid>()->m_numSplits = m_numSplits + 1;
			obj2->GetComponent<Asteroid>()->m_numSplits = m_numSplits + 1;

			float colRadius = GetOwner()->GetComponent<Beta::ColliderCircle>()->GetRadius();
			
			// 1.41421356237 is sqrt(2)
			float newRadius = (abs(colRadius)*1.41421356237f) / 2;

			obj1->GetComponent<Beta::ColliderCircle>()->SetRadius(newRadius);
			obj2->GetComponent<Beta::ColliderCircle>()->SetRadius(newRadius);

			obj1->GetComponent<Asteroid>()->m_pointValue = m_pointValue * sizePointsModifier;
			obj2->GetComponent<Asteroid>()->m_pointValue = m_pointValue * sizePointsModifier;
		}

	} else if(((CollisionEvent&)event).otherObject.GetName() == "Asteroid"){
		//bounce asteroid off eachother (WARNING: JANKY)
		Beta::Vector2D vec = m_transform->GetTranslation() - ((CollisionEvent&)event).otherObject.GetComponent<Beta::Transform>()->GetTranslation();

		vec = vec.Normalized();

		m_rigidBody->SetVelocity((m_rigidBody->GetVelocity() + vec).Normalized() * std::max(speedMin, m_rigidBody->GetVelocity().Magnitude()/2));
		//otherRB->SetVelocity((otherRB->GetVelocity() - vec).Normalized() * otherRB->GetVelocity().Magnitude()/2);

	}

}

void Asteroid::SetPosition() {

	corner c = (corner)Random::Range(0, 3);

	Vector2D position;

	Beta::Camera* cam = &GetSpace()->GetCamera();

	Vector2D extents = cam->GetScreenWorldDimensions().extents;
	Vector2D scale = m_transform->GetScale();

	float nOffsetx = (-extents.x) - (scale.x / 2);
	float pOffsetx = (+extents.x) + (scale.x / 2);
	
	float nOffsety = (-extents.y) - (scale.y / 2);
	float pOffsety = (+extents.y) + (scale.y / 2);

	switch (c) {
	case TopLeft:
		position = Vector2D(nOffsetx, pOffsety);
		break;
	case TopRight:
		position = Vector2D(pOffsetx, pOffsety);
		break;
	case BottomLeft:
		position = Vector2D(nOffsetx, nOffsety);
		break;
	case BottomRight:
	default:
		position = Vector2D(pOffsetx, nOffsety);
		break;
	}

	m_transform->SetTranslation(position);
	m_transform->SetRotation(Random::Range(0, 360) * (float)M_PI / 180);
	m_rigidBody->SetAngularVelocity(Random::Range(-rotationRange, rotationRange));



}


//------------------------------------------------------------------------------

// Extra component stuff - DO NOT REMOVE
COMPONENT_SUBCLASS_DEFINITION(Asteroid)
