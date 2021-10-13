#ifndef AVION_H_
#define AVION_H_

class AspasMolino;

#include "EntidadIG.h"
class Avion : public EntidadIG
{
public:
	Avion(SceneNode* node);
	virtual inline bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

private:
	SceneNode* mCuerpoNode;
	SceneNode* mAlaINode;
	SceneNode* mAlaDNode;
	AspasMolino* mHeliceINode;
	AspasMolino* mHeliceDNode;
	SceneNode* mFrenteNode;
	SceneNode* mPilotoNode;

	SceneNode* lightNode;
	Light* light;
};
#endif