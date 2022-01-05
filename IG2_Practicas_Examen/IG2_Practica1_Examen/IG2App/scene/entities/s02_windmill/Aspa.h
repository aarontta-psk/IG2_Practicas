#ifndef ASPA_H_
#define ASPA_H_

#include "../EntityIG.h"

using namespace Ogre;

class Aspa : public EntityIG
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