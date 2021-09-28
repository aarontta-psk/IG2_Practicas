#pragma once

#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <SDL_keycode.h>

using namespace Ogre;

class EntityIG : public OgreBites::InputListener
{
public:
	EntityIG(SceneNode* node, std::string name = "");
	~EntityIG() {};

	inline SceneNode* getNode() { return mNode; };

	virtual inline bool keyPressed(const OgreBites::KeyboardEvent& evt) { return true; };

protected:
	SceneNode* mNode;
	SceneManager* mSM;
};

