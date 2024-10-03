///////////////////////////////////////////////////////////////////////////////
//
// ConvexEntity.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ConvexEntity.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CConvexEntity
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CConvexEntity::CConvexEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CConvexEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CConvexEntity::CConvexEntity(_FLOAT mass)
	: CPhysicsEntity(mass)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CConvexEntity
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CConvexEntity::~CConvexEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateShape
//
///////////////////////////////////////////////////////////////////////////////
	
_OBJECT CConvexEntity::createShape(CPhysicsManager* manager,CListNodeContainer& shapes)
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
	//Get scale.
	C4DVector3 vScale = object->getScale();

	//Vertex attribute.
	CVertexAttribute attribute;
	//Get vertex attribute.
	((CPhysicsPrimitiveObject *)object)->getVertexAttribute(attribute);
#ifdef _DEBUG
	assert(attribute.getVertexType() != CVertexAttribute::nullVertex);
#endif
	//Set vertex count.
	_INTEGER vertexCount = attribute.getVertexCount();
#ifdef _DEBUG
	assert(vertexCount >= 3);
#endif
	//Get vertex array.
	_FLOAT3* vertexArray = attribute.getFloat3Vertex();
#ifdef _DEBUG
	assert(vertexArray != _NULL);
#endif
	//Do while.
	for(_INTEGER i = 0;i < vertexCount;i ++)
	{
		//Set vertex.
		vertexArray[i][0] *= vScale.x();
		vertexArray[i][1] *= vScale.y();
		vertexArray[i][2] *= vScale.z();
	}
	//Now create a collision convex for this entity.
	_OBJECT shape = manager->createConvexShape(vertexCount,(_FLOAT *)vertexArray);
	//Return shape.
	return shape;
}
