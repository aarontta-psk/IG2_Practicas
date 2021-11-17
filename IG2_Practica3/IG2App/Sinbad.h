#ifndef SINBAD_H_
#define SINBAD_H_

#include "EntityIG.h"
#include "OgreTimer.h"

#include <vector>

using namespace Ogre;

class Sinbad : public EntityIG
{
	// Dance, DrawSwords, HandsClosed, HandsRelaxed, IdleBase, IdleTop, JumpEnd, JumpLoop, 
	// JumpStart, RunBase, RunTop, SliceHorizontal, SliceVertical
	enum class AnimState { IDLE, RUN, JUMP, DANCE, HANDS_CLOSED, HANDS_RELAXED, DRAW_SWORDS, SLICE_H, SLICE_V };

	enum class MovState { MOVING, ROTATING_LEFT, ROTATING_RIGHT };

	enum class SwordStance { NONE, L_SWORD, R_SWORD, DUAL_SWORD };

public:
	Sinbad(SceneNode* node);
	virtual ~Sinbad() {};

	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual void receiveEvent(Message message, EntityIG* entidad);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void cambiaEspada();
	void arma(bool swHand);
	void arma();
	void unarm();
private:
	Entity* sinbad;
	Entity* leftSword;
	Entity* rightSword;
	bool isDed;
	float aux;

	std::vector<Ogre::String> currentAnims;
	
	SwordStance currentWeapon; 
	AnimationState* walkAnim;

	MovState state;
	Ogre::Timer* myTimer;

	void changeAnim(const std::vector<Ogre::String> newAnims);
	void initAnim(const Ogre::String& animation);
	void resetAnim(const Ogre::String& animation);
	std::vector<Ogre::String> newAnimsList(const AnimState newAnim);
	void addTimeAnim(const Ogre::String& animation, Ogre::Real offset);

	void swordVisibility();

	void sinbadMovement();
};
#endif
