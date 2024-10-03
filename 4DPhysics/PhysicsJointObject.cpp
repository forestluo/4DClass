///////////////////////////////////////////////////////////////////////////////
//
// PhysicsJointObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsJointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsJointObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CPhysicsJointObject::CPhysicsJointObject(_INTEGER jointType)
	: CWorldJointObject(jointType)
{
	//Set this.
	setThis(this);
	//Set object type.
	setObjectType(CTypeAttribute::jointObject);
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsJointObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CPhysicsJointObject::CPhysicsJointObject(const CJointAttribute& attribute)
	: CWorldJointObject(attribute)
{
	//Set this.
	setThis(this);
	//Set object type.
	setObjectType(CTypeAttribute::jointObject);
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsJointObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CPhysicsJointObject::~CPhysicsJointObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// IsPhysicsValid
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CPhysicsJointObject::isPhysicsValid() const
{
	//Get child.
	CWorldObject* child = getJointChild();
	//Check result.
	if(child == _NULL) return _FALSE;
	//Check child.
	if(!child->isPhysicsObject()) return _FALSE;
	//Get physics child.
	CPhysicsObject* physicsChild = (CPhysicsObject *)child->getPhysics();
#ifdef _DEBUG
	assert(physicsChild != _NULL);
#endif
	//Check mass.
	if(physicsChild->getMass() <= 0.0f) return _FALSE;

	//Get parent.
	CWorldObject* parent = getJointParent();
	//Check result.
	if(parent!= _NULL)
	{
		//Check physics object.
		if(!parent->isPhysicsObject()) return _FALSE;
		//Get physics parent.
		CPhysicsObject* physicsParent = (CPhysicsObject *)parent->getPhysics();
#ifdef _DEBUG
		assert(physicsParent != _NULL);
#endif
		//Check mass.
		if(physicsParent->getMass() < 0.0f) return _FALSE;
	}

	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsJointObject::paragramEnd(_LONG timestamp)
{
	//Get child.
	CWorldObject* child = getJointChild();
	//Check child.
	if(child != _NULL && child->isPhysicsObject())
	{
		//Get physics object.
		CPhysicsObject* physicsChild = (CPhysicsObject *)child->getPhysics();
#ifdef _DEBUG
		assert(physicsChild != _NULL);
#endif
		//Calcaulte the world position of joint.
		//First, calculate joint relative position according to child position.
		//The ideal joint will keep the constant direction with the child object.
		//So it is possible to calculate the corrent position accoriding to child position.
		C4DVector3 jointPosition1 = physicsChild->getRotationAccompany(- getRelativeDirection(_TRUE)) + child->getPosition();

		//Get parent.
		CWorldObject* parent = getJointParent();
		//Check result.
		if(parent == _NULL || !parent->isPhysicsObject())
		{
			//There is no parent so the joint position could be decided only by child.
			setPosition(jointPosition1);
		}
		else
		{
			//Get physics object.
			CPhysicsObject* physicsParent = (CPhysicsObject *)parent->getPhysics();
#ifdef _DEBUG
			assert(physicsParent != _NULL);
#endif
			//Calcaulte the world position of joint.
			//First, calculate joint relative position according to parent position.
			//The ideal joint will keep the constant direction with the parent object.
			//So it is possible to calculate the corrent position accoriding to parent position.
			C4DVector3 jointPosition2 = physicsParent->getRotationAccompany(- getRelativeDirection(_FALSE)) + parent->getPosition();
			
			//Ideally, they should be the same.
			//So get the average value to eliminate the error of calculating.
			setPosition((jointPosition1 + jointPosition2) / 2.0f);
		}
	}
	//Call function.
	CPhysicsObject::paragramEnd(timestamp);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetRelativeDirection
//
/////////////////////////////////////////////////////////////////////////////////

C4DVector3 CPhysicsJointObject::getRelativeDirection(_BOOL childFlag) const
{
	//Physics object.
	CPhysicsObject* physicsObject;

	//Get child.
	CWorldObject* child = getJointChild();
	//Get parent.
	CWorldObject* parent = getJointParent();

	//Check child.
	if(childFlag)
	{
		//Check result.
		if(child == _NULL || !child->isPhysicsObject()) return C4DVector3(0.0f,0.0f,0.0f);
		//Get physics child.
		physicsObject = (CPhysicsObject *)child->getPhysics();
	}
	else
	{
		if(parent == _NULL || !parent->isPhysicsObject()) return C4DVector3(0.0f,0.0f,0.0f);
		//Get physics parent.
		physicsObject = (CPhysicsObject *)parent->getPhysics();
	}

	//Origin position.
	C4DVector3 origin;
	//Current position.
	C4DVector3 position;
	//Get keeper.
	CStatusKeeper* keeper = getKeeper();
	//Check keeper.
	if(keeper == _NULL)
	{
		//Get position.
		origin = getPosition();
		//Get position.
		position = childFlag ? child->getPosition() : parent->getPosition();
	}
	else
	{
		//Get previous position.
		origin = keeper->getPosition();

#ifdef _DEBUG
		assert(physicsObject != _NULL);
#endif
		//Get keeper.
		CStatusKeeper* subkeeper = physicsObject->getKeeper();
#ifdef _DEBUG
		assert(subkeeper != _NULL);
#endif
		//Get position.
		position = subkeeper->getPosition();
	}
	//Return result.
	return position - origin;
}
