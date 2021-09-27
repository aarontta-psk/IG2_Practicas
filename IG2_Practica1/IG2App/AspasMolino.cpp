#include "AspasMolino.h"

AspasMolino::AspasMolino(SceneNode* node, int numAspas, double rotation) : EntityIG(node)
{
	//Creacion
	cilindroCentralNode = mNode->createChildSceneNode();
	aspasNode = mNode->createChildSceneNode();

	cilindroCentralNode->attachObject(mSM->createEntity("Barrel.mesh"));
	cilindroCentralNode->pitch(Degree(90));
	int scale = 20; //Mas comodo de cambiar asi
	cilindroCentralNode->setScale(scale, scale * 0.2f, scale);

	//Aspas
	arrayAspas = new Aspa * [numAspas];
	double angleStep = 360.0 / numAspas;
	for (int i = 0; i < numAspas; i++) {
		arrayAspas[i] = new Aspa(aspasNode);
		arrayAspas[i]->getNode()->roll(Degree(i * angleStep));
		arrayAspas[i]->getNode()->translate(200, 0, 0, SceneNode::TS_LOCAL); //El (gran) truco
	}

	this->numAspas = numAspas;
	rot = rotation;
}

AspasMolino::~AspasMolino()
{
	for (int i = 0; i < numAspas; ++i)
		delete arrayAspas[i];
	delete[] arrayAspas;
}

void AspasMolino::setAdornosVisibility(bool isVisible)
{
	for (int i = 0; i < numAspas; i++)
		arrayAspas[i]->setAdornoVisible(isVisible);
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g)
		aspasNode->roll(Degree(rot)); // -- Apartado 9 --
	else if (evt.keysym.sym == SDLK_c)
		cilindroCentralNode->translate(0, -1, 0, SceneNode::TS_LOCAL); // --- Apartado 11 ---

	return true;
}
