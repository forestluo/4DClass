///////////////////////////////////////////////////////////////////////////////
//
// HeightFieldEntity.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "HeightFieldEntity.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CHeightFieldEntity
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CHeightFieldEntity::CHeightFieldEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CHeightFieldEntity
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CHeightFieldEntity::~CHeightFieldEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CHeightFieldEntity::createShape(CPhysicsManager* manager,CListNodeContainer& shapes)
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
	assert(primitiveAttribute.getType() == CPrimitiveAttribute::ground80x60Primitive ||
			primitiveAttribute.getType() == CPrimitiveAttribute::ground320x240Primitive ||
			primitiveAttribute.getType() == CPrimitiveAttribute::ground640x480Primitive);
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
	_OBJECT shape = manager->createHeightFieldShape(primitiveAttribute.rings,
													primitiveAttribute.segments,
													primitiveAttribute.primitiveData.grid.quadWidth,
													primitiveAttribute.primitiveData.grid.quadHeight,(_FLOAT *)vertexArray);
	//Return shape.
	return shape;
}
