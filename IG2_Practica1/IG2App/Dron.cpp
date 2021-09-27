#include "Dron.h"

Dron::Dron(SceneNode* node, int nAspas, int nBrazos) : EntityIG(node)
{
	//Creacion
	mSphereNode = mNode->createChildSceneNode();

	mBrazosNodes = new Ogre::SceneNode * [nBrazos];
	arrayBrazos = new BrazoDron * [nBrazos];
	double angleStep = 360.0 / nBrazos;
	for (int i = 0; i < nBrazos; i++)
	{
		mBrazosNodes[i] = mNode->createChildSceneNode();
		//if (i % 2 == 0) { // WIP first idea
		//	mBrazosNodes[i]->setOrientation(mBrazosNodes[i]->getOrientation().Inverse());
		//	mBrazosNodes[i]->setScale(-1, 1, -1);
		//}

		arrayBrazos[i] = new BrazoDron(mBrazosNodes[i], nAspas, (i % 2 == 0) ? 2 : -2); // posible cambio

		arrayBrazos[i]->getNode()->yaw(Degree(i * angleStep));
		arrayBrazos[i]->getNode()->translate(500, 0, 0, SceneNode::TS_LOCAL); //El (gran) truco

		arrayBrazos[i]->getNode()->yaw(Degree(-90), SceneNode::TS_LOCAL);
		arrayBrazos[i]->getNode()->setScale(0.8, 0.8, 0.8);
	}

	mSphereNode->attachObject(mSM->createEntity("sphere.mesh"));
	mSphereNode->setScale(2, 2, 2);

	numAspas = nAspas; numBrazos = nBrazos;
}

Dron::~Dron()
{
	for (int i = 0; i < numBrazos; ++i)
		delete mBrazosNodes[i];
	delete[] mBrazosNodes;

	for (int i = 0; i < numBrazos; ++i)
		delete arrayBrazos[i];
	delete[] arrayBrazos;
}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	for (int i = 0; i < numBrazos; i++)
		arrayBrazos[i]->keyPressed(evt);

	return true;
}