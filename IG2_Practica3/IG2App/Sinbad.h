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
	Entity* leftSword;
	Entity* rightSword;

	void InitialiceAnimation(const Ogre::String& animation);
	void AddTimeToAnimation(const Ogre::String& animation, Ogre::Real offset);
	
	void arma(bool armado);
	void cambiaEspada();
	void arma();

	int currentArma; // 1 left, 0 right
	bool armado;
	Ogre::Timer* myTimer;
	State state;
};
#endif