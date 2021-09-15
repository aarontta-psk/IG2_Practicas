#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	//else if (evt.keysym.sym == SDLK_???)

	return true;
}

void IG2App::shutdown()
{
	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;  mTrayMgr = nullptr;
	delete mCamMgr; mCamMgr = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
	// do not forget to call the base first
	IG2ApplicationContext::setup();

	mSM = mRoot->createSceneManager();

	// register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);

	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	addInputListener(mTrayMgr);

	addInputListener(this);
	setupScene();
}

void IG2App::setupScene(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// finally something to render

	//COMENTARIO SOBRE FORMAS DE CREAR LAS ESFERAS
	//Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
	//Ogre::Entity* ent = mSM->createEntity("Sphere", Ogre::SceneManager::PT_SPHERE);

	//Create nodes

	//--- Apartado 1 ---

	//Fields
	const int numHourNodes = 12;
	const int radius = 750;
	const int angleStep = 360 / numHourNodes;

	mHourNode = new Ogre::SceneNode * [numHourNodes];
	mClockNode = mSM->getRootSceneNode()->createChildSceneNode("nClock");
	mClockNode->setScale(0.4, 0.4, 0.4); //Era o esto o echar la camara hacia atras y esto es mas facil

	for (int i = 0; i < numHourNodes; i++)
	{
		float angle = Ogre::Math::DegreesToRadians(i * angleStep);
		std::string nodeName = "Hora " + std::to_string(i);
		mHourNode[i] = mClockNode->createChildSceneNode(nodeName);
		mHourNode[i]->attachObject(mSM->createEntity("sphere.mesh"));
		mHourNode[i]->setPosition(Ogre::Math::Sin(angle) * radius, Ogre::Math::Cos(angle) * radius, 0);
	}

	//--- Apartado 2 ---
	//Cambiar de tama�o los nodos de las horas pares
	//for (int i = 0; i < numHourNodes; i += 2)
	//{
	//	std::string nodeName = "Hora " + std::to_string(i);
	//	mSM->getSceneNode(nodeName)->setScale(0.5, 0.5, 0.5);
	//}

	//--- Apartado 3 ---

	//Hay algunos numeros cableados, pero esta cableado
	//en funcion del radio del reloj, si se cambia el radio, todo sigue bien

	mClockHours = mClockNode->createChildSceneNode("nHoras");
	mClockMinutes = mClockNode->createChildSceneNode("nMinutes");
	mClockSeconds = mClockNode->createChildSceneNode("nSeconds");

	mClockHours->attachObject(mSM->createEntity("cube.mesh"));
	mClockMinutes->attachObject(mSM->createEntity("cube.mesh"));
	mClockSeconds->attachObject(mSM->createEntity("cube.mesh"));

	int clockCubeScale = radius / 107; //107 es el numero que queda bien, no tiene otra explicacion
	mClockHours->setScale(clockCubeScale * 0.7f, clockCubeScale / 10.0f, 1);
	mClockMinutes->setScale(clockCubeScale, clockCubeScale / 18.0f, 1);
	mClockSeconds->setScale(clockCubeScale, clockCubeScale / 36.0f, 1);

	float displacementX = radius / 4.0f;
	float displacementY = radius / 3.25f;
	mClockHours->setPosition(displacementX, 0, 0);
	mClockMinutes->setPosition(0, displacementY, 0);
	mClockSeconds->setPosition(0, -displacementY, 0);

	mClockMinutes->roll(Ogre::Degree(90));
	mClockSeconds->roll(Ogre::Degree(90));

	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}

