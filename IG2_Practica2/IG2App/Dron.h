#ifndef DRON_H_
#define DRON_H_

#include "OgreTimer.h"

#include "EntidadIG.h"
#include "BrazoDron.h"

using namespace Ogre;

class Dron : public EntidadIG
{
	enum class State { MOVING, ROTATING_LEFT, ROTATING_RIGHT };

public:
	Dron(SceneNode* node, int numAspas, int nBrazos);
	virtual ~Dron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void receiveEvent(Message message, EntidadIG* entidad) override;
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	void disableLight() { light->setVisible(false); };

private:
	SceneNode* mSphereNode;
	SceneNode** mBrazosNodes;
	BrazoDron** arrayBrazos;
	bool detenido;

	SceneNode* lightNode;
	Light* light;

	Ogre::Timer* myTimer;
	State state;

	int numAspas, numBrazos;
};
#endif