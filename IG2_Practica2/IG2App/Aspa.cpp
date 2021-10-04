#include "Aspa.h"

Aspa::Aspa(SceneNode* node) : EntityIG(node)
{
	//Creacion
	tableroNode = mNode->createChildSceneNode();
	adornoNode = mNode->createChildSceneNode();

	tableroNode->attachObject(mSM->createEntity("cube.mesh"));
	adornoNode->attachObject(mSM->createEntity("Barrel.mesh"));

	//Posicion y escala
	tableroNode->setScale(3, 0.5, 0.05); //Numeros cableados, no queda otra :(
	adornoNode->setScale(3, 6, 3);       //El barril es enano por alguna razon
	adornoNode->setPosition(130, 0, 12); //Desplazar derecha y traer al frente

	adornoNode->setInheritOrientation(false);
}

void Aspa::setAdornoVisible(bool isVisible)
{
	adornoNode->setVisible(isVisible);
}