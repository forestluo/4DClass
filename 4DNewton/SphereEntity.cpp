///////////////////////////////////////////////////////////////////////////////
//
// SphereEntity.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "SphereEntity.h"

///////////////////////////////////////////////////////////////////////////////
//
// CSphereEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CSphereEntity::CSphereEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CSphereEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CSphereEntity::CSphereEntity(_FLOAT mass)
	: CPhysicsEntity(mass)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CSphereEntity
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CSphereEntity::~CSphereEntity(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateShape
//
/////////////////////////////////////////////////////////////////////////////////
	
_OBJECT CSphereEntity::createShape(CPhysicsManager *manager,CListNodeContainer& shapes)
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

	//Now create a collision sphere for this entity.
	return manager->createSphereShape(size.m_x / 2.0f,size.m_y / 2.0f,size.m_z / 2.0f);
}
