//------------------------------------------------------------------------------
//
// File Name:	Cutable.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework Project 1: Asteroids
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Cutable.h"

COMPONENT_SUBCLASS_DEFINITION(Cutable);

Cutable::Cutable() : Beta::Component("Cutable"), m_angle((float)M_PI/2) {

}

void Cutable::Initialize() {
	m_transform = GetOwner()->GetComponent<Beta::Transform>();

	m_range = (float)M_PI;
	m_angle = 0;
}

void Cutable::Update(float dt) {
	UNREFERENCED_PARAMETER(dt);
}

//void Shutdown() override;

std::pair<Beta::GameObject*, Beta::GameObject*> Cutable::PsudoSliceObject() {
	using namespace Beta;

	//create new objects
	GameObject* newObject1 = new GameObject(*GetOwner());
	GameObject* newObject2 = new GameObject(*GetOwner());

	GameObjectManager* objectManager = &GetSpace()->GetObjectManager();
	objectManager->AddObject(*newObject1);
	objectManager->AddObject(*newObject2);

	//create their new meshes (use psudo sliceing because mesh data is not exposed)
	Vector2D center = Vector2D(0, 0);

	float obj1angle = m_angle + m_range / 2;
	float obj2angle = m_angle - m_range / 2;

	Vector2D obj1P1 = Vector2D(cos(m_angle), sin(m_angle));
	Vector2D obj1P2 = Vector2D(cos(obj1angle + m_range / 2), sin(obj1angle + m_range / 2));
	Vector2D obj1tri2 = Vector2D(cos(obj1angle), sin(obj1angle));

	Vertex vobj1Center(center - obj1tri2 / 4, ((center*2) + 1) / 2);
	Vertex vobj1P1(obj1P1 - obj1tri2 / 4,     (((obj1P1*2) + 1) / 2));
	Vertex vobj1P2(obj1P2 - obj1tri2 / 4,     (((obj1P2*2) + 1) / 2));
	Vertex vobj1tri2(obj1tri2 - obj1tri2 / 4, (((obj1tri2*2) + 1) / 2));

	vobj1P1.textureCoords.y = 1 - vobj1P1.textureCoords.y;
	vobj1P2.textureCoords.y = 1 - vobj1P2.textureCoords.y;
	vobj1tri2.textureCoords.y = 1 - vobj1tri2.textureCoords.y;


	Vector2D obj2P1 = Vector2D(cos(m_angle), sin(m_angle));
	Vector2D obj2P2 = Vector2D(cos(obj2angle - m_range / 2), sin(obj2angle - m_range / 2));
	Vector2D obj2tri2 = Vector2D(cos(obj2angle), sin(obj2angle));
	
	Vertex vobj2Center(center - obj2tri2 / 4, ((center*2) + 1) / 2);
	Vertex vobj2P1(obj2P1 - obj2tri2 / 4,     (((obj2P1*2) + 1) / 2));
	Vertex vobj2P2(obj2P2 - obj2tri2 / 4,     (((obj2P2*2) + 1) / 2));
	Vertex vobj2tri2(obj2tri2 - obj2tri2 / 4, (((obj2tri2*2) + 1) / 2));

	vobj2P1.textureCoords.y = 1 - vobj2P1.textureCoords.y;
	vobj2P2.textureCoords.y = 1 - vobj2P2.textureCoords.y;
	vobj2tri2.textureCoords.y = 1 - vobj2tri2.textureCoords.y;


	
	//set their meshes

	MeshFactory* meshFactory = EngineGetModule(MeshFactory);
	meshFactory->AddTriangle(vobj1Center, vobj1P1, vobj1P2);
	meshFactory->AddTriangle(vobj1tri2, vobj1P1, vobj1P2);
	newObject1->GetComponent<Sprite>()->SetMesh(MeshPtr(meshFactory->EndCreate()));

	meshFactory->AddTriangle(vobj2Center, vobj2P1, vobj2P2);
	meshFactory->AddTriangle(vobj2tri2, vobj2P1, vobj2P2);
	newObject2->GetComponent<Sprite>()->SetMesh(MeshPtr(meshFactory->EndCreate()));
	

	//Sprite::GetMeshManager();

	newObject1->GetComponent<Cutable>()->m_range = m_range / 2;
	newObject2->GetComponent<Cutable>()->m_range = m_range / 2;

	newObject1->GetComponent<Cutable>()->m_angle = obj1angle;
	newObject2->GetComponent<Cutable>()->m_angle = obj2angle;

	float obj1OffsetAngle = m_transform->GetRotation() + obj1angle;
	float obj2OffsetAngle = m_transform->GetRotation() + obj2angle;

	Vector2D obj1Offset = Vector2D(cos(obj1OffsetAngle), sin(obj1OffsetAngle))/8;
	Vector2D obj2Offset = Vector2D(cos(obj2OffsetAngle), sin(obj2OffsetAngle))/8;

	newObject1->GetComponent<Transform>()->SetTranslation(m_transform->GetTranslation() + obj1Offset);
	newObject2->GetComponent<Transform>()->SetTranslation(m_transform->GetTranslation() + obj2Offset);

	newObject1->GetComponent<Transform>()->SetRotation(m_transform->GetRotation());
	newObject2->GetComponent<Transform>()->SetRotation(m_transform->GetRotation());
	


	//delete this object

	GetOwner()->Destroy();

	return std::pair<GameObject*, GameObject*>(newObject1, newObject2);

}