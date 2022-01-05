#include "EntityIG.h"

std::vector<EntityIG*> EntityIG::appListeners = std::vector<EntityIG*>(0, nullptr);

EntityIG::EntityIG(SceneNode* node, std::string name)
{
	mNode = (name.empty() ? node->createChildSceneNode() : node->createChildSceneNode(name));
	mSM = node->getCreator();
}

void EntityIG::sendEvent(Message message, EntityIG* entidad)
{
	for (EntityIG* e : appListeners)
		if (e != entidad)
			e->receiveEvent(message, entidad);
}