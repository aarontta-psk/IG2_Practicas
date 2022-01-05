#ifndef DRON_H_
#define DRON_H_

#include <iostream>
#include <OgreTimer.h>

#include "../../EntityIG.h"

#include "BrazoDron.h"

using namespace Ogre;

class Dron : public EntityIG
{
	enum class State { MOVING, ROTATING_LEFT, ROTATING_RIGHT };

public:
	Dron(SceneNode* node, int numAspas, int nBrazos, bool control = false);
	virtual ~Dron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void receiveEvent(Message message, EntityIG* entidad) override;
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	void disableLight() { light->setVisible(false); };
private:
	static int numDrones;
	SceneNode* mSphereNode;
	SceneNode** mBrazosNodes;
	BrazoDron** arrayBrazos;
	bool detenido;
	bool control;

	SceneNode* lightNode;
	Light* light;

	Ogre::Timer* myTimer;
	State state;

	int numAspas, numBrazos;
};
#endif