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
#include "Plano.h"
#include "Sinbad.h"
#include "Bomba.h"

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
		vEntities[0]->getNode()->translate(0, -315, 0, SceneNode::TS_LOCAL);
		vEntities[0]->getNode()->roll(Ogre::Degree(-3), SceneNode::TS_LOCAL);
		vEntities[0]->getNode()->translate(0, 315, 0, SceneNode::TS_LOCAL);
	}
	else if (evt.keysym.sym == SDLK_j) {
		// -- Apartado 19 ---
		//ficticioDronNode->yaw(Ogre::Degree(-3));

		// -- Apartado 20 ---
		vEntities[0]->getNode()->yaw(Ogre::Degree(-3), SceneNode::TS_LOCAL);
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

	/*for (size_t i = 0; i < vEntities.size(); i++)
		delete vEntities[i];
	vEntities.clear();*/

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
	cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0., 0., 0.));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1, 1, 1);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// finally something to render

	//Create nodes
	//EscenaReloj();
	//EscenaMolino();
	//EscenaDrones();
	//EscenaSimbad(); 
	escenaTexturas();
}


void IG2App::escenaReloj()
{
	// COMENTARIO SOBRE FORMAS DE CREAR LAS ESFERAS
	//Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
	//Ogre::Entity* ent = mSM->createEntity("Sphere", Ogre::SceneManager::PT_SPHERE);
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
	//mClockNode->setVisible(false);
}

void IG2App::escenaMolino()
{
	// --- Apartado 7 ---
	//Aspa aspa = Aspa(mSM->getRootSceneNode());

	// --- Apartado 8 ---
	//AspasMolino* aspaMolino = new AspasMolino(mSM->getRootSceneNode(), 12);
	//addInputListener(aspaMolino);

	// -- Apartado 10 ---
	Molino* molino = new Molino(mSM->getRootSceneNode(), 6);
	addInputListener(molino);
}

void IG2App::escenaDrones()
{
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
	//Avion* avion = new Avion(mSM->getRootSceneNode());
	//addInputListener(avion);

	// -- Apartado 23 ---
	//MeshManager::getSingleton().createPlane("mPlane1080x800",
	//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//	Plane(Vector3::UNIT_Y, 0),
	//	1080, 800, 27, 20, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	//planeNode = mSM->getRootSceneNode()->createChildSceneNode("nPlano");
	//planeNode->attachObject(mSM->createEntity("mPlane1080x800"));

	//// -- Apartado 26 --
	planetaNode = mSM->getRootSceneNode()->createChildSceneNode("nPlaneta");
	Entity* planet = mSM->createEntity("sphere.mesh");
	planet->setMaterialName("Practica1/Cyan");
	planetaNode->attachObject(planet);
	planetaNode->setScale(3, 3, 3);

	createDrones();

	vEntities.push_back(new Dron(mSM->getRootSceneNode(), 3, 3, true));
	static_cast<Dron*>(vEntities[vEntities.size() - 1])->disableLight();
	vEntities[vEntities.size() - 1]->getNode()->yaw(Ogre::Degree(30));
	vEntities[vEntities.size() - 1]->getNode()->translate(0, 315, 0, SceneNode::TS_LOCAL);
	vEntities[vEntities.size() - 1]->getNode()->setScale(0.1, 0.1, 0.1);
	addInputListener(vEntities[vEntities.size() - 1]);
	EntityIG::addListener(vEntities[vEntities.size() - 1]);

	ficticioAvionNode = mSM->getRootSceneNode()->createChildSceneNode("nFicticioAvion");
	vEntities.push_back(new Avion(ficticioAvionNode));
	vEntities[vEntities.size() - 1]->getNode()->setScale(0.15, 0.15, 0.15);
	vEntities[vEntities.size() - 1]->getNode()->translate(0, 330, 0);
	addInputListener(vEntities[vEntities.size() - 1]);
	EntityIG::addListener(vEntities[vEntities.size() - 1]);

	vEntities.push_back(new Plano(mSM->getRootSceneNode(), "mPlane1080x800",
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 27, 20, true, 1, 1.0, 1.0, Vector3::UNIT_Z));
	vEntities[vEntities.size() - 1]->getNode()->pitch(Ogre::Degree(90));
	vEntities[vEntities.size() - 1]->getNode()->translate(0, 0, -1000);
	vEntities[vEntities.size() - 1]->getNode()->setScale(2, 2, 2);
}

