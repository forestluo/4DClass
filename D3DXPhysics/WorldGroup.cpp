///////////////////////////////////////////////////////////////////////////////
//
// WorldGroup.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldGroup.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "ListNodeContainer.h"
#include "D3DXRenderableObject.h"

#include "JointObject.h"
#include "CompoundObject.h"
#include "PrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
/////////////////////////////////////////////////////////////////////////////////

#define OBJECTS_INSTANCE(p)									((CListNodeContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CWorldGroup
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CWorldGroup::CWorldGroup(void)
{
	//Create objects.
	objects = new CListNodeContainer();
#ifdef _DEBUG
	assert(objects != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CWorldGroup
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CWorldGroup::~CWorldGroup(void)
{
	//Release all objects.
	releaseAll();
	//Check objects.
	if(objects != _NULL)
	{
		//Delete objects.
		delete (CListNodeContainer *)objects;
		//Clear objects.
		objects = (CListNodeContainer *)_NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
/////////////////////////////////////////////////////////////////////////////////

void CWorldGroup::releaseAll()
{
#ifdef _DEBUG
	assert(objects != _NULL);
#endif

	//Do while.
	while(OBJECTS_INSTANCE(objects)->getCount() > 0)
	{
		//Remove object.
		CWorldObject* object = (CWorldObject *)OBJECTS_INSTANCE(objects)->removeHead();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Get this.
		_OBJECT thisObject = object->getThis();
#ifdef _DEBUG
		assert(thisObject != _NULL);
#endif
		//Check object.
		if(object->isRenderableObject()
			&& object->isPhysicsObject())
		{
			//Check type.
			if(object->isJointObject())
			{
				//Delete joint object.
				delete (CJointObject *)thisObject;
			}
			else if(object->isCompoundObject())
			{
				//Delete compound object.
				delete (CCompoundObject *)thisObject;
			}
			else if(object->isPrimitiveObject())
			{
				//Delete primitive object.
				delete (CPrimitiveObject *)thisObject;
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
		}
		else if(object->isRenderableObject())
		{
			//Check type.
			if(object->isJointObject())
			{
				//Delete joint object.
				delete (CD3DXJointObject *)thisObject;
			}
			else if(object->isCompoundObject())
			{
				//Delete compound object.
				delete (CD3DXCompoundObject *)thisObject;
			}
			else if(object->isPrimitiveObject())
			{
				//Delete primitive object.
				delete (CD3DXPrimitiveObject *)thisObject;
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
		}
		else if(object->isPhysicsObject())
		{
			//Check type.
			if(object->isJointObject())
			{
				//Delete joint object.
				delete (CPhysicsJointObject *)thisObject;
			}
			else if(object->isCompoundObject())
			{
				//Delete compound object.
				delete (CPhysicsCompoundObject *)thisObject;
			}
			else if(object->isPrimitiveObject())
			{
				//Delete primitive object.
				delete (CPhysicsPrimitiveObject *)thisObject;
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
		}
#ifdef _DEBUG
		else assert(_FALSE);
#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddObject
//
/////////////////////////////////////////////////////////////////////////////////

void CWorldGroup::addObject(CWorldObject* object)
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

void CWorldGroup::removeObject(CWorldObject* object)
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

_BOOL CWorldGroup::objectExists(CWorldObject* object) const
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
		//Check result.
		if(thisObject == object) return _TRUE;
		//Check result.
		if(thisObject->getCount() > 0)
		{
			//Check children.
			if(thisObject->objectExists(object)) return _TRUE;
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

CWorldObject* CWorldGroup::getObject(const CNormalString& alias)
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
		//Check result.
		if(object->getCount() > 0)
		{
			//Get child object.
			CWorldObject* childObject
				= object->getObject(alias);
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

void CWorldGroup::getEnumeration(CListNodeEnumeration& enumeration) const
{
#ifdef _DEBUG
	assert(objects != _NULL);
#endif
	//Get enumeration.
	OBJECTS_INSTANCE(objects)->getEnumeration(&enumeration);
}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearTexture
//
/////////////////////////////////////////////////////////////////////////////////

void CWorldGroup::clearTexture(const CNormalString& name)
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
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check result.
		if(object->isRenderableObject())
		{
			//Get renderable object.
			CD3DXRenderableObject* renderableObject =
				(CD3DXRenderableObject *)object->getRenderable();
#ifdef _DEBUG
			assert(renderableObject != _NULL);
#endif
			//Clear texture.
			renderableObject->clearTexture(name);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CWorldGroup::setViewPort(CViewPort* viewPort)
{
	//Result.
	HRESULT hr = S_OK;
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(objects != _NULL);
	assert(viewPort != _NULL);
#endif

	//Get enumeration.
	OBJECTS_INSTANCE(objects)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != NULL);
#endif
		//Check result.
		if(object->isRenderableObject())
		{
			//Get renderable object.
			CD3DXRenderableObject* renderableObject = 
				(CD3DXRenderableObject *)object->getRenderable();
#ifdef _DEBUG
			assert(renderableObject != _NULL);
#endif
			//Set view port.
			if(FAILED(renderableObject->setViewPort(viewPort))) hr = E_FAIL;
		}
	}
	//Return result.
	return hr;
}

/////////////////////////////////////////////////////////////////////////////////
//
// DispatchMessage
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CWorldGroup::dispatchMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;
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
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check result.
		if(object->isRenderableObject())
		{
			//Get renderable object.
			CD3DXRenderableObject* renderableObject = 
				(CD3DXRenderableObject *)object->getRenderable();
#ifdef _DEBUG
			assert(renderableObject != _NULL);
#endif
			//Set view port.
			if(FAILED(renderableObject->handleMessage(d3dxEvent))) hr = E_FAIL;
		}
	}
	//Return result.
	return hr;
}
