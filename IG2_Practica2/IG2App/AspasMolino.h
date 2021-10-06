#ifndef ASPASMOLINO_H_
#define ASPASMOLINO_H_

#include "EntidadIG.h"
#include "Aspa.h"

using namespace Ogre;

class AspasMolino : public EntidadIG
{
public:
	AspasMolino(SceneNode* node, int numAspas, double rotation = 2);
	~AspasMolino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void setAdornosVisibility(bool isVisible);

private:
	SceneNode* cilindroCentralNode;
	SceneNode* aspasNode;

	Aspa** arrayAspas;

	int numAspas;
	double rot; // WIP
};
#endif