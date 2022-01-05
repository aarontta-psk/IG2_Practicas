#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"

#include <vector>
#include <iostream>

#include <SDL_keycode.h>

#include <OgreInput.h>
#include <OgreTrays.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreCameraMan.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

using namespace Ogre;

class EntityIG;

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener
{
public:
	explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
	virtual ~IG2App() { };   // delete -> shutdown()  

protected:
	virtual void setup();
	virtual void shutdown();
	virtual void setupScene();

	void escenaTexturas();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener

	Camera* cam = nullptr;

	Ogre::SceneManager* mSM = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;

	Ogre::SceneNode* mCamNode = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;

	Ogre::SceneNode* ficticioAvionNode = nullptr;

	std::vector<EntityIG*> vEntities;
};
#endif