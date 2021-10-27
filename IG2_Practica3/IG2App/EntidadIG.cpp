#include "EntidadIG.h"

std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(SceneNode* node, std::string name)
{
	mNode = (name.empty() ? node->createChildSceneNode() : node->createChildSceneNode(name));
	mSM = node->getCreator();
}

void EntidadIG::sendEvent(Message message, EntidadIG* entidad)
{
	for (EntidadIG* e : appListeners)
		if (e != entidad)
			e->receiveEvent(message, entidad);
}