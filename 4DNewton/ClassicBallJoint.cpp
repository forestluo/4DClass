///////////////////////////////////////////////////////////////////////////////
//
// ClassicBallJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ClassicBallJoint.h"

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
// CClassicBallJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicBallJoint::CClassicBallJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CClassicBallJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicBallJoint::~CClassicBallJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicBallJoint::paragramEnd(_LONG timestamp)
{
	CPhysicsJoint::paragramEnd(timestamp);

	//Value.
	dVector value;

#ifdef _DEBUG
	assert(joint != _NULL);
	assert(object != _NULL);
	assert(CJointAttribute::isClassicJoint(object->getJointType()));
#endif

	//Get force.
	::NewtonBallGetJointForce(JOINT_INSTANCE(joint),&value[0]);
	//Set force.
	object->setJointForce(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get angle.
	::NewtonBallGetJointAngle(JOINT_INSTANCE(joint),&value[0]);
	//Set angle.
	object->setRelativeAngle(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get omega.
	::NewtonBallGetJointOmega(JOINT_INSTANCE(joint),&value[0]);
	//Set omega.
	object->setRelativeOmega(C4DVector3(value.m_x,value.m_y,value.m_z));
}

/////////////////////////////////////////////////////////////////////////////////
//
// Callback
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicBallJoint::callback(_OBJECT joint,_FLOAT timestep)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(object != _NULL);
	assert(CJointAttribute::isClassicJoint(object->getJointType()));
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetCallbacks
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicBallJoint::setCallbacks(_OBJECT joint)
{
	CPhysicsJoint::setCallbacks(joint);
	//Set callbacks.
	::NewtonBallSetUserCallback(JOINT_INSTANCE(joint),ApplyBallCallBack);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicBallJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::classicBallJoint);
#endif
	//Get cone axis.
	C4DVector3 coneAxis = object->getJointAttribute().jointData.jointClassicBall.direction;
#ifdef _DEBUG
	assert(coneAxis.length() > 0.0f);
#endif
	//Vector.
	dVector pin(coneAxis.x(),coneAxis.y(),coneAxis.z());

	//Get max cone angle.
	_FLOAT maxConeAngle = object->getJointAttribute().jointData.jointClassicBall.maxConeAngle;
#ifdef _DEBUG
	assert(maxConeAngle >= 0.0f);
#endif

	//Get max twist angle.
	_FLOAT maxTwistAngle = object->getJointAttribute().jointData.jointClassicBall.maxTwistAngle;
#ifdef _DEBUG
	assert(maxTwistAngle >= 0.0f);
#endif

#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Set limits.
	::NewtonBallSetConeLimits(JOINT_INSTANCE(joint),&pin[0],maxConeAngle,maxTwistAngle);
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CClassicBallJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::classicBallJoint);
#endif
	//Return result.
	return manager->createBallJoint(object->getPosition(),getPhysicsChild(),getPhysicsParent());
}

/////////////////////////////////////////////////////////////////////////////////
//
// ApplyBallCallBack
//
/////////////////////////////////////////////////////////////////////////////////

void ApplyBallCallBack(const NewtonJoint* ball,dFloat timestep)
{
#ifdef _DEBUG
	assert(ball != _NULL);
#endif
	//Get user data.
	CClassicBallJoint* joint = (CClassicBallJoint *)::NewtonJointGetUserData(ball);
	//Check result.
	if(joint != _NULL)
	{
		//Callback.
		joint->callback((_OBJECT)ball,timestep);
	}
}
