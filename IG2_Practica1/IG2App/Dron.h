#pragma once

#include "IG2App.h"
#include "BrazoDron.h"

using namespace Ogre;

class Dron : public OgreBites::InputListener
{
public:
	Dron(SceneNode* node, SceneManager* mSM, int numAspas, int nBrazos);
	~Dron();
	SceneNode* getNode() { return mNode; } //Para poder trasladar desde fuera, pero sin cambiar el nodo en sí

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mNode;
	SceneNode* mSphereNode;
	SceneNode** mBrazosNodes;
	BrazoDron** arrayBrazos;

	int numAspas, numBrazos;
};

Dron::Dron(SceneNode* node, SceneManager* mSM, int nAspas, int nBrazos)
{
	numAspas = nAspas; numBrazos = nBrazos;

	//Creacion
	mNode = node->createChildSceneNode();
	mSphereNode = mNode->createChildSceneNode();
	
	mBrazosNodes = new Ogre::SceneNode * [nBrazos];
	arrayBrazos = new BrazoDron * [nBrazos];
	double angleStep = 360.0 / nBrazos;
	for (int i = 0; i < nBrazos; i++)
	{
		mBrazosNodes[i] = mNode->createChildSceneNode();
		//if (i % 2 == 0) {
		//	mBrazosNodes[i]->setOrientation(mBrazosNodes[i]->getOrientation().Inverse());
		//	mBrazosNodes[i]->setScale(-1, 1, -1);
		//}

		arrayBrazos[i] = new BrazoDron(mBrazosNodes[i], mSM, nAspas, (i % 2 == 0) ? 2 : -2);

		arrayBrazos[i]->getNode()->yaw(Degree(i * angleStep));
		arrayBrazos[i]->getNode()->translate(500, 0, 0, SceneNode::TS_LOCAL); //El (gran) truco

		arrayBrazos[i]->getNode()->yaw(Degree(-90), SceneNode::TS_LOCAL);
		arrayBrazos[i]->getNode()->setScale(0.8, 0.8, 0.8);
	}

	mSphereNode->attachObject(mSM->createEntity("sphere.mesh"));
	mSphereNode->setScale(2, 2, 2);
}

Dron::~Dron() //No se si hay que hacer algo aqui
{
	delete[] mBrazosNodes;
	delete[] arrayBrazos;
}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	for (int i = 0; i < numBrazos; i++)
		arrayBrazos[i]->keyPressed(evt); //Lo comento para poder descomentarlo luego lmao
	return true;
}

