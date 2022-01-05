#include "IG2App.h"

#include "./entities/EntityIG.h"

#include "./entities/p02_sinbad/Bomba.h"
#include "./entities/p02_sinbad/Plano.h"
#include "./entities/p02_sinbad/Avion.h"
#include "./entities/p02_sinbad/Sinbad.h"
#include "./entities/p02_sinbad/EsferaCursed.h"

// Rotaciones:
//		X -> pitch();
//		Y -> yaw();
//		Z -> roll();

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}

	return true;
}

void IG2App::shutdown()
{
	for (size_t i = 0; i < vEntities.size(); i++)
		delete vEntities[i];
	vEntities.clear();

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
	cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT); // CS_FREELOOK control tanque

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	//vp->setDimensions(0, 0, 0.5, 1);
	vp->setBackgroundColour(Ogre::ColourValue(0., 0., 0.));
	
	//vp = getRenderWindow()->addViewport(cam, 1);
	//vp->setDimensions(0.5, 0, 0.5, 1);
	//vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5));

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
	escenaTexturas();
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
	Camera* camReflex = mSM->createCamera("CamReflex");    // Añadimos una nueva camara para el reflejo 
	camReflex->setNearClipDistance(1);						 // Configurar frustum igual que camara de la escena
	camReflex->setFarClipDistance(10000);						       
	camReflex->setAutoAspectRatio(true);
	mCamNode->attachObject(camReflex);

	Camera* camMirror = mSM->createCamera("CamMirror");    // Añadimos una nueva camara para el reflejo 
	camMirror->setNearClipDistance(1);						 // Configurar frustum igual que camara de la escena
	camMirror->setFarClipDistance(10000);
	camMirror->setAutoAspectRatio(true);
	mCamNode->attachObject(camMirror);

	plano->setReflejo(camReflex, cam->getViewport()->getActualWidth(), cam->getViewport()->getActualHeight());
	espejo->setEspejo(camMirror, cam->getViewport()->getActualWidth(), cam->getViewport()->getActualHeight());
	/// Fin reflejo

	float sizeX = 540, sizeY = 540;
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

	ficticioAvionNode = mSM->getRootSceneNode()->createChildSceneNode("nFicticioAvion");
	vEntities.push_back(new Avion(ficticioAvionNode));
	vEntities[vEntities.size() - 1]->getNode()->setScale(0.25, 0.25, 0.25);
	vEntities[vEntities.size() - 1]->getNode()->translate(-350, 330, 0);
	addInputListener(vEntities[vEntities.size() - 1]);
	
	EsferaCursed* esferaCursed = new EsferaCursed(mSM->getRootSceneNode(), Vector3(0.25), Vector3(800, 20, -800));
	EntityIG::addListener(esferaCursed);
	
	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -100),
		"Practica2/SpaceZoomGLSL", 1, 1, true, 0.5, 100, 100);
}