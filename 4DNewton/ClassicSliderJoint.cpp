///////////////////////////////////////////////////////////////////////////////
//
// ClassicSliderJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ClassicSliderJoint.h"

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
// CClassicSliderJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicSliderJoint::CClassicSliderJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CClassicSliderJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CClassicSliderJoint::~CClassicSliderJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicSliderJoint::paragramEnd(_LONG timestamp)
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
	::NewtonSliderGetJointForce(JOINT_INSTANCE(joint),&value[0]);
	//Set force.
	object->setJointForce(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get position.
	value.m_x = ::NewtonSliderGetJointPosit(JOINT_INSTANCE(joint));
	//Set position.
	object->setRelativePosition(C4DVector3(value.m_x,value.m_y,value.m_z));

	//Get velocity.
	value.m_x = ::NewtonSliderGetJointVeloc(JOINT_INSTANCE(joint));
	//Set position.
	object->setRelativeVelocity(C4DVector3(value.m_x,value.m_y,value.m_z));
}

/////////////////////////////////////////////////////////////////////////////////
//
// Callback
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicSliderJoint::callback(_OBJECT joint,_FLOAT accel,_FLOAT minFricition,_FLOAT maxFricition,_FLOAT timestep)
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

void CClassicSliderJoint::setCallbacks(_OBJECT joint)
{
	CPhysicsJoint::setCallbacks(joint);
	//Set callbacks.
	::NewtonSliderSetUserCallback(JOINT_INSTANCE(joint),ApplySliderCallBack);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CClassicSliderJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::classicSliderJoint);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CClassicSliderJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::classicSliderJoint);
#endif
	//Get direction.
	C4DVector3 direction = object->getJointAttribute().jointData.jointClassicSlider.direction;
	//Return result.
	return manager->createSliderJoint(object->getPosition(),direction,getPhysicsChild(),getPhysicsParent());
}

/////////////////////////////////////////////////////////////////////////////////
//
// ApplySliderCallBack
//
/////////////////////////////////////////////////////////////////////////////////

unsigned ApplySliderCallBack(const NewtonJoint* slider,NewtonHingeSliderUpdateDesc* desc)
{
#ifdef _DEBUG
	assert(desc != _NULL);
	assert(slider != _NULL);
#endif
	//Get user data.
	CClassicSliderJoint* joint = (CClassicSliderJoint *)::NewtonJointGetUserData(slider);
	//Check result.
	if(joint != _NULL)
	{
		//Callback.
		joint->callback((_OBJECT)slider,desc->m_accel,desc->m_minFriction,desc->m_maxFriction,desc->m_timestep);
	}
	//Return true.
	return _TRUE;
}
