#include "Sinbad.h"

Sinbad::Sinbad(SceneNode* node) : EntityIG(node), currentWeapon(SwordStance::NONE), state(MovState::MOVING)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(sinbad);

	initAnim("RunBase");
	initAnim("RunTop");

	leftSword = mSM->createEntity("Sword.mesh");
	sinbad->attachObjectToBone("Handle.L", leftSword);

	rightSword = mSM->createEntity("Sword.mesh");
	sinbad->attachObjectToBone("Handle.R", rightSword);

	swordVisibility();

	myTimer = new Timer();

	/*AnimationStateSet* aux = sinbad->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end())
	{
		auto s = it->first; ++it;
		std::cout << "\n" << s << "\n";
	}*/

	float dur = 10;
	Animation* anim = mSM->createAnimation("AnimWalkSinbad", dur);

	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	Vector3 src(0, 0, 1);
	float despl = 1600;
	Real durPaso = dur / 11.0;

	TransformKeyFrame* kf;
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 1: Mira el frente
	kf->setRotation(Quaternion::IDENTITY);

	kf = track->createNodeKeyFrame(durPaso * 0.75); // Keyframe 2: rota en origin
	kf->setRotation(src.getRotationTo(Vector3(1, 0, -1)));

	kf = track->createNodeKeyFrame(durPaso * 4.75); // Keyframe 3: llega a la otra plataforma
	kf->setTranslate({despl, 0, -despl});
	kf->setRotation(src.getRotationTo(Vector3(1, 0, -1)));

	kf = track->createNodeKeyFrame(durPaso * 5.75); // Keyframe 4: roto en la otra plataforma
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));
	kf->setTranslate({ despl, 0, -despl });

	kf = track->createNodeKeyFrame(durPaso * 9.75); // Keyframe 5: rota en origin
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));

	kf = track->createNodeKeyFrame(durPaso * 10); // Keyframe 6: Mira el frente
	kf->setRotation(Quaternion::IDENTITY);

	walkAnim = mSM->createAnimationState("AnimWalkSinbad");

	walkAnim->setLoop(true);
	walkAnim->setEnabled(true);
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	walkAnim->addTime(evt.timeSinceLastFrame);

	for (auto anim : currentAnims)
		addTimeAnim(anim, evt.timeSinceLastFrame);

	if (isDed && myTimer->getMilliseconds() >= 5000)
	{
		sendEvent({ BOMB }, this);
		isDed = false;
	}
	//sinbadMovement();
}

void Sinbad::receiveEvent(Message message, EntityIG* entidad)
{
	if (message.id_ == SIMBAD_DIES_YAY)
	{
		walkAnim->setEnabled(false);
		myTimer->reset();
		changeAnim(newAnimsList(AnimState::IDLE));
		mNode->pitch(Degree(-90));
		mNode->translate(0, -75, 0);
		isDed = true;
	}
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_s)
		cambiaEspada();
	else if (evt.keysym.sym == SDLK_e)
		arma();
	else if (evt.keysym.sym == SDLK_u)
		unarm();
	else if (evt.keysym.sym == SDLK_c)
		changeAnim((currentAnims.size() <= 1) ? newAnimsList(AnimState::RUN) : newAnimsList(AnimState::DANCE));
	/*else if (evt.keysym.sym == SDLK_r)
		changeAnim(newAnimsList((AnimState)(std::rand() % 9)));*/

	return true;
}

void Sinbad::changeAnim(const std::vector<Ogre::String> newAnims)
{
	for (auto anim : currentAnims)
		resetAnim(anim);
	currentAnims.clear();

	for (auto newAnim : newAnims)
		initAnim(newAnim);
}

void Sinbad::initAnim(const Ogre::String& animation)
{
	auto anim = sinbad->getAnimationState(animation);

	anim->setEnabled(true);
	anim->setLoop(true);

	currentAnims.push_back(animation);
}

void Sinbad::resetAnim(const Ogre::String& animation)
{
	auto anim = sinbad->getAnimationState(animation);

	anim->setEnabled(false);
	anim->setLoop(false);
	anim->setTimePosition(0);
}

std::vector<Ogre::String> Sinbad::newAnimsList(const AnimState newAnim)
{
	switch (newAnim)
	{
	case AnimState::IDLE:
		return { "IdleBase", "IdleTop" };
		break;
	case AnimState::RUN:
		return { "RunBase", "RunTop" };
		break;
	case AnimState::JUMP:
		return { "JumpLoop" };
		break;
	case AnimState::DANCE:
		return { "Dance" };
		break;
	case AnimState::HANDS_CLOSED:
		return { "HandsClosed" };
		break;
	case AnimState::HANDS_RELAXED:
		return { "HandsRelaxed" };
		break;
	case AnimState::DRAW_SWORDS:
		return { "DrawSwords" };
		break;
	case AnimState::SLICE_H:
		return { "SliceHorizontal" };
		break;
	case AnimState::SLICE_V:
		return { "SliceVertical" };
		break;
	default:
		return { };
		break;
	}
}

void Sinbad::addTimeAnim(const Ogre::String& animation, Ogre::Real offset)
{
	sinbad->getAnimationState(animation)->addTime(offset);
}

void Sinbad::cambiaEspada()
{
	switch (currentWeapon)
	{
	case SwordStance::NONE:
	case SwordStance::DUAL_SWORD:
		arma(std::rand() % 2);
		break;
	case SwordStance::L_SWORD:
		arma(true);
		break;
	case SwordStance::R_SWORD:
		arma(false);
		break;
	default:
		break;
	}
}

void Sinbad::arma(bool swHand)
{
	currentWeapon = (SwordStance)(swHand + 1);
	swordVisibility();
}

void Sinbad::arma()
{
	currentWeapon = SwordStance::DUAL_SWORD;
	swordVisibility();
}

void Sinbad::unarm()
{
	currentWeapon = SwordStance::NONE;
	swordVisibility();
}

void Sinbad::swordVisibility()
{
	switch (currentWeapon)
	{
	case SwordStance::NONE:
		leftSword->setVisible(false);
		rightSword->setVisible(false);
		break;
	case SwordStance::L_SWORD:
		leftSword->setVisible(true);
		rightSword->setVisible(false);
		break;
	case SwordStance::R_SWORD:
		leftSword->setVisible(false);
		rightSword->setVisible(true);
		break;
	case SwordStance::DUAL_SWORD:
		leftSword->setVisible(true);
		rightSword->setVisible(true);
		break;
	default:
		break;
	}
}

void Sinbad::sinbadMovement()
{
	SceneNode* parentNode = mNode->getParentSceneNode();

	switch (state) {
	case MovState::MOVING: {
		if (myTimer->getMilliseconds() >= 2000) {
			state = (MovState)(rand() % 2 + 1);
			myTimer->reset();
		}
		break;
	}
	case MovState::ROTATING_LEFT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = MovState::MOVING;
			myTimer->reset();
		}
		else
			parentNode->yaw(Ogre::Degree(1));
		break;
	}
	case MovState::ROTATING_RIGHT: {
		if (myTimer->getMilliseconds() >= 1500) {
			state = MovState::MOVING;
			myTimer->reset();
		}
		else
			parentNode->yaw(Ogre::Degree(-1));
		break;
	}
	}
	parentNode->pitch(Ogre::Degree(1));
}