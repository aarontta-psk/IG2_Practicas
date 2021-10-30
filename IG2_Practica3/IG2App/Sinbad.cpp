#include "Sinbad.h"
#include <iostream>

Sinbad::Sinbad(SceneNode* node) : EntidadIG(node)
{
	simbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(simbad);
	InitialiceAnimation("RunBase");
	InitialiceAnimation("RunTop");
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	AddTimeToAnimation("RunBase", evt.timeSinceLastFrame);
	AddTimeToAnimation("RunTop", evt.timeSinceLastFrame);
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
