#ifndef ENTITYIG_H_
#define ENTITYIG_H_

#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreFrameListener.h>
#include <SDL_keycode.h>

#include "Message.h"

using namespace Ogre;

class EntityIG : public OgreBites::InputListener
{
public:
	EntityIG(SceneNode* node, std::string name = "");
	~EntityIG() {};

	static void addListener(EntityIG* entidad) { appListeners.push_back(entidad); };

	void sendEvent(Message message, EntityIG* entidad);
	virtual void receiveEvent(Message message, EntityIG* entidad) {};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

	inline SceneNode* getNode() { return mNode; };

protected:
	static std::vector<EntityIG*> appListeners;

	SceneNode* mNode;
	SceneManager* mSM;

	virtual inline bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };
};

#endif