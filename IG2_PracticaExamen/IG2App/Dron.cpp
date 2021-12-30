#include "Dron.h"
#include <iostream>
#include "Randomized.h"

using namespace Randomized;

int Dron::numDrones = 0;

Dron::Dron(SceneNode* node, int nAspas, int nBrazos, bool control) : EntityIG(node), state(State::MOVING), detenido(false), control(control)
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

	Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName(control ? "Practica1/Red" :"Practica1/Cursed");
	mSphereNode->attachObject(sphere);
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

	if(!control) numDrones++;
}

Dron::~Dron()
{
	// lo hacemos invisible para no tener que eliminarlo fuera del mSM, ya se encargara el de hacerlo
	mNode->setVisible(false);

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

void Dron::receiveEvent(Message message, EntityIG* entidad)
{
	switch (message.id_)
	{
	case DEFAULT:
		break;
	case STOP_ALL_ENTITIES:
		detenido = !detenido;
		static_cast<Entity*>(mSphereNode->getAttachedObjects()[0])->setMaterialName("Practica1/Red");
		break;
	case CHECK_COLLISION:
	{
		if (control) return;
		AxisAlignedBox aab1 = mNode->_getWorldAABB();
		AxisAlignedBox aab2 = entidad->getNode()->_getWorldAABB();

		if (aab1.intersects(aab2))
		{
			appListeners.erase(std::remove(appListeners.begin(), appListeners.end(), this));
			numDrones--;
			std::cout << numDrones << '\n';
			if (numDrones == 0) sendEvent({ ALL_DRON_DEAD }, nullptr);
			delete this;
		}
		break;
	}
	case ALL_DRON_DEAD:
		if (!control) return;
		static_cast<Entity*>(mSphereNode->getAttachedObjects()[0])->setMaterialName("Practica1/Yellow");
		break;
	default:
		break;
	}
}

void Dron::frameRendered(const Ogre::FrameEvent& evt)
{
	for (int i = 0; i < numBrazos; i++)
		arrayBrazos[i]->frameRendered(evt);

	if (detenido) return;
	SceneNode* parentNode = mNode->getParentSceneNode();

	switch (state) {
	case State::MOVING: {
		if (myTimer->getMilliseconds() >= GetRandomInt(1000, 2000)) {
			state = (State)(rand() % 2 + 1);
			myTimer->reset();
		}
		else {
			mNode->translate(0, -315, 0, SceneNode::TS_LOCAL);
			mNode->roll(Ogre::Degree(-1), SceneNode::TS_LOCAL);
			mNode->translate(0, 315, 0, SceneNode::TS_LOCAL);
		}
		break;
	}
	case State::ROTATING_LEFT: {
		if (myTimer->getMilliseconds() >= GetRandomInt(800, 1200)) {
			state = State::MOVING;
			myTimer->reset();
		}
		else
			mNode->yaw(Ogre::Degree(1), SceneNode::TS_LOCAL);
		break;
	}
	case State::ROTATING_RIGHT: {
		if (myTimer->getMilliseconds() >= GetRandomInt(800, 1200)) {
			state = State::MOVING;
			myTimer->reset();
		}
		else
			mNode->yaw(Ogre::Degree(-1), SceneNode::TS_LOCAL);
		break;
	}
	}
}