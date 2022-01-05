#ifndef AVION_H_
#define AVION_H_

#include <OgreTimer.h>
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>

#include "../EntityIG.h"

#include "../s02_windmill/AspasMolino.h"

class Avion : public EntityIG
{
	enum class State { MOVING, ROTATING_LEFT, ROTATING_RIGHT, EXPLOSION, DEATH };

public:
	Avion(SceneNode* node);
	void receiveEvent(Message message, EntityIG* entidad) override;
	virtual inline bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	SceneNode* mCuerpoNode;
	SceneNode* mAlaINode;
	SceneNode* mAlaDNode;
	AspasMolino* mHeliceINode;
	AspasMolino* mHeliceDNode;
	SceneNode* mFrenteNode;
	SceneNode* mPilotoNode;

	SceneNode* lightNode;
	Light* light;
	bool detenido, manualControl;

	SceneNode* mPSNode;
	ParticleSystem* explosionParticle;

	Ogre::Timer* myTimer;
	State state;
};
#endif