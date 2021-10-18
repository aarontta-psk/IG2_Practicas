#ifndef AVION_H_
#define AVION_H_

class AspasMolino;

#include "EntidadIG.h"
#include "OgreTimer.h"

class Avion : public EntidadIG
{
	enum class State { MOVING, ROTATING_LEFT, ROTATING_RIGHT };

public:
	Avion(SceneNode* node);
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

	Ogre::Timer* myTimer;
	State state;
};
#endif