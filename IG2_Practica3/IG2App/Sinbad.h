#ifndef SINBAD_H_
#define SINBAD_H_

#include "EntidadIG.h"
#include "OgreTimer.h"

using namespace Ogre;

class Sinbad : public EntidadIG
{
	enum class State { MOVING, ROTATING_LEFT, ROTATING_RIGHT };

public:
	Sinbad(SceneNode* node);
	virtual ~Sinbad() {};
	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	Entity* simbad;
	void InitialiceAnimation(const Ogre::String& animation);
	void AddTimeToAnimation(const Ogre::String& animation, Ogre::Real offset);
	Ogre::Timer* myTimer;
	State state;
};
#endif