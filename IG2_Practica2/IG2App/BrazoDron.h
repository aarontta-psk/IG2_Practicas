#ifndef BRAZODRON_H_
#define BRAZODRON_H_

#include "EntityIG.h"
#include "RotorDron.h"

using namespace Ogre;

class BrazoDron : public EntityIG
{
public:
	BrazoDron(SceneNode* node, int numAspas, double rotation = 2);
	~BrazoDron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mSphereNode;
	SceneNode* mBrazosNode;
	RotorDron* mAspas;

	int numAspas;
};
#endif