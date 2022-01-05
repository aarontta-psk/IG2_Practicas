#ifndef ROTORDRON_H_
#define ROTORDRON_H_

#include "EntityIG.h"
#include "AspasMolino.h"

using namespace Ogre;

class RotorDron : public EntityIG
{
public:
	RotorDron(SceneNode* node,int numAspas, double rotation = 2);
	~RotorDron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	SceneNode* mEsferaNode;
	SceneNode* mHelicesNode;
	AspasMolino* mAspas;

	int numAspas;
};
#endif