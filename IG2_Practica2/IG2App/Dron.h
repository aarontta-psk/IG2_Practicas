#ifndef DRON_H_
#define DRON_H_

#include "EntidadIG.h"
#include "BrazoDron.h"

using namespace Ogre;

class Dron : public EntidadIG
{
public:
	Dron(SceneNode* node, int numAspas, int nBrazos);
	~Dron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mSphereNode;
	SceneNode** mBrazosNodes;
	BrazoDron** arrayBrazos;

	int numAspas, numBrazos;
};
#endif