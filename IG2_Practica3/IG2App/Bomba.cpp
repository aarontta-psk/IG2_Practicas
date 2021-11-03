#include "Bomba.h"

#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyframe.h>
#include <iostream>

Bomba::Bomba(SceneNode* node, int dur, int despl) : EntityIG(node)
{
	std::cout << dur << " " << despl;
	Entity* ent = mSM->createEntity("Barrel.mesh");
	mNode->attachObject(ent);
	ent->setMaterialName("Practica1/Checker");

	Animation* anim = mSM->createAnimation("AnimVV", dur);

	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	Vector3 src(0, 0, 1);
	Real durPaso = dur / 4.0;

	TransformKeyFrame* kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen

	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: arriba
	kf->setTranslate(Vector3::UNIT_Y * despl * 2);
	kf->setRotation(src.getRotationTo(Vector3(1, 0, 1)));

	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: origen

	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: abajo
	kf->setTranslate(-Vector3::UNIT_Y * despl * 2);
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));

	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: origen

	animationState = mSM->createAnimationState("AnimVV");

	animationState->setLoop(true);
	animationState->setEnabled(true);
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}