///////////////////////////////////////////////////////////////////////////////
//
// PhysicsClassicJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsClassicJoint.h"

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
#define NEWTON_JOINT(p)										((const NewtonJoint *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsClassicJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsClassicJoint::CPhysicsClassicJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsClassicJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsClassicJoint::~CPhysicsClassicJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// SetCallbacks
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsClassicJoint::setCallbacks(_OBJECT joint)
{
	//Set callbacks.
	CPhysicsJoint::setCallbacks(joint);

	//Set destructor callback.
	//::NewtonJointSetDestructor(NEWTON_JOINT(joint),DestroyJointCallback);
}

/////////////////////////////////////////////////////////////////////////////////
//
// DetachObject
//
/////////////////////////////////////////////////////////////////////////////////
	
void CPhysicsClassicJoint::detachObject(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
#endif

#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Destroy joint.
	manager->destroyJoint(joint);
}

/////////////////////////////////////////////////////////////////////////////////
//
// AttachObject
//
/////////////////////////////////////////////////////////////////////////////////
	
_BOOL CPhysicsClassicJoint::attachObject(CPhysicsManager* manager,CPhysicsJointObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(this->object == _NULL);
	assert(CJointAttribute::isClassicJoint(object->getJointType()));
#endif
	//Set value.
	this->object = object;

	//Create joint.
    joint = createJoint(manager);
#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Set user data.
	::NewtonJointSetUserData(NEWTON_JOINT(joint),this);

	//Check result.
	setLimits(joint);
	//Set callbacks.
	setCallbacks(joint);

	//Get stiffness.
	_FLOAT stiffness = object->getJointAttribute().stiffness;
#ifdef _DEBUG
	assert(stiffness >= 0.0f && stiffness <= 1.0f);
#endif
	//Set stiffness.
	::NewtonJointSetStiffness(NEWTON_JOINT(joint),stiffness);
	//Set self collision.
	::NewtonJointSetCollisionState(NEWTON_JOINT(joint),object->isSelfCollision());
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// DestroyJointCallback
//
///////////////////////////////////////////////////////////////////////////////

void DestroyJointCallback(const NewtonJoint* joint)
{
	//Joint.
	CPhysicsClassicJoint* object;

#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Get the entity associated with this rigid body.
	object = (CPhysicsClassicJoint *)::NewtonJointGetUserData(joint);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Call function.
	object->destroy();
}
