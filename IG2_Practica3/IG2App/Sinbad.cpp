#include "Sinbad.h"
#include <iostream>

Sinbad::Sinbad(SceneNode* node) : EntidadIG(node), currentWeapon(SwordStance::NONE), state(MovState::MOVING)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);

	initAnim("RunBase");
	initAnim("RunTop");

	leftSword = mSM->createEntity("Sword.mesh");
	sinbad->attachObjectToBone("Handle.L", leftSword);

	rightSword = mSM->createEntity("Sword.mesh");
	sinbad->attachObjectToBone("Handle.R", rightSword);

	swordVisibility();

	myTimer = new Timer();

	/*AnimationStateSet* aux = sinbad->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end())
	{
		auto s = it->first; ++it;
		std::cout << "\n" << s << "\n";
	}*/
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	for (auto anim : currentAnims)
		addTimeAnim(anim, evt.timeSinceLastFrame);

	//sinbadMovement();
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_s)
		cambiaEspada();
	else if (evt.keysym.sym == SDLK_e)
		arma();
	else if (evt.keysym.sym == SDLK_u)
		unarm();
	else if (evt.keysym.sym == SDLK_c)
		changeAnim((currentAnims.size() <= 1) ? newAnimsList(AnimState::RUN) : newAnimsList(AnimState::DANCE));
	else if (evt.keysym.sym == SDLK_r)
		changeAnim(newAnimsList((AnimState)(std::rand() % 9)));

	return true;
}

void Sinbad::changeAnim(const std::vector<Ogre::String> newAnims)
{
	for (auto anim : currentAnims)
		resetAnim(anim);
	currentAnims.clear();

	for (auto newAnim : newAnims)
		initAnim(newAnim);
}

void Sinbad::initAnim(const Ogre::String& animation)
{
	auto anim = sinbad->getAnimationState(animation);

	anim->setEnabled(true);
	anim->setLoop(true);

	currentAnims.push_back(animation);
}

void Sinbad::resetAnim(const Ogre::String& animation)
{
	auto anim = sinbad->getAnimationState(animation);

	anim->setEnabled(false);
	anim->setLoop(false);
	anim->setTimePosition(0);
}

std::vector<Ogre::String> Sinbad::newAnimsList(const AnimState newAnim)
{
	switch (newAnim)
	{
	case AnimState::IDLE:
		return { "IdleBase", "IdleTop" };
		break;
	case AnimState::RUN:
		return { "RunBase", "RunTop" };
		break;
	case AnimState::JUMP:
		return { "JumpLoop" };
		break;
	case AnimState::DANCE:
		return { "Dance" };
		break;
	case AnimState::HANDS_CLOSED:
		return { "HandsClosed" };
		break;
	case AnimState::HANDS_RELAXED:
		return { "HandsRelaxed" };
		break;
	case AnimState::DRAW_SWORDS:
		return { "DrawSwords" };
		break;
	case AnimState::SLICE_H:
		return { "SliceHorizontal" };
		break;
	case AnimState::SLICE_V:
		return { "SliceVertical" };
		break;
	default:
		return { };
		break;
	}
}

void Sinbad::addTimeAnim(const Ogre::String& animation, Ogre::Real offset)
{
	sinbad->getAnimationState(animation)->addTime(offset);
}

void Sinbad::cambiaEspada()
{
	switch (currentWeapon)
	{
	case SwordStance::NONE:
	case SwordStance::DUAL_SWORD:
		arma(std::rand() % 2);
		break;
	case SwordStance::L_SWORD:
		arma(true);
		break;
	case SwordStance::R_SWORD:
		arma(false);
		break;
	default:
		break;
	}
}

void Sinbad::arma(bool swHand)
{
	currentWeapon = (SwordStance)(swHand + 1);
	swordVisibility();
}

void Sinbad::arma()
{
	currentWeapon = SwordStance::DUAL_SWORD;
	swordVisibility();
}

void Sinbad::unarm()
{
	currentWeapon = SwordStance::NONE;
	swordVisibility();
}

void Sinbad::swordVisibility()
{
	switch (currentWeapon)
	{
	case SwordStance::NONE:
		leftSword->setVisible(false);
		rightSword->setVisible(false);
		break;
	case SwordStance::L_SWORD:
		leftSword->setVisible(true);
		rightSword->setVisible(false);
		break;
	case SwordStance::R_SWORD:
		leftSword->setVisible(false);
		rightSword->setVisible(true);
		break;
	case SwordStance::DUAL_SWORD:
		leftSword->setVisible(true);
		rightSword->setVisible(true);
		break;
	default:
		break;
	}
}

void Sinbad::sinbadMovement()
{
	SceneNode* parentNode = mNode->getParentSceneNode();

	switch (state) {
	case MovState::MOVING: {
		if (myTimer->getMilliseconds() >= 2000) {
			state = (MovState)(rand() % 2 + 1);
			myTimer->reset();
		}
		break;
	}
	case MovState::ROTATING_LEFT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = MovState::MOVING;
			myTimer->reset();
		}
		else
			parentNode->yaw(Ogre::Degree(1));
		break;
	}
	case MovState::ROTATING_RIGHT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = MovState::MOVING;
			myTimer->reset();
		}
		else
			parentNode->yaw(Ogre::Degree(-1));
		break;
	}
	}
	parentNode->pitch(Ogre::Degree(1));
}