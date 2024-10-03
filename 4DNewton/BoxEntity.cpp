///////////////////////////////////////////////////////////////////////////////
//
// BoxEntity.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "BoxEntity.h"

///////////////////////////////////////////////////////////////////////////////
//
// CBoxEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CBoxEntity::CBoxEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CBoxEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CBoxEntity::CBoxEntity(_FLOAT mass)
	: CPhysicsEntity(mass)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CBoxEntity
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CBoxEntity::~CBoxEntity(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateShape
//
/////////////////////////////////////////////////////////////////////////////////
	
_OBJECT CBoxEntity::createShape(CPhysicsManager *manager,CListNodeContainer& shapes)
{
#ifdef _DEBUG
	assert(manager != _NULL);
#endif

	dVector minBox;
	dVector maxBox;
	//Get the Bounding Box for this entity.
	getBoundingBox(minBox,maxBox);

	//Calculate the box size and dimensions of the physics collision shape. 
	dVector size(maxBox - minBox);
	dVector origin((maxBox + minBox).Scale(0.5f));
	size.m_w = 1.0f;
	origin.m_w = 1.0f;

	//Make and offset matrix for this collision shape.
	dMatrix offset(GetIdentityMatrix());
	offset.m_posit = origin;

	//Now create a collision Box for this entity.
	return manager->createBoxShape(size.m_x,size.m_y,size.m_z);
}
