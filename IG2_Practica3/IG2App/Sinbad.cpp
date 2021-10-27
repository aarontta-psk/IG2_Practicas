#include "Sinbad.h"

Sinbad::Sinbad(SceneNode* node) : EntidadIG(node)
{
	mNode->attachObject(mSM->createEntity("Sinbad.mesh"));
}
