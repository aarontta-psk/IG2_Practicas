#pragma once

#include "IG2App.h"

using namespace Ogre;

class Aspa : public OgreBites::InputListener
{
public:
	Aspa(SceneNode* node, SceneManager* mSM);
	void SetAdornoVisible(bool visibility);
	~Aspa();
	SceneNode* getNode() { return mNode; } //Para poder trasladar desde fuera, pero sin cambiar el nodo en sí

private:
	SceneNode* mNode;
	SceneNode* tableroNode;
	SceneNode* adornoNode;
};

Aspa::Aspa(SceneNode* node, SceneManager* mSM)
{
	//Creacion
	mNode = node->createChildSceneNode();
	tableroNode = mNode->createChildSceneNode();
	adornoNode = mNode->createChildSceneNode();

	tableroNode->attachObject(mSM->createEntity("cube.mesh"));
	adornoNode->attachObject(mSM->createEntity("Barrel.mesh"));

	//Posicion y escala
	tableroNode->setScale(3, 0.5, 0.05);  //Numeros cableados, no queda otra :(
	adornoNode->setScale(3, 6, 3);     //El barril es enano por alguna razon
	adornoNode->setPosition(130, 0, 12); //Desplazar derecha y traer al frente

	adornoNode->setInheritOrientation(false);
}

inline void Aspa::SetAdornoVisible(bool isVisible)
{
	adornoNode->setVisible(isVisible);
}

Aspa::~Aspa() //No se si hay que hacer algo aqui
{
	/*delete mNode;
	delete tableroNode;
	delete adornoNode;*/
}