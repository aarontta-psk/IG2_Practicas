#include "RotorDron.h"

RotorDron::RotorDron(SceneNode* node, int nAspas, double rotation) :EntidadIG(node)
{
	//Creacion
	mEsferaNode = mNode->createChildSceneNode();
	mHelicesNode = mNode->createChildSceneNode();

	mEsferaNode->attachObject(mSM->createEntity("sphere.mesh"));
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