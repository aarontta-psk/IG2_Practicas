#include "Avion.h"
#include "AspasMolino.h"
#include <iostream>

Avion::Avion(SceneNode* node) : EntidadIG(node, ""), state(State::MOVING)
{
	mCuerpoNode = mNode->createChildSceneNode();
	mAlaINode = mNode->createChildSceneNode();
	mAlaDNode = mNode->createChildSceneNode();
	mHeliceINode = new AspasMolino(mNode, 5);
	mHeliceDNode = new AspasMolino(mNode, 5);
	mFrenteNode = mNode->createChildSceneNode();
	mPilotoNode = mNode->createChildSceneNode();

	Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Red");
	mCuerpoNode->attachObject(sphere);
	mCuerpoNode->setScale(2, 2, 2);

	float helicesScale = 0.25f;
	mHeliceINode->getNode()->setScale(Vector3(helicesScale));
	mHeliceDNode->getNode()->setScale(Vector3(helicesScale));

	float helicesOffsetX = 350.0f;
	float helicesOffseZ = 80.0f;
	mHeliceINode->getNode()->translate(-helicesOffsetX, 0, helicesOffseZ);
	mHeliceDNode->getNode()->translate( helicesOffsetX, 0, helicesOffseZ);

	Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/Brown");
	mFrenteNode->attachObject(cilindro);
	mFrenteNode->translate(0, 0, 175);
	mFrenteNode->setScale(Vector3(20.f));
	mFrenteNode->pitch(Degree(90));

	Entity* ninja = mSM->createEntity("ninja.mesh");
	ninja->setMaterialName("Practica1/Yellow");
	mPilotoNode->attachObject(ninja);
	mPilotoNode->translate(0, 200, 0);
	mPilotoNode->yaw(Degree(180));

	float alasScaleX = 4.0f;
	float alasScaleY = 0.4f;
	float alasScaleZ = 1.5f;
	float alasOffset = 300.0f;
	Entity* ala = mSM->createEntity("cube.mesh");
	ala->setMaterialName("Practica1/Alas");
	mAlaINode->attachObject(ala);

	ala = mSM->createEntity("cube.mesh");
	ala->setMaterialName("Practica1/Alas");
	mAlaDNode->attachObject(ala);
	mAlaINode->setScale(alasScaleX, alasScaleY, alasScaleZ);
	mAlaDNode->setScale(alasScaleX, alasScaleY, alasScaleZ);
	mAlaINode->translate(-alasOffset, 0, 0);
	mAlaDNode->translate( alasOffset, 0, 0);

	light = mSM->createLight();

	lightNode = mSM->createSceneNode();
	mNode->addChild(lightNode);
	lightNode->attachObject(light);

	light->setType(Light::LT_SPOTLIGHT);
	light->setDirection(Vector3(0, -1, 0));
	light->setSpotlightInnerAngle(Degree(0));
	light->setSpotlightOuterAngle(Degree(45));
	light->setSpotlightFalloff(1.0f);
	
	myTimer = new Timer();
}

inline bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mHeliceDNode->keyPressed(evt);
	mHeliceINode->keyPressed(evt);
	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	SceneNode* parentNode = mNode->getParentSceneNode();

	switch (state) {
	case State::MOVING: {
		if (myTimer->getMilliseconds() >= 2000) {
			state = (State)(rand() % 2 + 1);
			myTimer->reset();
		}
		break;
	}
	case State::ROTATING_LEFT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = State::MOVING;
			myTimer->reset();
		}
		else
			parentNode->yaw(Ogre::Degree(1));
		break;
	}
	case State::ROTATING_RIGHT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = State::MOVING;
			myTimer->reset();
		}
		else
			parentNode->yaw(Ogre::Degree(-1));
		break;
	}
	}
	parentNode->pitch(Ogre::Degree(1));
}