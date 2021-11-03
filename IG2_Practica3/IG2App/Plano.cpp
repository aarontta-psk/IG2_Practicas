#include "Plano.h"
#include <OgreMeshManager.h>

Plano::Plano(SceneNode* node, const String& name, const Plane& plane,
	Real width, Real height,
	int xsegments, int ysegments,
	bool normals, unsigned short numTexCoordSets,
	Real uTile, Real vTile, const Vector3& upVector,
	HardwareBuffer::Usage vertexBufferUsage,
	HardwareBuffer::Usage indexBufferUsage,
	bool vertexShadowBuffer, bool indexShadowBuffer) : EntityIG(node, "")
{
	MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		width, height, xsegments, ysegments, normals, numTexCoordSets, uTile, vTile, upVector,
		vertexBufferUsage, indexBufferUsage, vertexShadowBuffer, indexShadowBuffer);
	planeM = mSM->createEntity(name);
	SetMaterialName("Practica1/Black");
	mNode->attachObject(planeM);
}

void Plano::SetMaterialName(String materialName)
{
	planeM->setMaterialName(materialName);
}
