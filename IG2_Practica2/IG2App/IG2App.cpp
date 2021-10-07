#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>

#include "Aspa.h"
#include "AspasMolino.h"
#include "Molino.h"
#include "RotorDron.h"
#include "BrazoDron.h"
#include "Dron.h"
#include "Avion.h"

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	//--- Apartado 4 ---
	else if (evt.keysym.sym == SDLK_g)
	{
		mClockNode->roll(Ogre::Degree(3));
	}
	else if (evt.keysym.sym == SDLK_h)
	{
		//--- Apartado 5 ---
		//mSphereNode->roll(Ogre::Degree(3));

		// -- Apartado 18 ---
		//ficticioDronNode->roll(Ogre::Degree(-3));

		// -- Apartado 20 ---
		dron->getNode()->translate(0, -540, 0, SceneNode::TS_LOCAL);
		dron->getNode()->roll(Ogre::Degree(-3), SceneNode::TS_LOCAL);
		dron->getNode()->translate(0, 540, 0, SceneNode::TS_LOCAL);
	}
	else if (evt.keysym.sym == SDLK_j) {
		// -- Apartado 19 ---
		//ficticioDronNode->yaw(Ogre::Degree(-3));

		// -- Apartado 20 ---
		dron->getNode()->yaw(Ogre::Degree(-3), SceneNode::TS_LOCAL);
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
	vp->setBackgroundColour(Ogre::ColourValue(0.2, 0.2, 0.2));

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

	// COMENTARIO SOBRE FORMAS DE CREAR LAS ESFERAS
	//Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
	//Ogre::Entity* ent = mSM->createEntity("Sphere", Ogre::SceneManager::PT_SPHERE);

	//Create nodes

	//--- Apartado 1 ---

	// Fields
	const int numHourNodes = 12;
	const int radius = 750;
	const double angleStep = 360.0 / numHourNodes;

	mClockNode = mSM->getRootSceneNode()->createChildSceneNode("nClock");
	mClockNode->setScale(0.4, 0.4, 0.4);

	mSphereNode = mClockNode->createChildSceneNode("nSphere");

	mHourNode = new Ogre::SceneNode * [numHourNodes];

	for (int i = 0; i < numHourNodes; i++)
	{
		float angle = Ogre::Math::DegreesToRadians(i * angleStep);
		std::string nodeName = "Hora " + std::to_string(i);
		mHourNode[i] = mSphereNode->createChildSceneNode(nodeName);
		mHourNode[i]->attachObject(mSM->createEntity("sphere.mesh"));
		mHourNode[i]->setPosition(Ogre::Math::Sin(angle) * radius, Ogre::Math::Cos(angle) * radius, 0);
	}

	//--- Apartado 2 ---
	// Cambiar de tama�o los nodos de las horas pares
	for (int i = 0; i < numHourNodes; i += 2)
	{
		std::string nodeName = "Hora " + std::to_string(i);
		mSM->getSceneNode(nodeName)->setScale(0.5, 0.5, 0.5);
	}

	//--- Apartado 3 ---

	// Hay algunos numeros cableados, pero esta cableado
	// en funcion del radio del reloj, si se cambia el radio, todo sigue bien

	mClockHours = mClockNode->createChildSceneNode("nHoras");
	mClockMinutes = mClockNode->createChildSceneNode("nMinutes");
	mClockSeconds = mClockNode->createChildSceneNode("nSeconds");

	mClockHours->attachObject(mSM->createEntity("cube.mesh"));
	mClockMinutes->attachObject(mSM->createEntity("cube.mesh"));
	mClockSeconds->attachObject(mSM->createEntity("cube.mesh"));

	// Scale
	double clockCubeScale = radius / 107; // 107 es el numero que queda bien, no tiene otra explicacion
	mClockHours->setScale(clockCubeScale * 0.7f, clockCubeScale / 10.0f, 1);
	mClockMinutes->setScale(clockCubeScale, clockCubeScale / 18.0f, 1);
	mClockSeconds->setScale(clockCubeScale, clockCubeScale / 36.0f, 1);

	// Position
	float displacementX = radius / 4.0f;
	float displacementY = radius / 3.25f;
	mClockHours->setPosition(displacementX, 0, 0);
	mClockMinutes->setPosition(0, displacementY, 0);
	//mClockSeconds->setPosition(0, -displacementY, 0); //-- Apartado 3 --
	mClockSeconds->setPosition(-displacementX * 1.1, -displacementY, 0); //-- Apartado 6 --

	// Rotation
	mClockMinutes->roll(Ogre::Degree(90));
	//mClockSeconds->roll(Ogre::Degree(90)); //-- Apartado 3 --
	mClockSeconds->roll(Ogre::Degree(45)); //-- Apartado 6 --

	// PONER EN TRUE PARA VER EJERCICIOS DEL 1 AL 6
	mClockNode->setVisible(false);

	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	// --- Apartado 7 ---
	//Aspa aspa = Aspa(mSM->getRootSceneNode());

	// --- Apartado 8 ---
	//AspasMolino* aspaMolino = new AspasMolino(mSM->getRootSceneNode(), 12);
	//addInputListener(aspaMolino);

	// -- Apartado 10 ---
	//Molino* molino = new Molino(mSM->getRootSceneNode(), 6);
	//addInputListener(molino);

	// -- Apartado 13 ---
	//RotorDron* rotorDron = new RotorDron(mSM->getRootSceneNode(), 6);
	//addInputListener(rotorDron);

	// -- Apartado 15 ---
	//BrazoDron* brazoDron = new BrazoDron(mSM->getRootSceneN-+-ode(), 6);
	//addInputListener(brazoDron);

	// -- Apartado 16 ---
	//Dron* dron = new Dron(mSM->getRootSceneNode(), 12, 8);
	//addInputListener(dron);

	// -- Apartado 17 ---
	//planetaNode = mSM->getRootSceneNode()->createChildSceneNode("nPlaneta");
	//planetaNode->attachObject(mSM->createEntity("sphere.mesh"));
	//planetaNode->setScale(5, 5, 5);
	//
	//ficticioDronNode = mSM->getRootSceneNode()->createChildSceneNode("nFicticioDron");
	//dron = new Dron(ficticioDronNode, 12, 8);
	//dron->getNode()->setScale(0.2, 0.2, 0.2);
	//dron->getNode()->translate(0, 540, 0);
	//
	//addInputListener(dron);

	//Apartado 21
	Avion* avion = new Avion(mSM->getRootSceneNode());
	addInputListener(avion);

	// -- Apartado 23 ---
	//MeshManager::getSingleton().createPlane("mPlane1080x800",
	//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//	Plane(Vector3::UNIT_Y, 0),
	//	1080, 800, 27, 20, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	//planeNode = mSM->getRootSceneNode()->createChildSceneNode("nPlano");
	//planeNode->attachObject(mSM->createEntity("mPlane1080x800"));
}

