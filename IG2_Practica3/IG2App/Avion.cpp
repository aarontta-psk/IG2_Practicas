#include "Avion.h"

#include "AspasMolino.h"

Avion::Avion(SceneNode* node) : EntityIG(node, ""), state(State::MOVING), detenido(false), manualControl(true)
{
	mCuerpoNode = mNode->createChildSceneNode();
	mAlaINode = mNode->createChildSceneNode();
	mAlaDNode = mNode->createChildSceneNode();
	mHeliceINode = new AspasMolino(mNode, 5);
	mHeliceDNode = new AspasMolino(mNode, 5);
	mFrenteNode = mNode->createChildSceneNode();
	mPilotoNode = mNode->createChildSceneNode();

	Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Red");
	mCuerpoNode->attachObject(sphere);
	mCuerpoNode->setScale(2, 2, 2);

	float helicesScale = 0.25f;
	mHeliceINode->getNode()->setScale(Vector3(helicesScale));
	mHeliceDNode->getNode()->setScale(Vector3(helicesScale));

	float helicesOffsetX = 350.0f;
	float helicesOffseZ = 80.0f;
	mHeliceINode->getNode()->translate(-helicesOffsetX, 0, helicesOffseZ);
	mHeliceDNode->getNode()->translate(helicesOffsetX, 0, helicesOffseZ);

	Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindro->setMaterialName("Practica1/Brown");
	mFrenteNode->attachObject(cilindro);
	mFrenteNode->translate(0, 0, 175);
	mFrenteNode->setScale(Vector3(20.f));
	mFrenteNode->pitch(Degree(90));

	Entity* ninja = mSM->createEntity("ninja.mesh");
	ninja->setMaterialName("Practica1/Yellow");
	mPilotoNode->attachObject(ninja);
	mPilotoNode->translate(0, 200, 0);
	mPilotoNode->yaw(Degree(180));

	float alasScaleX = 4.0f;
	float alasScaleY = 0.4f;
	float alasScaleZ = 1.5f;
	float alasOffset = 300.0f;
	Entity* ala = mSM->createEntity("cube.mesh");
	ala->setMaterialName("Practica1/Checker");
	mAlaINode->attachObject(ala);

	ala = mSM->createEntity("cube.mesh");
	ala->setMaterialName("Practica1/Checker");
	mAlaDNode->attachObject(ala);
	mAlaINode->setScale(alasScaleX, alasScaleY, alasScaleZ);
	mAlaDNode->setScale(alasScaleX, alasScaleY, alasScaleZ);
	mAlaINode->translate(-alasOffset, 0, 0);
	mAlaDNode->translate(alasOffset, 0, 0);
	light = mSM->createLight();

	lightNode = mSM->createSceneNode();
	mNode->addChild(lightNode);
	lightNode->attachObject(light);

	light->setType(Light::LT_SPOTLIGHT);
	light->setDirection(Vector3(0, -1, 0));
	light->setSpotlightInnerAngle(Degree(0));
	light->setSpotlightOuterAngle(Degree(45));
	light->setSpotlightFalloff(1.0f);

	BillboardSet* bbSet = mSM->createBillboardSet("10PointsBb", 1);
	bbSet->setDefaultDimensions(250, 125);
	bbSet->setMaterialName("Practica1/10Panel");
	mNode->attachObject(bbSet);

    bbSet->createBillboard(Vector3(0, 0, -330));

	myTimer = new Timer();
}

void Avion::receiveEvent(Message message, EntityIG* entidad)
{
	switch (message.id_)
	{
	case DEFAULT:
		break;
	case STOP_ALL_ENTITIES:
		detenido = true;
		static_cast<Entity*>(mAlaDNode->getAttachedObjects()[0])->setMaterialName("Practica1/Red");
		static_cast<Entity*>(mAlaINode->getAttachedObjects()[0])->setMaterialName("Practica1/Red");
		break;
	default:
		break;
	}
}

inline bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	mHeliceDNode->keyPressed(evt);
	mHeliceINode->keyPressed(evt);


	if (evt.keysym.sym == SDLK_r)
		sendEvent({ STOP_ALL_ENTITIES }, nullptr);
	else if (evt.keysym.sym == SDLK_h && manualControl) {
		mNode->getParentSceneNode()->pitch(Ogre::Degree(5));
		sendEvent({ CHECK_COLLISION }, this);
	}
	else if (evt.keysym.sym == SDLK_m && manualControl)
		mNode->getParentSceneNode()->yaw(Ogre::Degree(3));
	else if (evt.keysym.sym == SDLK_n)
		manualControl = !manualControl;

	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	mHeliceDNode->frameRendered(evt);
	mHeliceINode->frameRendered(evt);

	mNode->getParentSceneNode()->yaw(Degree(1));

	if (!manualControl) {
		if (detenido) return;

		SceneNode* parentNode = mNode->getParentSceneNode();

		switch (state) {
		case State::MOVING: {
			if (myTimer->getMilliseconds() >= 2000) {
				state = (State)(rand() % 2 + 1);
				myTimer->reset();
			}
			break;
		}
		case State::ROTATING_LEFT: {
			if (myTimer->getMilliseconds() >= 1500) {
				state = State::MOVING;
				myTimer->reset();
			}
			else
				parentNode->yaw(Ogre::Degree(1));
			break;
		}
		case State::ROTATING_RIGHT: {
			if (myTimer->getMilliseconds() >= 1500) {
				state = State::MOVING;
				myTimer->reset();
			}
			else
				parentNode->yaw(Ogre::Degree(-1));
			break;
		}
		}
		parentNode->pitch(Ogre::Degree(1));
	}
}
