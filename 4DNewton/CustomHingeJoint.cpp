///////////////////////////////////////////////////////////////////////////////
//
// CustomHingeJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CustomHingeJoint.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DMath.h"
#include "PhysicsManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define COLLISION_BODY(p)									((const NewtonBody *)(p))
#define DEFAULT_DIRECTION									C4DVector3(1.0f,0.0f,0.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CCustomHingeJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCustomHingeJoint::CCustomHingeJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCustomHingeJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCustomHingeJoint::~CCustomHingeJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CCustomHingeJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::customHingeJoint);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CCustomHingeJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::customHingeJoint);
#endif

	//Get physics child.
	CPhysicsObject* child = getPhysicsChild();
	//Get child body.
	_OBJECT childBody = manager->getCollisionBody(getPhysicsChild());
#ifdef _DEBUG
	assert(childBody != _NULL);
#endif

	//Get physics parent.
	CPhysicsObject* parent = getPhysicsParent();
	//Get parent body.
	_OBJECT parentBody = parent != _NULL ? manager->getCollisionBody(parent) : _NULL;
#ifdef _DEBUG
	assert(childBody != parentBody);
#endif

	//Get position.
	dVector position = object->getPosition();
	//Get direction.
	C4DVector3 direction = object->getMajorDirection();
#ifdef _DEBUG
	assert(direction.length() > 0.0f);
#endif
	//Get value.
	C4DQuaternion value(DEFAULT_DIRECTION,direction);
	//Set rotation.
	dQuaternion rotation(value.w(),value.x(),value.y(),value.z());
	//Set matrix.
	dMatrix matrix(rotation,position);
	//Return result.
	return ::CreateCustomHinge(&matrix[0][0],(NewtonBody *)childBody,(NewtonBody *)parentBody);
}
