///////////////////////////////////////////////////////////////////////////////
//
// CustomBallJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CustomBallJoint.h"

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

#define COLLISION_BODY(p)									((const NewtonBody *)(p))
#define DEFAULT_DIRECTION									C4DVector3(1.0f,0.0f,0.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CCustomBallJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCustomBallJoint::CCustomBallJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCustomBallJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCustomBallJoint::~CCustomBallJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CCustomBallJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::customBallJoint);
#endif

	//Get cone angle.
	dFloat maxConeAngle = object->getJointAttribute().jointData.jointCustomBall.maxConeAngle;
	//Set cone angle.
	::BallAndSocketSetConeAngle((NewtonUserJoint *)joint,maxConeAngle);

	//Get min twist angle.
	dFloat minTwistAngle = object->getJointAttribute().jointData.jointCustomBall.minTwistAngle;
	//Get max twist angle.
	dFloat maxTwistAngle = object->getJointAttribute().jointData.jointCustomBall.maxTwistAngle;
	//Set twist angle.
	::BallAndSocketSetTwistAngle((NewtonUserJoint *)joint,minTwistAngle,maxTwistAngle);
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CCustomBallJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::customBallJoint);
#endif

	//Get child.
	CPhysicsObject* child = getPhysicsChild();
	//Get child body.
	_OBJECT childBody = manager->getCollisionBody(child);
#ifdef _DEBUG
	assert(childBody != _NULL);
#endif
	//Get parent.
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
	return ::CreateCustomBallAndSocket(&matrix[0][0],(NewtonBody *)childBody,(NewtonBody *)parentBody);
}
