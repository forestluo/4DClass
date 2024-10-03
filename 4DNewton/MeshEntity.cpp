///////////////////////////////////////////////////////////////////////////////
//
// MeshEntity.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "MeshEntity.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CMeshEntity
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CMeshEntity::CMeshEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CMeshEntity
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CMeshEntity::~CMeshEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CMeshEntity::createShape(CPhysicsManager* manager,CListNodeContainer& shapes)
{
#ifdef _DEBUG
	assert(manager != _NULL);
#endif

	dVector minBox;
	dVector maxBox;
	//Get the Bounding Box for this entity
	getBoundingBox(minBox, maxBox);

	dVector size (maxBox - minBox);
	dVector origin ((maxBox + minBox).Scale (0.5f));
	size.m_w = 1.0f;
	origin.m_w = 1.0f;

#ifdef _DEBUG
	assert(object != _NULL);
	assert(object->getObjectType() == CWorldObject::primitiveObject);
#endif
	//Get attribute.
	CPrimitiveAttribute primitiveAttribute = ((CPhysicsPrimitiveObject *)object)->getPrimitiveAttribute();
#ifdef _DEBUG
	assert(primitiveAttribute.getType() == CPrimitiveAttribute::grid4x3Primitive ||
		primitiveAttribute.getType() == CPrimitiveAttribute::grid20x15Primitive);
#endif

	//Index attribute.
	CIndexAttribute indexAttribute;
	//Get index attribute.
	((CPhysicsPrimitiveObject *)object)->getIndexAttribute(indexAttribute);
#ifdef _DEBUG
	assert(indexAttribute.getIndexType() != CVertexAttribute::nullVertex);
#endif
	//Set index count.
	_INTEGER indexCount = indexAttribute.getIndexCount();
#ifdef _DEBUG
	assert(indexCount >= 3);
#endif
	//Get index array.
	_SHORT3* indexArray = indexAttribute.getShort3Index();
#ifdef _DEBUG
	assert(indexArray != _NULL);
#endif

	//Vertex attribute.
	CVertexAttribute vertexAttribute;
	//Get vertex attribute.
	((CPhysicsPrimitiveObject *)object)->getVertexAttribute(vertexAttribute);
#ifdef _DEBUG
	assert(vertexAttribute.getVertexType() != CVertexAttribute::nullVertex);
#endif
	//Set vertex count.
	_INTEGER vertexCount = vertexAttribute.getVertexCount();
#ifdef _DEBUG
	assert(vertexCount >= 3);
#endif
	//Get vertex array.
	_FLOAT3* vertexArray = vertexAttribute.getFloat3Vertex();
#ifdef _DEBUG
	assert(vertexArray != _NULL);
#endif

	//Now create a collision convex for this entity.
	_OBJECT shape = manager->createMeshShape(3 * indexCount,(_SHORT *)indexArray,(_FLOAT *)vertexArray);
	//Return shape.
	return shape;
}
