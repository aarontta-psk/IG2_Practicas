#ifndef MOLINO_H_
#define MOLINO_H_

#include "EntityIG.h"
#include "AspasMolino.h"

using namespace Ogre;

class Molino : public EntityIG
{
public:
	Molino(SceneNode* node, int numAspas);
	~Molino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mEsferaTecho;
	SceneNode* mCilindroCuerpo;
	SceneNode* mAspasNode;

	AspasMolino* mAspas;
};

#endif