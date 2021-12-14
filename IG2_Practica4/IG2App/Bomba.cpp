#include "Bomba.h"

#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyframe.h>
#include <iostream>

Bomba::Bomba(SceneNode* node, int dur, int despl) : EntityIG(node), detenida(false)
{
	std::cout << dur << " " << despl;
	ent = mSM->createEntity("uv_sphere.mesh");
	mNode->attachObject(ent);
	//mNode->setScale(0.01, 0.01, 0.01);
	//ent->setMaterialName("Practica2/TesellatedBomb");
	ent->setMaterialName("Practica2/BombaAgujerosLuz");

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

	mExplosionNode = node->createChildSceneNode();
	mExplosionNode->setVisible(false);
	myTimer = new Timer();

	explosionParticles = mSM->createParticleSystem("psSmokeBomb", "Practica1/BombExplosion");
	explosionParticles->setEmitting(false);
	mExplosionNode->attachObject(explosionParticles);
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt)
{
	if (explosionParticles->getEmitting() && myTimer->getMilliseconds() >= 5000)
		explosionParticles->setEmitting(false);

	if (detenida) return;
	animationState->addTime(evt.timeSinceLastFrame);
}

void Bomba::receiveEvent(Message message, EntityIG* entidad)
{
	if (message.id_ == BOMB && entidad != this)
	{
		detenida == true;
		mExplosionNode->setVisible(true);
		mNode->setVisible(false);
		explosionParticles->setEmitting(true);
		myTimer->reset();
	}
}

inline bool Bomba::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_t)
	{
		sendEvent({ BOMB }, this);
		detenida = true;
	}
	else if(evt.keysym.sym == SDLK_1)
	{
		ent->setMaterialName("Practica2/TesellatedBomb");
	}
	else if (evt.keysym.sym == SDLK_2)
	{
		ent->setMaterialName("Practica2/BombaAgujerosLuz");
	}
	else if (evt.keysym.sym == SDLK_3)
	{
		ent->setMaterialName("Practica2/BombaAgujeros");
	}

	return true;
}
