#ifndef EsferaCursed_H_
#define EsferaCursed_H_

#include "EntityIG.h"
#include <OgreTimer.h>
#include <OgreParticleSystem.h>

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