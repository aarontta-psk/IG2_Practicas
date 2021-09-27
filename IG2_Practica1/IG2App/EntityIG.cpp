#include "EntityIG.h"

EntityIG::EntityIG(SceneNode* node, std::string name)
{
	mNode = (name.empty() ? node->createChildSceneNode() : node->createChildSceneNode(name));
	mSM = node->getCreator();
}