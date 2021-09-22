#pragma once

#include "IG2App.h"
#include "AspasMolino.h"

using namespace Ogre;

class Molino : public OgreBites::InputListener
{
public:
	Molino(SceneNode* node, SceneManager* mSM, int numAspas);
	~Molino();
	const SceneNode* getNode() { return mNode; } //Para poder trasladar desde fuera, pero sin cambiar el nodo en s�

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mNode;
	SceneNode* mEsferaTecho;
	SceneNode* mCilindroCuerpo;
	SceneNode* mAspasNode;
	AspasMolino* mAspas;
};

Molino::Molino(SceneNode* node, SceneManager* mSM, int numAspas)
{
	//Creacion
	mNode = node->createChildSceneNode();
	mEsferaTecho = mNode->createChildSceneNode();
	mCilindroCuerpo = mNode->createChildSceneNode();
	mAspasNode = mNode->createChildSceneNode();

	mEsferaTecho->attachObject(mSM->createEntity("sphere.mesh"));
	mCilindroCuerpo->attachObject(mSM->createEntity("Barrel.mesh"));
	mAspas = new AspasMolino(mNode, mSM, numAspas);           // E L ( G R A N ) T R U C O
	//mAspas = new AspasMolino(mAspasNode, mSM, numAspas);    // nodo fantasma

	//Escalas
	mAspas->getNode()->setScale(0.7, 0.7, 0.7);
	float sphereScale = 1.55f;
	mEsferaTecho->setScale(sphereScale, sphereScale, sphereScale);
	float multiplier = 12; //Comodidad
	mCilindroCuerpo->setScale(5 * multiplier, 6 * multiplier, 5 * multiplier);

	//Posiciones
	mAspas->getNode()->setPosition(0, 200, 168);
	mEsferaTecho->setPosition(0, 200, 0);
}

Molino::~Molino() //No se si hay que hacer algo aqui
{
	delete mAspas;
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mAspas->keyPressed(evt);
	if (evt.keysym.sym == SDLK_h) {
		mAspas->getNode()->translate(0, -200, -168, SceneNode::TS_LOCAL);
		mAspas->getNode()->yaw(Degree(2)); // E L ( G R A N ) T R U C O
		mAspas->getNode()->translate(0, 200, 168, SceneNode::TS_LOCAL);

		//mAspasNode->yaw(Degree(2));  
	}
	return true;
}

