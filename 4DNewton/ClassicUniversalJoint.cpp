///////////////////////////////////////////////////////////////////////////////
//
// ClassicUniversalJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ClassicUniversalJoint.h"

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
// CClassicUniversalJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicUniversalJoint::CClassicUniversalJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CClassicUniversalJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicUniversalJoint::~CClassicUniversalJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicUniversalJoint::paragramEnd(_LONG timestamp)
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
	::NewtonUniversalGetJointForce(JOINT_INSTANCE(joint),&value[0]);
	//Set force.
	object->setJointForce(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get angle.
	value.m_x = ::NewtonUniversalGetJointAngle0(JOINT_INSTANCE(joint));
	//Get angle.
	value.m_y = ::NewtonUniversalGetJointAngle1(JOINT_INSTANCE(joint));
	//Set angle.
	object->setRelativeAngle(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get omega.
	value.m_x = ::NewtonUniversalGetJointOmega0(JOINT_INSTANCE(joint));
	//Get omega.
	value.m_y = ::NewtonUniversalGetJointOmega1(JOINT_INSTANCE(joint));
	//Set omega.
	object->setRelativeOmega(C4DVector3(value.m_x,value.m_y,value.m_z));
}

/////////////////////////////////////////////////////////////////////////////////
//
// Callback
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicUniversalJoint::callback(_OBJECT joint,_FLOAT accel,_FLOAT minFricition,_FLOAT maxFricition,_FLOAT timestep)
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

void CClassicUniversalJoint::setCallbacks(_OBJECT joint)
{
	CPhysicsJoint::setCallbacks(joint);
	//Set callbacks.
	::NewtonUniversalSetUserCallback(JOINT_INSTANCE(joint),ApplyUniversalCallBack);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicUniversalJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::classicUniversalJoint);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CClassicUniversalJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::classicUniversalJoint);
#endif
	//Get direction.
	C4DVector3 direction0 = object->getJointAttribute().jointData.jointClassicUniversal.majorDirection;
	//Get direction.
	C4DVector3 direction1 = object->getJointAttribute().jointData.jointClassicUniversal.minorDirection;
	//Return result.
	return manager->createUniversalJoint(object->getPosition(),direction0,direction1,getPhysicsChild(),getPhysicsParent());
}

/////////////////////////////////////////////////////////////////////////////////
//
// ApplyUniversalCallBack
//
/////////////////////////////////////////////////////////////////////////////////

unsigned ApplyUniversalCallBack(const NewtonJoint* universal,NewtonHingeSliderUpdateDesc* desc)
{
#ifdef _DEBUG
	assert(desc != _NULL);
	assert(universal != _NULL);
#endif
	//Get user data.
	CClassicUniversalJoint* joint = (CClassicUniversalJoint *)::NewtonJointGetUserData(universal);
	//Check result.
	if(joint != _NULL)
	{
		//Callback.
		joint->callback((_OBJECT)universal,desc->m_accel,desc->m_minFriction,desc->m_maxFriction,desc->m_timestep);
	}
	//Return true.
	return _TRUE;
}
