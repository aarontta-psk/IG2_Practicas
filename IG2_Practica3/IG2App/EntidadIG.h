#ifndef ENTIDADIG_H_
#define ENTIDADIG_H_

#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreFrameListener.h>
#include <SDL_keycode.h>

#include "Message.h"

using namespace Ogre;

class EntidadIG : public OgreBites::InputListener
{
public:
	EntidadIG(SceneNode* node, std::string name = "");
	~EntidadIG() {};

	static void addListener(EntidadIG* entidad) { appListeners.push_back(entidad); };

	void sendEvent(Message message, EntidadIG* entidad);
	virtual void receiveEvent(Message message, EntidadIG* entidad) {};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

	inline SceneNode* getNode() { return mNode; };

protected:
	static std::vector<EntidadIG*> appListeners;

	SceneNode* mNode;
	SceneManager* mSM;

	virtual inline bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };
};

#endif