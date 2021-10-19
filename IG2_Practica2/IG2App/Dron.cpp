#include "Dron.h"

Dron::Dron(SceneNode* node, int nAspas, int nBrazos) : EntidadIG(node), state(State::MOVING)
{
	//Creacion
	mSphereNode = mNode->createChildSceneNode();

	mBrazosNodes = new Ogre::SceneNode * [nBrazos];
	arrayBrazos = new BrazoDron * [nBrazos];
	double angleStep = 360.0 / nBrazos;
	for (int i = 0; i < nBrazos; i++)
	{
		mBrazosNodes[i] = mNode->createChildSceneNode();

		arrayBrazos[i] = new BrazoDron(mBrazosNodes[i], nAspas, (i % 2 == 0) ? 2 : -2); // posible cambio

		arrayBrazos[i]->getNode()->yaw(Degree(i * angleStep));
		arrayBrazos[i]->getNode()->translate(500, 0, 0, SceneNode::TS_LOCAL); //El (gran) truco

		arrayBrazos[i]->getNode()->yaw(Degree(-90), SceneNode::TS_LOCAL);
		arrayBrazos[i]->getNode()->setScale(0.8, 0.8, 0.8);
	}

	arrayBrazos[0]->getNode()->setScale(1.2, 1.2, 1.2);

	mSphereNode->attachObject(mSM->createEntity("sphere.mesh"));
	mSphereNode->setScale(2, 2, 2);

	light = mSM->createLight();

	lightNode = mSM->createSceneNode();
	mNode->addChild(lightNode);
	lightNode->attachObject(light);

	light->setType(Light::LT_SPOTLIGHT);
	light->setDirection(Vector3(0, -1, 0));
	light->setSpotlightInnerAngle(Degree(0));
	light->setSpotlightOuterAngle(Degree(45));
	light->setSpotlightFalloff(1.0f);

	numAspas = nAspas; numBrazos = nBrazos;

	myTimer = new Timer();
}

Dron::~Dron()
{
	for (int i = 0; i < numBrazos; ++i)
		delete mBrazosNodes[i];
	delete[] mBrazosNodes;

	for (int i = 0; i < numBrazos; ++i)
		delete arrayBrazos[i];
	delete[] arrayBrazos;

	delete myTimer;
}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	for (int i = 0; i < numBrazos; i++)
		arrayBrazos[i]->keyPressed(evt);

	return true;
}

void Dron::frameRendered(const Ogre::FrameEvent& evt)
{
	SceneNode* parentNode = mNode->getParentSceneNode();

	switch (state) {
	case State::MOVING: {
		if (myTimer->getMilliseconds() >= 2000) {
			state = (State)(rand() % 2 + 1);
			myTimer->reset();
		}
		else {
			mNode->translate(0, -315, 0, SceneNode::TS_LOCAL);
			mNode->roll(Ogre::Degree(-3), SceneNode::TS_LOCAL);
			mNode->translate(0, 315, 0, SceneNode::TS_LOCAL);
		}
		break;
	}
	case State::ROTATING_LEFT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = State::MOVING;
			myTimer->reset();
		}
		else
			mNode->yaw(Ogre::Degree(1), SceneNode::TS_LOCAL);
		break;
	}
	case State::ROTATING_RIGHT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = State::MOVING;
			myTimer->reset();
		}
		else
			mNode->yaw(Ogre::Degree(-1), SceneNode::TS_LOCAL);
		break;
	}
	}
}