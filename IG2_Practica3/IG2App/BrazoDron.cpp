#include "BrazoDron.h"

BrazoDron::BrazoDron(SceneNode* node, int nAspas, double rotation) : EntityIG(node)
{
	//Creacion
	mCilindroNode = mNode->createChildSceneNode();
	mRotorNode = mNode->createChildSceneNode();

	Entity* brazo = mSM->createEntity("Barrel.mesh");
	brazo->setMaterialName("Practica1/Junction");
	mCilindroNode->attachObject(brazo);
	rotor = new RotorDron(mRotorNode, nAspas, rotation);

	//Escalas
	float cilindroScale = 16.5f;
	float yScaleMultiplier = 3.0f;
	float dronScale = 0.55f;
	mCilindroNode->setScale(cilindroScale, cilindroScale * yScaleMultiplier, cilindroScale);
	mRotorNode->setScale(dronScale, dronScale, dronScale);

	//Posiciones
	mCilindroNode->pitch(Degree(-90));
	mCilindroNode->setPosition(0, 0, 250);

	numAspas = nAspas;
}

BrazoDron::~BrazoDron()
{
	delete rotor;
}

bool BrazoDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	rotor->keyPressed(evt);
	return true;
}

void BrazoDron::frameRendered(const Ogre::FrameEvent& evt)
{
	rotor->frameRendered(evt);
}
