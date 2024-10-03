///////////////////////////////////////////////////////////////////////////////
//
// PhysicsObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsJointObject.h"
#include "PhysicsCompoundObject.h"
#include "PhysicsPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsObject::CPhysicsObject(void)
{
	//Set this.
	setThis(this);
	//Set physics.
	CWorldObject::setPhysics(this);
	//Set default value.
	keeper = (CStatusKeeper *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsObject::~CPhysicsObject(void)
{
	//Enumeration.
	CListNodeEnumeration iterator;
	//Get numeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get world object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Get this object.
		_OBJECT thisObject = object->getThis();
#ifdef _DEBUG
		assert(thisObject != _NULL);
#endif
		//Check result.
		if(object->isPhysicsObject()
			&& !object->isRenderableObject())
		{
			//Remove it from list.
			CWorldObject::removeObject(object);

			//Check type.
			if(object->isJointObject())
			{
				//Delete object.
				delete (CPhysicsJointObject *)thisObject;
			}
			else if(object->isCompoundObject())
			{
				//Delete object.
				delete (CPhysicsCompoundObject *)thisObject;
			}
			else if(object->isPrimitiveObject())
			{
				//Delete object.
				delete (CPhysicsPrimitiveObject *)thisObject;
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
		}
#ifdef _DEBUG
		//Check result.
		else if(object->isRenderableObject() && object->isPhysicsObject()) assert(_FALSE);
#endif
	}

	//Check status keeper.
	if(keeper != _NULL)
	{
		//Delete keeper.
		delete (CStatusKeeper *)keeper;
		//Clear keeper.
		keeper = (CStatusKeeper *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
///////////////////////////////////////////////////////////////////////////////
	
void CPhysicsObject::paragramEnd(_LONG timestamp)
{
	//Keep status.
	if(keeper != _NULL)
	{
		//Keep current.
		keeper->keepCurrent(this,timestamp);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsEnd
//
///////////////////////////////////////////////////////////////////////////////
	
void CPhysicsObject::physicsEnd()
{
	//Check status keeper.
	if(keeper != _NULL)
	{
		//Recover status.
		keeper->recoverOrigin(this);

		//Delete keeper.
		delete (CStatusKeeper *)keeper;
		//Clear keeper.
		keeper = (CStatusKeeper *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsBegin
//
///////////////////////////////////////////////////////////////////////////////
	
void CPhysicsObject::physicsBegin(_LONG timestamp)
{
	//Check status keeper.
	if(keeper != _NULL)
	{
		//Delete keeper.
		delete (CStatusKeeper *)keeper;
		//Clear keeper.
		keeper = (CStatusKeeper *)_NULL;
	}
	//Create keeper.
	keeper = new CStatusKeeper();
#ifdef _DEBUG
	assert(keeper != _NULL);
#endif
	//Keep status.
	keeper->keepOrigin(this,timestamp);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetKeeper
//
///////////////////////////////////////////////////////////////////////////////

CStatusKeeper* CPhysicsObject::getKeeper() const
{
	//Return result.
	return keeper;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetRotationAccompany
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CPhysicsObject::getRotationAccompany(const C4DVector3& vector) const
{
	//Get current rotation.
	C4DQuaternion currentRotation = getRotation();
	//Get reserved quaternion.
	C4DQuaternion reservedRotation = keeper == _NULL ? currentRotation : keeper->getRotation();
	//Calculate rotation.
	C4DQuaternion rotation = reservedRotation.inverse().cross(currentRotation);
	//Return result.
	return rotation.rotate(vector);
}
