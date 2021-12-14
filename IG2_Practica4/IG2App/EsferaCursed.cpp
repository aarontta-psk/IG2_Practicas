#include "EsferaCursed.h"

EsferaCursed::EsferaCursed(SceneNode* node, Vector3 scale, Vector3 pos) : EntityIG(node)
{
	ent = mSM->createEntity("sphere.mesh");
	ent->setMaterialName("Practica1/Cursed");
	mNode->attachObject(ent);
	mNode->setScale(scale);
	mNode->setPosition(pos);
}

void EsferaCursed::receiveEvent(Message message, EntityIG* entidad)
{
	if (message.id_ == PRE_REFLECTION)
		ent->setMaterialName("Practica1/Desruc");
	else if (message.id_ == POST_REFLECTION)
		ent->setMaterialName("Practica1/Cursed");
}
