#pragma once

#include "IG2App.h"
#include "RotorDron.h"

using namespace Ogre;

class BrazoDron : public OgreBites::InputListener
{
public:
	BrazoDron(SceneNode* node, SceneManager* mSM, int numAspas);
	~BrazoDron();
	const SceneNode* getNode() { return mNode; } //Para poder trasladar desde fuera, pero sin cambiar el nodo en sí

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mNode;
	SceneNode* mCilindroNode;
	SceneNode* mDronNode;
	RotorDron* mAspas;

	int numAspas;
};

BrazoDron::BrazoDron(SceneNode* node, SceneManager* mSM, int numAspas)
{
	//Creacion
	mNode = node->createChildSceneNode();
	mCilindroNode = mNode->createChildSceneNode();
	mDronNode = mNode->createChildSceneNode();

	mCilindroNode->attachObject(mSM->createEntity("Barrel.mesh"));
	mAspas = new RotorDron(mDronNode, mSM, numAspas);

	//Escalas
	float cilindroScale = 16.5f;
	float yScaleMultiplier = 3.0f;
	float dronScale = 0.55f;
	mCilindroNode->setScale(cilindroScale, cilindroScale * yScaleMultiplier, cilindroScale);
	mDronNode->setScale(dronScale, dronScale, dronScale);

	//Posiciones
	mCilindroNode->pitch(Degree(-90));
	mCilindroNode->setPosition(0, 0, 250);

}

BrazoDron::~BrazoDron() //No se si hay que hacer algo aqui
{
	delete mAspas;
}

bool BrazoDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mAspas->keyPressed(evt); //Lo comento para poder descomentarlo luego lmao
	return true;
}

