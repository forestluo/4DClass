///////////////////////////////////////////////////////////////////////////////
//
// ClassicHingeJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ClassicHingeJoint.h"

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
// CClassicHingeJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicHingeJoint::CClassicHingeJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CClassicHingeJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicHingeJoint::~CClassicHingeJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicHingeJoint::paragramEnd(_LONG timestamp)
{
	CPhysicsJoint::paragramEnd(timestamp);

	//Value.
	dVector value(0.0f,0.0f,0.0f);

#ifdef _DEBUG
	assert(joint != _NULL);
	assert(object != _NULL);
	assert(CJointAttribute::isClassicJoint(object->getJointType()));
#endif

	//Get force.
	::NewtonHingeGetJointForce(JOINT_INSTANCE(joint),&value[0]);
	//Set force.
	object->setJointForce(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get angle.
	value.m_x = ::NewtonHingeGetJointAngle(JOINT_INSTANCE(joint));
	//Set angle.
	object->setRelativeAngle(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get omega.
	value.m_x = ::NewtonHingeGetJointOmega(JOINT_INSTANCE(joint));
	//Set omega.
	object->setRelativeOmega(C4DVector3(value.m_x,value.m_y,value.m_z));
}

/////////////////////////////////////////////////////////////////////////////////
//
// Callback
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicHingeJoint::callback(_OBJECT joint,_FLOAT accel,_FLOAT minFricition,_FLOAT maxFricition,_FLOAT timestep)
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

void CClassicHingeJoint::setCallbacks(_OBJECT joint)
{
	CPhysicsJoint::setCallbacks(joint);
	//Set callbacks.
	::NewtonHingeSetUserCallback(JOINT_INSTANCE(joint),ApplyHingeCallBack);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicHingeJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::classicHingeJoint);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CClassicHingeJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::classicHingeJoint);
#endif
	//Get direction.
	C4DVector3 direction = object->getJointAttribute().jointData.jointClassicHinge.direction;
	//Return result.
	return manager->createHingeJoint(object->getPosition(),direction,getPhysicsChild(),getPhysicsParent());
}

/////////////////////////////////////////////////////////////////////////////////
//
// ApplyHingeCallBack
//
/////////////////////////////////////////////////////////////////////////////////

unsigned ApplyHingeCallBack(const NewtonJoint* hinge,NewtonHingeSliderUpdateDesc* desc)
{
#ifdef _DEBUG
	assert(desc != _NULL);
	assert(hinge != _NULL);
#endif
	//Get user data.
	CClassicHingeJoint* joint = (CClassicHingeJoint *)::NewtonJointGetUserData(hinge);
	//Check result.
	if(joint != _NULL)
	{
		//Callback.
		joint->callback((_OBJECT)hinge,desc->m_accel,desc->m_minFriction,desc->m_maxFriction,desc->m_timestep);
	}
	//Return true.
	return _TRUE;
}
