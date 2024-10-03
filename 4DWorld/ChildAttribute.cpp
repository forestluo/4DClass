///////////////////////////////////////////////////////////////////////////////
//
// ChildAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ChildAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldObject.h"
#include "ListNodeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define OBJECTS_INSTANCE(p)									((CListNodeContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CChildAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CChildAttribute::CChildAttribute(void)
{
	//Create container.
	objects = new CListNodeContainer();
#ifdef _DEBUG
	assert(objects != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CChildAttribute
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CChildAttribute::~CChildAttribute(void)
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(objects != _NULL);
#endif
	//Get numeration.
	OBJECTS_INSTANCE(objects)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get world object.
		CWorldObject* object = (CWorldObject *)iterator.hasMoreElements();
#ifdef _DEBUG
		assert(object != _NULL);
		assert(!object->isPhysicsObject() && !object->isRenderableObject());
#endif
		//Delete object.
		delete (CWorldObject *)object;
	}

	//Check objects.
	if(objects != _NULL)
	{
		//Delete container.
		delete (CListNodeContainer *)objects;
		//Clear container.
		objects = (CListNodeContainer *)_NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetCount
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CChildAttribute::getCount() const
{
#ifdef _DEBUG
	assert(objects != _NULL);
#endif
	//Return result.
	return OBJECTS_INSTANCE(objects)->getCount();
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddObject
//
/////////////////////////////////////////////////////////////////////////////////

void CChildAttribute::addObject(CWorldObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(objects != _NULL);
	assert(!objectExists(object));
#endif
	//Add object.
	OBJECTS_INSTANCE(objects)->addTail(object);
}

/////////////////////////////////////////////////////////////////////////////////
//
// RemoveObject
//
/////////////////////////////////////////////////////////////////////////////////

void CChildAttribute::removeObject(CWorldObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(objectExists(object));
#endif
	//Remove object.
	OBJECTS_INSTANCE(objects)->removeValue(object);
}

/////////////////////////////////////////////////////////////////////////////////
//
// ObjectExists
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CChildAttribute::objectExists(CWorldObject* object) const
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(objects != _NULL);
#endif

	//Get enumeration.
	OBJECTS_INSTANCE(objects)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* thisObject = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(thisObject != _NULL);
#endif
		//Check name.
		if(thisObject == object) return _TRUE;
		//Check instance.
		if(thisObject->getCount() > 0)
		{
			//Check result.
			if(((CChildAttribute *)thisObject)->objectExists(object)) return _TRUE;
		}
	}
	//Return false.
	return _FALSE;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetObject
//
/////////////////////////////////////////////////////////////////////////////////

CWorldObject* CChildAttribute::getObject(const CNormalString& alias)
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(objects != _NULL);
	assert(alias.length() > 0);
#endif

	//Get enumeration.
	OBJECTS_INSTANCE(objects)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check name.
		if(object->getAlias() == alias) return object;
		//Check child objects.
		if(object->getCount() > 0)
		{
			//Do it recursively.
			CWorldObject* childObject =
				//Get world object.
				((CChildAttribute *)object)->getObject(alias);
			//Check result.
			if(childObject != _NULL) return childObject;
		}
	}
	//Return null.
	return (CWorldObject *)_NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetEnumeration
//
/////////////////////////////////////////////////////////////////////////////////

void CChildAttribute::getEnumeration(CListNodeEnumeration& enumeration) const
{
#ifdef _DEBUG
	assert(objects != _NULL);
#endif
	//Get enumeration.
	OBJECTS_INSTANCE(objects)->getEnumeration(&enumeration);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWorldBox
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CChildAttribute::getWorldBox(CSimpleBox& box) const
{
	//Value
	_BOOL flag = _FALSE;
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(objects != _NULL);
#endif

	//Get enumeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check flag.
		if(!flag)
		{
			//Get box.
			if(object->getWorldBox(box)) flag = _TRUE;
		}
		else
		{
			//Box.
			CSimpleBox tempBox;
			//Get box.
			if(object->getWorldBox(tempBox)) box.fuse(&tempBox);
		}
	}
	//Return result.
	return flag;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWorldSphere
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CChildAttribute::getWorldSphere(CSimpleSphere& sphere) const
{
	//Value
	_BOOL flag = _FALSE;
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(objects != _NULL);
#endif

	//Get enumeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check flag.
		if(!flag)
		{
			//Get sphere.
			if(object->getWorldSphere(sphere)) flag = _TRUE;
		}
		else
		{
			//Temp sphere.
			CSimpleSphere tempSphere;
			//Get sphere.
			if(object->getWorldSphere(tempSphere)) sphere.fuse(&tempSphere);
		}
	}
	//Return result.
	return flag;
}
