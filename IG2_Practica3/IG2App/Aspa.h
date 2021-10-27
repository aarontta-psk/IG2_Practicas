#ifndef ASPA_H_
#define ASPA_H_

#include "EntidadIG.h"

using namespace Ogre;

class Aspa : public EntidadIG
{
public:
	Aspa(SceneNode* node);
	~Aspa() {};

	void setAdornoVisible(bool visibility);

private:
	SceneNode* tableroNode;
	SceneNode* adornoNode;
};
#endif