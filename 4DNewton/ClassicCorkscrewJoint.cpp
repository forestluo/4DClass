///////////////////////////////////////////////////////////////////////////////
//
// ClassicCorkscrewJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ClassicCorkscrewJoint.h"

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
// CClassicCorkscrewJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicCorkscrewJoint::CClassicCorkscrewJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CClassicCorkscrewJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicCorkscrewJoint::~CClassicCorkscrewJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicCorkscrewJoint::paragramEnd(_LONG timestamp)
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
	::NewtonCorkscrewGetJointForce(JOINT_INSTANCE(joint),&value[0]);
	//Set force.
	object->setJointForce(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get angle.
	value.m_x = ::NewtonCorkscrewGetJointAngle(JOINT_INSTANCE(joint));
	//Set angle.
	object->setRelativeAngle(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get omega
	value.m_x = ::NewtonCorkscrewGetJointOmega(JOINT_INSTANCE(joint));
	//Set omega.
	object->setRelativeOmega(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get position.
	value.m_x = ::NewtonCorkscrewGetJointPosit(JOINT_INSTANCE(joint));
	//Set position.
	object->setRelativePosition(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get velocity.
	value.m_x = ::NewtonCorkscrewGetJointVeloc(JOINT_INSTANCE(joint));
	//Set position.
	object->setRelativeVelocity(C4DVector3(value.m_x,value.m_y,value.m_z));
}

/////////////////////////////////////////////////////////////////////////////////
//
// Callback
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicCorkscrewJoint::callback(_OBJECT joint,_FLOAT accel,_FLOAT minFricition,_FLOAT maxFricition,_FLOAT timestep)
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

void CClassicCorkscrewJoint::setCallbacks(_OBJECT joint)
{
	CPhysicsJoint::setCallbacks(joint);
	//Set callbacks.
	::NewtonCorkscrewSetUserCallback(JOINT_INSTANCE(joint),ApplyCorkscrewCallBack);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicCorkscrewJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::classicCorkscrewJoint);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CClassicCorkscrewJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::classicCorkscrewJoint);
#endif
	//Get direction.
	C4DVector3 direction = object->getJointAttribute().jointData.jointClassicCorkscrew.direction;
	//Return result.
	return manager->createCorkscrewJoint(object->getPosition(),direction,getPhysicsChild(),getPhysicsParent());
}

/////////////////////////////////////////////////////////////////////////////////
//
// ApplyCorkscrewCallBack
//
/////////////////////////////////////////////////////////////////////////////////

unsigned ApplyCorkscrewCallBack(const NewtonJoint* corkscrew,NewtonHingeSliderUpdateDesc* desc)
{
#ifdef _DEBUG
	assert(desc != _NULL);
	assert(corkscrew != _NULL);
#endif
	//Get user data.
	CClassicCorkscrewJoint* joint = (CClassicCorkscrewJoint *)::NewtonJointGetUserData(corkscrew);
	//Check result.
	if(joint != _NULL)
	{
		//Callback.
		joint->callback((_OBJECT)corkscrew,desc->m_accel,desc->m_minFriction,desc->m_maxFriction,desc->m_timestep);
	}
	//Return true.
	return _TRUE;
}
