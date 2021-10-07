#include "Avion.h"
#include "AspasMolino.h"
#include <iostream>

Avion::Avion(SceneNode* node) : EntidadIG(node, "")
{
	mCuerpoNode = mNode->createChildSceneNode();
	mAlaINode = mNode->createChildSceneNode();
	mAlaDNode = mNode->createChildSceneNode();
	mHeliceINode = new AspasMolino(mNode, 5);
	mHeliceDNode = new AspasMolino(mNode, 5);
	mFrenteNode = mNode->createChildSceneNode();
	mPilotoNode = mNode->createChildSceneNode();

	mCuerpoNode->attachObject(mSM->createEntity("sphere.mesh"));
	mCuerpoNode->setScale(2, 2, 2);

	float helicesScale = 0.25f;
	mHeliceINode->getNode()->setScale(Vector3(helicesScale));
	mHeliceDNode->getNode()->setScale(Vector3(helicesScale));

	float helicesOffsetX = 350.0f;
	float helicesOffseZ = 80.0f;
	mHeliceINode->getNode()->translate(-helicesOffsetX, 0, helicesOffseZ);
	mHeliceDNode->getNode()->translate( helicesOffsetX, 0, helicesOffseZ);

	mFrenteNode->attachObject(mSM->createEntity("Barrel.mesh"));
	mFrenteNode->translate(0, 0, 175);
	mFrenteNode->setScale(Vector3(20.f));
	mFrenteNode->pitch(Degree(90));

	mPilotoNode->attachObject(mSM->createEntity("ninja.mesh"));
	mPilotoNode->translate(0, 200, 0);
	mPilotoNode->yaw(Degree(180));

	float alasScaleX = 8.0f;
	float alasScaleY = 0.4f;
	float alasScaleZ = 1.5f;
	float alasOffset = 150.0f;
	mAlaINode->attachObject(mSM->createEntity("cube.mesh"));
	mAlaDNode->attachObject(mSM->createEntity("cube.mesh"));
	mAlaINode->setScale(alasScaleX, alasScaleY, alasScaleZ);
	mAlaDNode->setScale(alasScaleX, alasScaleY, alasScaleZ);
	mAlaINode->translate(-alasOffset, 0, 0);
	mAlaDNode->translate( alasOffset, 0, 0);
}

inline bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mHeliceDNode->keyPressed(evt);
	mHeliceINode->keyPressed(evt);
	return true;
}
