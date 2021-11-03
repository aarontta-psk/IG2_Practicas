#ifndef AVION_H_
#define AVION_H_

class AspasMolino;

#include "EntityIG.h"
#include "OgreTimer.h"

class Avion : public EntityIG
{
	enum class State { MOVING, ROTATING_LEFT, ROTATING_RIGHT };

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

	Ogre::Timer* myTimer;
	State state;
};
#endif