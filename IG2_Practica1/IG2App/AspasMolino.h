#pragma once

#include "IG2App.h"
#include "Aspa.h"
//#include <SDL_keycode.h>
//#include <OgreInput.h>

using namespace Ogre;

class AspasMolino : public OgreBites::InputListener
{
public:
	AspasMolino(SceneNode* node, SceneManager* mSM, int numAspas, double rotation = 2);
	~AspasMolino();
	void SetAdornosVisibility(bool isVisible);
	SceneNode* getNode() { return mNode; } //Para poder trasladar desde fuera, pero sin cambiar el nodo en s�

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	SceneNode* mNode;
	SceneNode* cilindroCentralNode;
	SceneNode* aspasNode;
	Aspa** arrayAspas;
	int numAspas;
	double rot;
};

AspasMolino::AspasMolino(SceneNode* node, SceneManager* mSM, int numAspas, double rotation)
{
	//Creacion
	mNode = node->createChildSceneNode();
	cilindroCentralNode = mNode->createChildSceneNode();
	aspasNode = mNode->createChildSceneNode();

	cilindroCentralNode->attachObject(mSM->createEntity("Barrel.mesh"));
	cilindroCentralNode->pitch(Degree(90));
	int scale = 20; //Mas facil de cambiar asi
	cilindroCentralNode->setScale(scale, scale * 0.2f, scale);

	//Aspas
	arrayAspas = new Aspa * [numAspas];
	double angleStep = 360.0 / numAspas;
	for (int i = 0; i < numAspas; i++)
	{
		arrayAspas[i] = new Aspa(aspasNode, mSM);
		arrayAspas[i]->getNode()->roll(Degree(i * angleStep));
		arrayAspas[i]->getNode()->translate(200, 0, 0, SceneNode::TS_LOCAL); //El (gran) truco
	}

	this->numAspas = numAspas;
	rot = rotation;
}

AspasMolino::~AspasMolino() //No se si hay que hacer algo aqui
{
	delete[] arrayAspas;
}

inline void AspasMolino::SetAdornosVisibility(bool isVisible)
{
	for (int i = 0; i < numAspas; i++)
		arrayAspas[i]->SetAdornoVisible(isVisible);
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g)
	{
		aspasNode->roll(Degree(rot));
	}
	else if (evt.keysym.sym == SDLK_c)
	{
		cilindroCentralNode->translate(0, -1, 0, SceneNode::TS_LOCAL); // --- Apartado 11 ---
	}
	return true;
}
