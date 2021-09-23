#pragma once

#include "IG2App.h"
#include "RotorDron.h"

using namespace Ogre;

class BrazoDron : public OgreBites::InputListener
{
public:
	BrazoDron(SceneNode* node, SceneManager* mSM, int numAspas, double rotation = 2);
	~BrazoDron();
	SceneNode* getNode() { return mNode; } //Para poder trasladar desde fuera, pero sin cambiar el nodo en sí

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mNode;
	SceneNode* mSphereNode;
	SceneNode* mBrazosNode;
	RotorDron* mAspas;

	int numAspas;
};

BrazoDron::BrazoDron(SceneNode* node, SceneManager* mSM, int nAspas, double rotation)
{
	numAspas = nAspas;

	//Creacion
	mNode = node->createChildSceneNode();
	mSphereNode = mNode->createChildSceneNode();
	mBrazosNode = mNode->createChildSceneNode();

	mSphereNode->attachObject(mSM->createEntity("Barrel.mesh"));
	mAspas = new RotorDron(mBrazosNode, mSM, numAspas, rotation);

	//Escalas
	float cilindroScale = 16.5f;
	float yScaleMultiplier = 3.0f;
	float dronScale = 0.55f;
	mSphereNode->setScale(cilindroScale, cilindroScale * yScaleMultiplier, cilindroScale);
	mBrazosNode->setScale(dronScale, dronScale, dronScale);

	//Posiciones
	mSphereNode->pitch(Degree(-90));
	mSphereNode->setPosition(0, 0, 250);
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

