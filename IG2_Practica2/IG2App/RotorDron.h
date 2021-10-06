#ifndef ROTORDRON_H_
#define ROTORDRON_H_

#include "EntidadIG.h"
#include "AspasMolino.h"

using namespace Ogre;

class RotorDron : public EntidadIG
{
public:
	RotorDron(SceneNode* node,int numAspas, double rotation = 2);
	~RotorDron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mEsferaNode;
	SceneNode* mHelicesNode;
	AspasMolino* mAspas;

	int numAspas;
};
#endif