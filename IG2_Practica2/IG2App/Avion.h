#ifndef AVION_H_
#define AVION_H_

class AspasMolino;

#include "EntidadIG.h"
class Avion : public EntidadIG
{
public:
	Avion(SceneNode* node);
private:
	SceneNode* mCuerpoNode;
	SceneNode* mAlaINode;
	SceneNode* mAlaDNode;
	AspasMolino* mHeliceINode;
	AspasMolino* mHeliceDNode;
	SceneNode* mFrenteNode;
	SceneNode* mPilotoNode;
};

#endif
