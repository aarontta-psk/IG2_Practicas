#pragma once

#include "IG2App.h"
#include "Aspa.h"

using namespace Ogre;

class AspasMolino : public OgreBites::InputListener
{
public:
	AspasMolino(SceneManager* mSM, int numAspas);
	~AspasMolino();
	const SceneNode* getNode() { return mNode; } //Para poder trasladar desde fuera, pero sin cambiar el nodo en sí

private:
	SceneNode* mNode;
	SceneNode* cilindroCentralNode;
	SceneNode* aspasNode;
	Aspa** arrayAspas;
	SceneManager* mSM;
};

AspasMolino::AspasMolino(SceneManager* mSM, int numAspas)
{
	this->mSM = mSM;
	
	//Creacion
	mNode = mSM->getRootSceneNode()->createChildSceneNode();
	cilindroCentralNode = mNode->createChildSceneNode();
	aspasNode = mNode->createChildSceneNode();

	cilindroCentralNode->attachObject(mSM->createEntity("Barrel.mesh"));
	cilindroCentralNode->pitch(Degree(90));
	int scale = 20; //Mas facil de cambiar asi
	cilindroCentralNode->setScale(scale, scale * 0.2f, scale);

	//Aspas
	arrayAspas = new Aspa*[numAspas];
	double angleStep = 360.0 / numAspas;
	for (int i = 0; i < numAspas; i++)
	{
		arrayAspas[i] = new Aspa(mSM);
		arrayAspas[i]->getNode()->roll(Degree(i*angleStep));
		arrayAspas[i]->getNode()->translate(200, 0, 0, SceneNode::TS_LOCAL);
	}
}

AspasMolino::~AspasMolino() //No se si hay que hacer algo aqui
{
	/*delete mNode;
	delete tableroNode;
	delete adornoNode;*/
}