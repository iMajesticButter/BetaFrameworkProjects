//------------------------------------------------------------------------------
//
// File Name:	Cutable.h
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework Project 1: Asteroids
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include <tuple>

class Cutable : public Beta::Component {

	COMPONENT_SUBCLASS_DECLARATION(Cutable);

public:

	//default constructor
	Cutable();
	
	//initialize the component
	void Initialize() override;

	//update the component
	// params:
	//	dt = the delta time since last frame
	void Update(float dt) override;
	//void Shutdown() override;
	
	//! split the object into two copies of itself and return a pair of pointers to those copies
	/*!
	  /param point the starting point of the line to cut the object along
	  /param directionVec a vector in the direction of the line to cut the object along
	  /returns a pair of GameObject pointers that are the new objects created after cutting
	*/
	std::pair<Beta::GameObject*, Beta::GameObject*> PsudoSliceObject();

private:

	Beta::Transform* m_transform;
	float m_angle;
	float m_range;

};