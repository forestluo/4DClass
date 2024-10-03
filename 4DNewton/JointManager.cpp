///////////////////////////////////////////////////////////////////////////////
//
// JointManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "JointManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsManager.h"

#include "NewtonPhysics.h"
#include "ListNodeContainer.h"

#include "ClassicBallJoint.h"
#include "ClassicHingeJoint.h"
#include "ClassicSliderJoint.h"
#include "ClassicUpVectorJoint.h"
#include "ClassicUniversalJoint.h"
#include "ClassicCorkscrewJoint.h"

#include "Custom6DOFJoint.h"
#include "CustomBallJoint.h"
#include "CustomHingeJoint.h"
#include "CustomSliderJoint.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define WORLD_INSTANCE(p)									((const NewtonWorld *)(p))
#define COLLISION_BODY(p)									((const NewtonBody *)(p))
#define JOINTS_INSTANCE(p)									((CListNodeContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CJointManager
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CJointManager::CJointManager(void)
{
	//Create joints.
	joints = new CListNodeContainer();
#ifdef _DEBUG
	assert(joints != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CJointManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CJointManager::~CJointManager(void)
{
	//Release all.
	releaseAll();
	//Check joints.
	if(joints != _NULL)
	{
		//Delete joints.
		delete (CListNodeContainer *)joints;
		//Clear joints.
		joints = (CListNodeContainer *)_NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
/////////////////////////////////////////////////////////////////////////////////

void CJointManager::releaseAll()
{
	//Get enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(joints != _NULL);
#endif

	//Get enumeration.
	JOINTS_INSTANCE(joints)->getEnumeration(&iterator);
	//Do while
	while(iterator.hasMoreElements())
	{
		//Get element.
		_OBJECT value = iterator.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
		assert(physicsManager != _NULL);
#endif
		//Detach object.
		((CPhysicsJoint *)value)->detachObject((CPhysicsManager *)physicsManager);
		//Delete entity.
		delete (CPhysicsJoint *)value;
	}
	//Clear all.
	JOINTS_INSTANCE(joints)->clearAll();
}

///////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
///////////////////////////////////////////////////////////////////////////////

void CJointManager::paragramEnd(_LONG timestamp)
{
	//Enumeration.
	CListNodeEnumeration enumeration;
#ifdef _DEBUG
	assert(joints != _NULL);
#endif
	//Get enumeration.
	JOINTS_INSTANCE(joints)->getEnumeration(&enumeration);
	//Do while
	while(enumeration.hasMoreElements())
	{
		//Get element.
		_OBJECT value = enumeration.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Set paragram.
		((CPhysicsJoint *)value)->paragramEnd(timestamp);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsEnd
//
///////////////////////////////////////////////////////////////////////////////

void CJointManager::physicsEnd()
{
	//Enumeration.
	CListNodeEnumeration enumeration;
#ifdef _DEBUG
	assert(joints != _NULL);
#endif
	//Get enumeration.
	JOINTS_INSTANCE(joints)->getEnumeration(&enumeration);
	//Do while
	while(enumeration.hasMoreElements())
	{
		//Get element.
		_OBJECT value = enumeration.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Set paragram.
		((CPhysicsJoint *)value)->physicsEnd();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsBegin
//
///////////////////////////////////////////////////////////////////////////////
	
void CJointManager::physicsBegin(_LONG timestamp)
{
	//Enumeration.
	CListNodeEnumeration enumeration;
#ifdef _DEBUG
	assert(joints != _NULL);
#endif
	//Get enumeration.
	JOINTS_INSTANCE(joints)->getEnumeration(&enumeration);
	//Do while
	while(enumeration.hasMoreElements())
	{
		//Get element.
		_OBJECT value = enumeration.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Set paragram.
		((CPhysicsJoint *)value)->physicsBegin(timestamp);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// DestroyJoint
//
///////////////////////////////////////////////////////////////////////////////

void CJointManager::destroyJoint(_OBJECT joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Destroy joint.
	::NewtonDestroyJoint(WORLD_INSTANCE(world),(NewtonJoint *)joint);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateUpVectorJoint
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CJointManager::createUpVectorJoint(const C4DVector3& direction,
											CPhysicsObject* child)
{
	//Vector.
	dVector pivotDirection(direction.x(),direction.y(),direction.z());

#ifdef _DEBUG
	assert(child != _NULL);
	assert(child->getMass() > 0.0f);
	assert(child->getObjectType() != CWorldObject::jointObject);
#endif

#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif
	//Get child body.
	_OBJECT childBody = ((CPhysicsManager *)physicsManager)->getCollisionBody(child);
#ifdef _DEBUG
	assert(childBody != _NULL);
#endif
	//Return result.
	return ::NewtonConstraintCreateUpVector(WORLD_INSTANCE(world),
											&pivotDirection[0],
											COLLISION_BODY(childBody));
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateBallJoint
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CJointManager::createBallJoint(const C4DVector3& position,
										CPhysicsObject* child,CPhysicsObject* parent)
{
	//Vector.
	dVector pivotPoint(position.x(),position.y(),position.z());

#ifdef _DEBUG
	assert(child != _NULL);
	assert(child->getMass() > 0.0f);
	assert(child->getObjectType() != CWorldObject::jointObject);
#endif

#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif
	//Get child body.
	_OBJECT childBody = ((CPhysicsManager *)physicsManager)->getCollisionBody(child);
#ifdef _DEBUG
	assert(childBody != _NULL);
#endif

	//Check parent.
	if(parent != _NULL)
	{
#ifdef _DEBUG
		assert(parent->getMass() >= 0.0f);
		assert(parent->getObjectType() != CWorldObject::jointObject);
#endif
	}
	//Get parent body.
	_OBJECT parentBody = parent != _NULL ? ((CPhysicsManager *)physicsManager)->getCollisionBody(parent) : _NULL;
#ifdef _DEBUG
	assert(childBody != parentBody);
#endif
	//Return result.
	return ::NewtonConstraintCreateBall(WORLD_INSTANCE(world),
										&pivotPoint[0],
										COLLISION_BODY(childBody),COLLISION_BODY(parentBody));
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateHingeJoint
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CJointManager::createHingeJoint(const C4DVector3& position,const C4DVector3& direction,
											CPhysicsObject* child,CPhysicsObject* parent)
{
	//Vector.
	dVector pivotPoint(position.x(),position.y(),position.z());
	dVector pivotDirection(direction.x(),direction.y(),direction.z());

#ifdef _DEBUG
	assert(child != _NULL);
	assert(child->getMass() > 0.0f);
	assert(child->getObjectType() != CWorldObject::jointObject);
#endif

#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif
	//Get child body.
	_OBJECT childBody = ((CPhysicsManager *)physicsManager)->getCollisionBody(child);
#ifdef _DEBUG
	assert(childBody != _NULL);
#endif

	//Check parent.
	if(parent != _NULL)
	{
#ifdef _DEBUG
		assert(parent->getMass() >= 0.0f);
		assert(parent->getObjectType() != CWorldObject::jointObject);
#endif
	}
	//Get parent body.
	_OBJECT parentBody = parent != _NULL ? ((CPhysicsManager *)physicsManager)->getCollisionBody(parent) : _NULL;
#ifdef _DEBUG
	assert(childBody != parentBody);
#endif
	//Return result.
	return ::NewtonConstraintCreateHinge(WORLD_INSTANCE(world),
										 &pivotPoint[0],&pivotDirection[0],
										 COLLISION_BODY(childBody),COLLISION_BODY(parentBody));
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateSliderJoint
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CJointManager::createSliderJoint(const C4DVector3& position,const C4DVector3& direction,
											CPhysicsObject* child,CPhysicsObject* parent)
{
	//Vector.
	dVector pivotPoint(position.x(),position.y(),position.z());
	dVector pivotDirection(direction.x(),direction.y(),direction.z());

#ifdef _DEBUG
	assert(child != _NULL);
	assert(child->getMass() > 0.0f);
	assert(child->getObjectType() != CWorldObject::jointObject);
#endif

#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif
	//Get child body.
	_OBJECT childBody = ((CPhysicsManager *)physicsManager)->getCollisionBody(child);
#ifdef _DEBUG
	assert(childBody != _NULL);
#endif

	//Check parent.
	if(parent != _NULL)
	{
#ifdef _DEBUG
		assert(parent->getMass() >= 0.0f);
		assert(parent->getObjectType() != CWorldObject::jointObject);
#endif
	}
	//Get parent body.
	_OBJECT parentBody = parent != _NULL ? ((CPhysicsManager *)physicsManager)->getCollisionBody(parent) : _NULL;
#ifdef _DEBUG
	assert(childBody != parentBody);
#endif
	//Return result.
	return ::NewtonConstraintCreateSlider(WORLD_INSTANCE(world),
										 &pivotPoint[0],&pivotDirection[0],
										 COLLISION_BODY(childBody),COLLISION_BODY(parentBody));
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCorwscrewJoint
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CJointManager::createCorkscrewJoint(const C4DVector3& position,const C4DVector3& direction,
											CPhysicsObject* child,CPhysicsObject* parent)
{
	//Vector.
	dVector pivotPoint(position.x(),position.y(),position.z());
	dVector pivotDirection(direction.x(),direction.y(),direction.z());

#ifdef _DEBUG
	assert(child != _NULL);
	assert(child->getMass() > 0.0f);
	assert(child->getObjectType() != CWorldObject::jointObject);
#endif

#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif
	//Get child body.
	_OBJECT childBody = ((CPhysicsManager *)physicsManager)->getCollisionBody(child);
#ifdef _DEBUG
	assert(childBody != _NULL);
#endif

	//Check parent.
	if(parent != _NULL)
	{
#ifdef _DEBUG
		assert(parent->getMass() >= 0.0f);
		assert(parent->getObjectType() != CWorldObject::jointObject);
#endif
	}
	//Get parent body.
	_OBJECT parentBody = parent != _NULL ? ((CPhysicsManager *)physicsManager)->getCollisionBody(parent) : _NULL;
#ifdef _DEBUG
	assert(childBody != parentBody);
#endif
	//Return result.
	return ::NewtonConstraintCreateCorkscrew(WORLD_INSTANCE(world),
										 &pivotPoint[0],&pivotDirection[0],
										 COLLISION_BODY(childBody),COLLISION_BODY(parentBody));
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateUniversalJoint
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CJointManager::createUniversalJoint(const C4DVector3& position,const C4DVector3& direction0,const C4DVector3& direction1,
											CPhysicsObject* child,CPhysicsObject* parent)
{
	//Vector.
	dVector pivotPoint(position.x(),position.y(),position.z());
	dVector pivotDirection0(direction0.x(),direction0.y(),direction0.z());
	dVector pivotDirection1(direction1.x(),direction1.y(),direction1.z());

#ifdef _DEBUG
	assert(child != _NULL);
	assert(child->getMass() > 0.0f);
	assert(child->getObjectType() != CWorldObject::jointObject);
#endif

#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif
	//Get child body.
	_OBJECT childBody = ((CPhysicsManager *)physicsManager)->getCollisionBody(child);
#ifdef _DEBUG
	assert(childBody != _NULL);
#endif

	//Check parent.
	if(parent != _NULL)
	{
#ifdef _DEBUG
		assert(parent->getMass() >= 0.0f);
		assert(parent->getObjectType() != CWorldObject::jointObject);
#endif
	}
	//Get parent body.
	_OBJECT parentBody = parent != _NULL ? ((CPhysicsManager *)physicsManager)->getCollisionBody(parent) : _NULL;
#ifdef _DEBUG
	assert(childBody != parentBody);
#endif
	//Return result.
	return ::NewtonConstraintCreateUniversal(WORLD_INSTANCE(world),
										 &pivotPoint[0],&pivotDirection0[0],&pivotDirection1[0],
										 COLLISION_BODY(childBody),COLLISION_BODY(parentBody));
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddJoint
//
/////////////////////////////////////////////////////////////////////////////////

void CJointManager::addJoint(CPhysicsJointObject* object)
{
	//Joint.
	CPhysicsJoint* joint;

#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Get type.
	_INTEGER type = object->getJointType();
	//Check result.
	if(type == CJointAttribute::classicBallJoint)
	{
		//Create joint.
		joint = new CClassicBallJoint();
	}
	else if(type == CJointAttribute::classicHingeJoint)
	{
		//Create joint.
		joint = new CClassicHingeJoint();
	}
	else if(type == CJointAttribute::classicSliderJoint)
	{
		//Create joint.
		joint = new CClassicSliderJoint();
	}
	else if(type == CJointAttribute::classicUpVectorJoint)
	{
		//Create joint.
		joint = new CClassicUpVectorJoint();
	}
	else if(type == CJointAttribute::classicUniversalJoint)
	{
		//Create joint.
		joint = new CClassicUniversalJoint();
	}
	else if(type == CJointAttribute::classicCorkscrewJoint)
	{
		//Create joint.
		joint = new CClassicCorkscrewJoint();
	}
	else if(type == CJointAttribute::custom6DOFJoint)
	{
		//Create joint.
		joint = new CCustom6DOFJoint();
	}
	else if(type == CJointAttribute::customBallJoint)
	{
		//Create joint.
		joint = new CCustomBallJoint();
	}
	else if(type == CJointAttribute::customHingeJoint)
	{
		//Create joint.
		joint = new CCustomHingeJoint();
	}
	else if(type == CJointAttribute::customSliderJoint)
	{
		//Create joint.
		joint = new CCustomSliderJoint();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif
	//Attach object.
	if(joint->attachObject((CPhysicsManager *)physicsManager,object))
	{
		//Add it into list.
		JOINTS_INSTANCE(joints)->addTail(joint);
	}
}