void IG2App::escenaSimbad()
{
	// --- Apartado 41 --

	//auto ficticioSimbadNode = mSM->getRootSceneNode()->createChildSceneNode("nFicticioSimbad");
	//vEntities.push_back(new Sinbad(ficticioSimbadNode));
	//addInputListener(vEntities[vEntities.size() - 1]);
	//vEntities[vEntities.size() - 1]->getNode()->translate(0, 348, 0);
	//vEntities[vEntities.size() - 1]->getNode()->setScale(10, 10, 10);

	auto bomba = new Bomba(mSM->getRootSceneNode(), 8, 30);
	vEntities.push_back(bomba);
	bomba->getNode()->setScale(20, 20, 20);
	bomba->getNode()->setInitialState();
	EntityIG::addListener(bomba);
	addInputListener(bomba);

	auto plano = new Plano(mSM->getRootSceneNode(), "mPlaneWater",
		Plane(Vector3::UNIT_Y, 0),
		1080, 1080, 30, 30, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	vEntities.push_back(plano);
	plano->setMaterialName("Practica1/Water");
	vEntities[vEntities.size() - 1]->getNode()->setScale(2, 2, 2);
	addInputListener(vEntities[vEntities.size() - 1]);
	EntityIG::addListener(plano);

	float sizeX = 540;
	float sizeY = 540;

	plano = new Plano(mSM->getRootSceneNode(), "mPlaneYellow",
		Plane(Vector3::UNIT_Y, 0),
		sizeX, sizeY, 2, 2, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	vEntities.push_back(plano);
	plano->setMaterialName("Practica1/Yellow");
	vEntities[vEntities.size() - 1]->getNode()->translate(-sizeX * 1.5f, 1.2, sizeY * 1.5f);

	plano = new Plano(mSM->getRootSceneNode(), "mPlaneRed",
		Plane(Vector3::UNIT_Y, 0),
		sizeX, sizeY, 2, 2, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	vEntities.push_back(plano);
	plano->setMaterialName("Practica1/Red");
	vEntities[vEntities.size() - 1]->getNode()->translate(sizeX * 1.5f, 1.2, -sizeY * 1.5f);

	auto simbad = new Sinbad(mSM->getRootSceneNode());
	vEntities.push_back(simbad);
	addInputListener(vEntities[vEntities.size() - 1]);
	EntityIG::addListener(simbad);
	simbad->getNode()->translate(-sizeX * 1.5f, 100, sizeY * 1.5f);
	simbad->getNode()->setScale(20, 20, 20);
	simbad->getNode()->setInitialState();
	simbad->arma();

	//Apartado 52
	Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Cursed");
	SceneNode* sphereNode = mSM->getRootSceneNode()->createChildSceneNode();
	sphereNode->attachObject(sphere);
	float sphereScale = 0.25;
	sphereNode->setScale(sphereScale, sphereScale, sphereScale);
	float pos = 800;
	sphereNode->setPosition({ pos, 20, -pos });

	ficticioAvionNode = mSM->getRootSceneNode()->createChildSceneNode("nFicticioAvion");
	vEntities.push_back(new Avion(ficticioAvionNode));
	vEntities[vEntities.size() - 1]->getNode()->setScale(0.25, 0.25, 0.25);
	vEntities[vEntities.size() - 1]->getNode()->translate(-350, 330, 0);
	addInputListener(vEntities[vEntities.size() - 1]);

	//APARTADO 55
	createSmokeScreen();
}

void IG2App::escenaTexturas()
{
	auto bomba = new Bomba(mSM->getRootSceneNode(), 8, 30);
	vEntities.push_back(bomba);
	bomba->getNode()->setInitialState();
	EntityIG::addListener(bomba);
	addInputListener(bomba);

	auto plano = new Plano(mSM->getRootSceneNode(), "mPlaneWater",
		Plane(Vector3::UNIT_Y, 0),
		1080, 1080, 30, 30, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	vEntities.push_back(plano);
	plano->setMaterialName("Practica1/Water");
	vEntities[vEntities.size() - 1]->getNode()->setScale(2, 2, 2);
	addInputListener(vEntities[vEntities.size() - 1]);
	EntityIG::addListener(plano);

	auto espejo = new Plano(mSM->getRootSceneNode(), "mirror",
		Plane(Vector3::UNIT_Y, 0),
		1080, 1080, 30, 30, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	vEntities.push_back(espejo);
	espejo->setMaterialName("Practica1/White");
	vEntities[vEntities.size() - 1]->getNode()->setScale(2, 2, 2);
	vEntities[vEntities.size() - 1]->getNode()->roll(Degree(90));
	vEntities[vEntities.size() - 1]->getNode()->translate(1080, 590, 0);
	addInputListener(vEntities[vEntities.size() - 1]);
	EntityIG::addListener(espejo);

	//Reflejo
										 // spherojo nombre único
	Camera* camReflex = mSM->createCamera("CamReflex");    // Añadimos una nueva camara para el reflejo 
	camReflex->setNearClipDistance(1);						 // Configurar frustum igual que camara de la escena
	camReflex->setFarClipDistance(10000);						       
	camReflex->setAutoAspectRatio(true);
	mCamNode->attachObject(camReflex);

	// spherojo nombre único
	Camera* camMirror = mSM->createCamera("CamMirror");    // Añadimos una nueva camara para el reflejo 
	camMirror->setNearClipDistance(1);						 // Configurar frustum igual que camara de la escena
	camMirror->setFarClipDistance(10000);
	camMirror->setAutoAspectRatio(true);
	mCamNode->attachObject(camMirror);

	plano->setReflejo(camReflex, cam->getViewport()->getActualWidth(), cam->getViewport()->getActualHeight());
	espejo->setEspejo(camMirror, cam->getViewport()->getActualWidth(), cam->getViewport()->getActualHeight());

	/// Fin reflejo

	float sizeX = 540;
	float sizeY = 540;

	plano = new Plano(mSM->getRootSceneNode(), "mPlaneYellow",
		Plane(Vector3::UNIT_Y, 0),
		sizeX, sizeY, 2, 2, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	vEntities.push_back(plano);
	plano->setMaterialName("Practica1/Yellow");
	vEntities[vEntities.size() - 1]->getNode()->translate(-sizeX * 1.5f, 1.2, sizeY * 1.5f);

	auto simbad = new Sinbad(mSM->getRootSceneNode());
	vEntities.push_back(simbad);
	addInputListener(vEntities[vEntities.size() - 1]);
	EntityIG::addListener(simbad);
	simbad->getNode()->translate(-sizeX * 1.5f, 100, sizeY * 1.5f);
	simbad->getNode()->setScale(20, 20, 20);
	simbad->getNode()->setInitialState();
	simbad->arma();

	//Apartado 52
	Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Cursed");
	SceneNode* sphereNode = mSM->getRootSceneNode()->createChildSceneNode();
	sphereNode->attachObject(sphere);
	float sphereScale = 0.25;
	sphereNode->setScale(sphereScale, sphereScale, sphereScale);
	float pos = 800;
	sphereNode->setPosition({ pos, 20, -pos });

	ficticioAvionNode = mSM->getRootSceneNode()->createChildSceneNode("nFicticioAvion");
	vEntities.push_back(new Avion(ficticioAvionNode, false));
	vEntities[vEntities.size() - 1]->getNode()->setScale(0.25, 0.25, 0.25);
	vEntities[vEntities.size() - 1]->getNode()->translate(-350, 330, 0);
	addInputListener(vEntities[vEntities.size() - 1]);

	// Apartado 2
	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -100),
		"Practica2/SpaceZoomGLSL", 1, 1, true, 0.0, 100, 100);

	// Apartado 4
}

void IG2App::createSmokeScreen() {
	BillboardSet* bbSet = mSM->createBillboardSet("Smokescreen", 9);
	bbSet->setDefaultDimensions(1500, 1500);
	bbSet->setMaterialName("Practica1/Smoke");
	mSM->getRootSceneNode()->attachObject(bbSet);

	bbSet->createBillboard(Vector3(300, 500, -500));
	bbSet->createBillboard(Vector3(700, 500, -500));
	bbSet->createBillboard(Vector3(1100, 500, -500));

	bbSet->createBillboard(Vector3(300, 500, -100));
	bbSet->createBillboard(Vector3(700, 500, -100));
	bbSet->createBillboard(Vector3(1100, 500, -100));

	bbSet->createBillboard(Vector3(300, 500, 400));
	bbSet->createBillboard(Vector3(700, 500, 400));
	bbSet->createBillboard(Vector3(1100, 500, 400));

}

void IG2App::createDrones()
{
	for (int i = 0; i < 20; i++) {
		vEntities.push_back(new Dron(mSM->getRootSceneNode(), 3, 3));
		static_cast<Dron*>(vEntities[vEntities.size() - 1])->disableLight();
		vEntities[vEntities.size() - 1]->getNode()->roll(Ogre::Degree(i * 100));
		vEntities[vEntities.size() - 1]->getNode()->pitch(Ogre::Degree(100));
		vEntities[vEntities.size() - 1]->getNode()->translate(0, 315, 0, SceneNode::TS_LOCAL);
		vEntities[vEntities.size() - 1]->getNode()->setScale(0.04, 0.04, 0.04);
		addInputListener(vEntities[vEntities.size() - 1]);
		EntityIG::addListener(vEntities[vEntities.size() - 1]);
	}

	for (int i = 0; i < 20; i++) {
		vEntities.push_back(new Dron(mSM->getRootSceneNode(), 3, 3));
		static_cast<Dron*>(vEntities[vEntities.size() - 1])->disableLight();
		vEntities[vEntities.size() - 1]->getNode()->yaw(Ogre::Degree(i * 100));
		vEntities[vEntities.size() - 1]->getNode()->pitch(Ogre::Degree(100));
		vEntities[vEntities.size() - 1]->getNode()->translate(0, 315, 0, SceneNode::TS_LOCAL);
		vEntities[vEntities.size() - 1]->getNode()->setScale(0.04, 0.04, 0.04);
		addInputListener(vEntities[vEntities.size() - 1]);
		EntityIG::addListener(vEntities[vEntities.size() - 1]);
	}
}