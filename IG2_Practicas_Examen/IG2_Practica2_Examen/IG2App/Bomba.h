#ifndef BOMBA_H_
#define BOMBA_H_

#include "EntityIG.h"
#include <OgreTimer.h>
#include <OgreParticleSystem.h>

using namespace Ogre;

class Bomba : public EntityIG
{
public:
	Bomba(SceneNode* node, int dur, int despl);
	~Bomba() {};

	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual void receiveEvent(Message message, EntityIG* entidad);

private:
	AnimationState* animationState;
	SceneNode* mExplosionNode;
	ParticleSystem* explosionParticles;
	Entity* ent = nullptr;

	Ogre::Timer* myTimer;
	bool detenida;
protected:
	virtual inline bool keyPressed(const OgreBites::KeyboardEvent& evt);
};
#endif