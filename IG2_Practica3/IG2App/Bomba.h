#ifndef BOMBA_H_
#define BOMBA_H_

#include "EntityIG.h"

using namespace Ogre;

class Bomba : public EntityIG
{
public:
	Bomba(SceneNode* node, int dur, int despl);
	~Bomba() {};

	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	AnimationState* animationState;
};
#endif