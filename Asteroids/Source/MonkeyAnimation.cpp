//------------------------------------------------------------------------------
//
// File Name:	MonkeyAnimation.cpp
// Author(s):	Student name here
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"				// Precompiled header
#include "MonkeyAnimation.h"	// Class file

using namespace Beta;

// STUDENT CODE GOES HERE


MonkeyAnimation::MonkeyAnimation() : Beta::Component("MonkeyAnimation"),
	idleAnimation(0), walkAnimation(0), jumpAnimation(0),
	currentState(StateIdle), nextState(StateIdle) {

}

// Initialize this component (happens at object creation).
void MonkeyAnimation::Initialize() {
	animator = GetOwner()->GetComponent<Beta::Animator>();
	idleAnimation = animator->GetAnimationIndex("mIdle");
	walkAnimation = animator->GetAnimationIndex("mWalk");
	jumpAnimation = animator->GetAnimationIndex("mJump");
	animator->Play(idleAnimation);
	animator->SetPlaybackSpeed(1.0f);
	
	physics = GetOwner()->GetComponent<Beta::RigidBody>();
	transform = GetOwner()->GetComponent<Beta::Transform>();

	originalScale = transform->GetScale();
}

// Fixed update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void MonkeyAnimation::Update(float dt) {
	UNREFERENCED_PARAMETER(dt);
	ChooseNextState();
	ChangeCurrentState();
	FlipSprite();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Choose the correct state based on velocity.
void MonkeyAnimation::ChooseNextState() {
	Beta::Vector2D vel = physics->GetVelocity();
	if (vel.y != 0) {
		nextState = StateJump;
	} else if (vel.x != 0) {
		nextState = StateWalk;
	} else {
		nextState = StateIdle;
	}
}

// Change states and start the appropriate animation.
void MonkeyAnimation::ChangeCurrentState() {
	if (currentState != nextState) {
		currentState = nextState;
		switch (currentState) {
		default:
		case StateIdle:
			animator->Play(idleAnimation);
			break;
		case StateWalk:
			animator->Play(walkAnimation);
			break;
		case StateJump:
			animator->Play(jumpAnimation);
			break;
		}
	}
}

// Flip the sprite based on velocity and current state.
void MonkeyAnimation::FlipSprite() const {
	Beta::Vector2D vel = physics->GetVelocity();
	if (currentState != StateIdle) {
		if (vel.x < 0) {
			transform->SetScale(Beta::Vector2D(-originalScale.x, originalScale.y));
		} else if (vel.x > 0) {
			transform->SetScale(originalScale);
		}
	}
}


// Create extra component functions - DO NOT REMOVE
COMPONENT_SUBCLASS_DEFINITION(MonkeyAnimation)
