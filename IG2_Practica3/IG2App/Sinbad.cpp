#include "Sinbad.h"
#include <iostream>

Sinbad::Sinbad(SceneNode* node) : EntidadIG(node), state(State::MOVING)
{
	simbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(simbad);
	InitialiceAnimation("RunBase");
	InitialiceAnimation("RunTop");
	myTimer = new Timer();

	leftSword = mSM->createEntity("Sword.mesh");
	simbad->attachObjectToBone("Handle.L", leftSword);

	rightSword = mSM->createEntity("Sword.mesh");
	simbad->attachObjectToBone("Handle.R", rightSword);

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

void Sinbad::arma(bool armado)
{
	if (currentArma == 1)
	{
		leftSword->setVisible(armado);
		rightSword->setVisible(!armado);
	}
	else
	{
		leftSword->setVisible(!armado);
		rightSword->setVisible(armado);
	}
	this->armado = armado;
}

void Sinbad::cambiaEspada()
{
	if (currentArma == 1) currentArma = 0;
	else currentArma = 1;
	if (!armado) return;
	arma(true);
}

void Sinbad::arma()
{
	leftSword->setVisible(true);
	rightSword->setVisible(true);
}
