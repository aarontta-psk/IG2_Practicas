#include "Plano.h"
#include <OgreMeshManager.h>

Plano::Plano(SceneNode* node, const String& name, const Plane& plane,
	Real width, Real height,
	int xsegments, int ysegments,
	bool normals, unsigned short numTexCoordSets,
	Real uTile, Real vTile, const Vector3& upVector,
	HardwareBuffer::Usage vertexBufferUsage,
	HardwareBuffer::Usage indexBufferUsage,
	bool vertexShadowBuffer, bool indexShadowBuffer) : EntityIG(node, ""), triggered(false)
{
	MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		width, height, xsegments, ysegments, normals, numTexCoordSets, uTile, vTile, upVector,
		vertexBufferUsage, indexBufferUsage, vertexShadowBuffer, indexShadowBuffer);

	planeM = mSM->createEntity(name);
	setMaterialName("Practica1/White");
	mNode->attachObject(planeM);

	myTimer = new Timer();
}

void Plano::frameRendered(const Ogre::FrameEvent& evt)
{
	if (triggered && myTimer->getMilliseconds() > 5000)
	{
		setMaterialName("Practica1/BeachStones");
		triggered = false;
	}
}

void Plano::setMaterialName(String materialName)
{
	planeM->setMaterialName(materialName);
}

void Plano::setReflejo(Camera* cam)
{
}

void Plano::setEspejo(Camera* cam)
{
}

void Plano::receiveEvent(Message message, EntityIG* entidad)
{
	if (message.id_ == BOMB)
	{
		triggered = true;
		myTimer->reset();
	}
}

inline bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return true;
}
