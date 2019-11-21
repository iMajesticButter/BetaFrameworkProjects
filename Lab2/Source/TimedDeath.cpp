//------------------------------------------------------------------------------
//
// File Name:	TimedDeath.cpp
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
#include "TimedDeath.h"

//-------------------------------------------------------------------------------

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Params:
//   timeUntilDeath = Amount of time until the object self-destructs.
TimedDeath::TimedDeath(float _timeUntilDeath) : Beta::Component("TimedDeath"),
	timeUntilDeath(_timeUntilDeath) {

}

// Update function for this component.
// Params:
//   dt = The (fixed) change in time since the last step.
void TimedDeath::Update(float dt) {
	timeUntilDeath -= dt;
	if (timeUntilDeath <= 0) {
		GetOwner()->Destroy();
	}
}

// Write object data to file
// Params:
//   parser = The parser that is writing this object to a file.
void TimedDeath::Serialize(Beta::FileStream& parser) const {
	
	parser.WriteVariable<float>("timeUntilDeath", timeUntilDeath);
}

// Read object data from a file
// Params:
//   parser = The parser that is reading this object's data from a file.
void TimedDeath::Deserialize(Beta::FileStream& parser) {
	parser.ReadVariable<float>("timeUntilDeath", timeUntilDeath);
}

// Student code goes here.

// Extra component functionality - DO NOT REMOVE
COMPONENT_SUBCLASS_DEFINITION(TimedDeath)

//------------------------------------------------------------------------------
