///////////////////////////////////////////////////////////////////////////////
//
// JointObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "JointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundObject.h"
#include "PrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CJointObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CJointObject::CJointObject(_INTEGER jointType)
	: CWorldJointObject(jointType)
	, CD3DXJointObject(jointType)
	, CPhysicsJointObject(jointType)
{
	//Set this.
	setThis(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// CJointObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CJointObject::CJointObject(const CJointAttribute& attribute)
	: CWorldJointObject(attribute)
	, CD3DXJointObject(attribute)
	, CPhysicsJointObject(attribute)
{
	//Set this.
	setThis(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// CJointObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CJointObject::~CJointObject(void)
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
		//Check result.
		if(object->isPhysicsObject()
			&& object->isRenderableObject())
		{
			//Remove it from list.
			CWorldObject::removeObject(object);

			//Get this.
			_OBJECT thisObject = object->getThis();
#ifdef _DEBUG
			assert(thisObject != _NULL);
#endif
			//Check type.
			if(object->isJointObject())
			{
				//Delete object.
				delete (CJointObject *)thisObject;
			}
			else if(object->isCompoundObject())
			{
				//Delete object.
				delete (CCompoundObject *)thisObject;
			}
			else if(object->isPrimitiveObject())
			{
				//Delete object.
				delete (CPrimitiveObject *)thisObject;
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
		}
	}
}
