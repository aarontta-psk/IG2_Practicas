#ifndef DRON_H_
#define DRON_H_

#include "EntidadIG.h"
#include "BrazoDron.h"

using namespace Ogre;

class Dron : public EntidadIG
{
public:
	Dron(SceneNode* node, int numAspas, int nBrazos);
	virtual ~Dron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mSphereNode;
	SceneNode** mBrazosNodes;
	BrazoDron** arrayBrazos;

	SceneNode* lightNode;
	Light* light;

	int numAspas, numBrazos;
};
#endif