#ifndef ESFERACURSED_H_
#define ESFERACURSED_H_

#include <OgreTimer.h>
#include <OgreParticleSystem.h>

#include "../EntityIG.h"

using namespace Ogre;

class EsferaCursed : public EntityIG
{
public:
	EsferaCursed(SceneNode* node, Vector3 scale, Vector3 pos);
	~EsferaCursed() {};

	virtual void receiveEvent(Message message, EntityIG* entidad);
private:
	SceneNode* mExplosionNode;
	Entity* ent = nullptr;
};
#endif