#include "Aspa.h"

Aspa::Aspa(SceneNode* node) : EntidadIG(node)
{
	//Creacion
	tableroNode = mNode->createChildSceneNode();
	adornoNode = mNode->createChildSceneNode();

	Entity* cube = mSM->createEntity("cube.mesh");
	cube->setMaterialName("Practica1/Aspa");
	tableroNode->attachObject(cube);

	Entity* adorno = mSM->createEntity("Barrel.mesh");
	adorno->setMaterialName("Practica1/Red");
	adornoNode->attachObject(adorno);

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