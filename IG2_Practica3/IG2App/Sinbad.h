#ifndef SINBAD_H_
#define SINBAD_H_

#include "EntidadIG.h"

using namespace Ogre;

class Sinbad : public EntidadIG
{
public:
	Sinbad(SceneNode* node);
	virtual ~Sinbad() {};
	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	Entity* simbad;
	void InitialiceAnimation(const Ogre::String& animation);
	void AddTimeToAnimation(const Ogre::String& animation, Ogre::Real offset);
};
#endif