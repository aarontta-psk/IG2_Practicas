#pragma once

#include "IG2App.h"
#include "AspasMolino.h"

using namespace Ogre;

class RotorDron : public OgreBites::InputListener
{
public:
	RotorDron(SceneNode* node, SceneManager* mSM, int numAspas);
	~RotorDron();
	const SceneNode* getNode() { return mNode; } //Para poder trasladar desde fuera, pero sin cambiar el nodo en sí

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mNode;
	SceneNode* mEsferaNode;
	SceneNode* mHelicesNode;
	AspasMolino* mAspas;

	int numAspas;
};

RotorDron::RotorDron(SceneNode* node, SceneManager* mSM, int numAspas)
{
	//Creacion
	mNode = node->createChildSceneNode();
	mEsferaNode = mNode->createChildSceneNode();
	mHelicesNode = mNode->createChildSceneNode();

	mEsferaNode->attachObject(mSM->createEntity("sphere.mesh"));
	mAspas = new AspasMolino(mHelicesNode, mSM, numAspas);
	mAspas->SetAdornosVisibility(false);

	//Escalas
	float sphereScale = 2;
	float helicesScale = 0.75f;
	mEsferaNode->setScale(sphereScale, sphereScale, sphereScale);
	mHelicesNode->setScale(helicesScale, helicesScale, helicesScale);

	//Posiciones
	mAspas->getNode()->setPosition(0, 260, 0);
	mAspas->getNode()->pitch(Degree(90));
}

RotorDron::~RotorDron() //No se si hay que hacer algo aqui
{
	delete mAspas;
}

bool RotorDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mAspas->keyPressed(evt); // --- Apartado 14 ---
	return true;
}

