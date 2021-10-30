#include "Sinbad.h"
#include <iostream>

Sinbad::Sinbad(SceneNode* node) : EntidadIG(node), state(State::MOVING)
{
	simbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(simbad);
	InitialiceAnimation("RunBase");
	InitialiceAnimation("RunTop");
	myTimer = new Timer();

	//AnimationStateSet* aux = simbad->getAllAnimationStates();
	//auto it = aux->getAnimationStateIterator().begin();
	//while (it != aux->getAnimationStateIterator().end())
	//{
	//	auto s = it->first; ++it;
	//	std::cout << "\n" << s << "\n";
	//}
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	AddTimeToAnimation("RunBase", evt.timeSinceLastFrame);
	AddTimeToAnimation("RunTop", evt.timeSinceLastFrame);

	SceneNode* parentNode = mNode->getParentSceneNode();

	switch (state) {
	case State::MOVING: {
		if (myTimer->getMilliseconds() >= 2000) {
			state = (State)(rand() % 2 + 1);
			myTimer->reset();
		}
		break;
	}
	case State::ROTATING_LEFT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = State::MOVING;
			myTimer->reset();
		}
		else
			parentNode->yaw(Ogre::Degree(1));
		break;
	}
	case State::ROTATING_RIGHT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = State::MOVING;
			myTimer->reset();
		}
		else
			parentNode->yaw(Ogre::Degree(-1));
		break;
	}
	}
	parentNode->pitch(Ogre::Degree(1));
}

void Sinbad::InitialiceAnimation(const Ogre::String& animation)
{
	auto anim = simbad->getAnimationState(animation);
	anim->setEnabled(true);
	anim->setLoop(true);
}

void Sinbad::AddTimeToAnimation(const Ogre::String& animation, Ogre::Real offset)
{
	simbad->getAnimationState(animation)->addTime(offset);
}
