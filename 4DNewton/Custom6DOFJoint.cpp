///////////////////////////////////////////////////////////////////////////////
//
// Custom6DOFJoint.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "Custom6DOFJoint.h"

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
#define DEFAULT_MAJOR_DIRECTION								C4DVector3(1.0f,0.0f,0.0f)
#define DEFAULT_MINOR_DIRECTION								C4DVector3(0.0f,0.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CCustom6DOFJoint
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCustom6DOFJoint::CCustom6DOFJoint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCustom6DOFJoint
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCustom6DOFJoint::~CCustom6DOFJoint(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// SetLimits
//
/////////////////////////////////////////////////////////////////////////////////

void CCustom6DOFJoint::setLimits(_OBJECT joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(object != _NULL);
	assert(object->getJointType() == CJointAttribute::custom6DOFJoint);
#endif
	//Limitation of joint.
	C4DVector3 vMinLinearLimits = object->getJointAttribute().jointData.jointCustom6DOF.minLinearLimits;
	C4DVector3 vMaxLinearLimits = object->getJointAttribute().jointData.jointCustom6DOF.maxLinearLimits;
	C4DVector3 vMinAngulaLimits = object->getJointAttribute().jointData.jointCustom6DOF.minAngulaLimits;
	C4DVector3 vMaxAngulaLimits = object->getJointAttribute().jointData.jointCustom6DOF.maxAngulaLimits;
	//Vector.
	dVector minLinearLimits(vMinLinearLimits.x(),vMinLinearLimits.y(),vMinLinearLimits.z());
	dVector maxLinearLimits(vMaxLinearLimits.x(),vMaxLinearLimits.y(),vMaxLinearLimits.z());
	dVector minAngulaLimits(vMinAngulaLimits.x(),vMinAngulaLimits.y(),vMinAngulaLimits.z());
	dVector maxAngulaLimits(vMaxAngulaLimits.x(),vMaxAngulaLimits.y(),vMaxAngulaLimits.z());
	//Set limits.
 	CustomJoint6DOF_SetLinearLimits((NewtonUserJoint *)joint,&minLinearLimits[0],&maxLinearLimits[0]);
 	CustomJoint6DOF_SetAngularLimits((NewtonUserJoint *)joint,&minAngulaLimits[0],&maxAngulaLimits[0]);
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CCustom6DOFJoint::createJoint(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(object->getJointType() == CJointAttribute::custom6DOFJoint);
#endif

	//Get child.
	CPhysicsObject* child = getPhysicsChild();
	//Get collision body.
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
	C4DVector3 majorDirection = object->getMajorDirection();
#ifdef _DEBUG
	assert(majorDirection.length() > 0.0f);
#endif
	//Get value.
	C4DQuaternion childValue(DEFAULT_MAJOR_DIRECTION,majorDirection);
	//Set rotation.
	dQuaternion childRotation(childValue.w(),childValue.x(),childValue.y(),childValue.z());
	//Set matrix.
	dMatrix childMatrix(childRotation,position);

	//Get direction.
	C4DVector3 minorDirection = object->getMinorDirection();
#ifdef _DEBUG
	assert(minorDirection.length() > 0.0f);
#endif
	//Get value.
	C4DQuaternion parentValue(DEFAULT_MINOR_DIRECTION,minorDirection);
	//Set rotation.
	dQuaternion parentRotation(parentValue.w(),parentValue.x(),parentValue.y(),parentValue.z());
	//Set matrix.
	dMatrix parentMatrix(parentRotation,position);

	//Return result.
	return ::CreateCustomJoint6DOF(&childMatrix[0][0],&parentMatrix[0][0],(NewtonBody *)childBody,(NewtonBody *)parentBody);
}
