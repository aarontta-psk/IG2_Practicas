#include "RotorDron.h"

RotorDron::RotorDron(SceneNode* node, int nAspas, double rotation) :EntityIG(node)
{
	//Creacion
	mEsferaNode = mNode->createChildSceneNode();
	mHelicesNode = mNode->createChildSceneNode();

	Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Orange");
	mEsferaNode->attachObject(sphere);
	mAspas = new AspasMolino(mHelicesNode, nAspas, rotation);
	mAspas->setAdornosVisibility(false);

	//Escalas
	float sphereScale = 2;
	float helicesScale = 0.75f;
	mEsferaNode->setScale(sphereScale, sphereScale, sphereScale);
	mHelicesNode->setScale(helicesScale, helicesScale, helicesScale);

	//Posiciones
	mAspas->getNode()->setPosition(0, 260, 0);
	mAspas->getNode()->pitch(Degree(90));

	numAspas = nAspas;
}

RotorDron::~RotorDron()
{
	delete mAspas;
}

bool RotorDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mAspas->keyPressed(evt); // --- Apartado 14 ---
	return true;
}

void RotorDron::frameRendered(const Ogre::FrameEvent& evt)
{
	mAspas->frameRendered(evt);
}
