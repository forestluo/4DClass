///////////////////////////////////////////////////////////////////////////////
//
// ClassicUpVectorJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ClassicUpVectorJoint.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define JOINT_INSTANCE(p)									((const NewtonJoint *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CClassicUpVectorJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicUpVectorJoint::CClassicUpVectorJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CClassicUpVectorJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicUpVectorJoint::~CClassicUpVectorJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicUpVectorJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::classicUpVectorJoint);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CClassicUpVectorJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::classicUpVectorJoint);
#endif
	//Get direction.
	C4DVector3 direction = object->getJointAttribute().jointData.jointClassicUpVector.direction;
	//Return result.
	return manager->createUpVectorJoint(direction,getPhysicsChild());
}
