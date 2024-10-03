///////////////////////////////////////////////////////////////////////////////
//
// CollisionAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CollisionAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "CollisionMethod.h"
#include "ListNodeContainer.h"
#include "D3DXRenderableObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CCollisionAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCollisionAttribute::CCollisionAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCollisionAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCollisionAttribute::~CCollisionAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// ClearCollision
//
///////////////////////////////////////////////////////////////////////////////

void CCollisionAttribute::clearCollision()
{
	//Enumeration.
	CListNodeEnumeration iterator;
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
		//Check result.
		if(object->isRenderableObject())
		{
			//Clear status.
			((CD3DXRenderableObject *)object->getRenderable())->setCollision(_FALSE);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// UpdateCollision
//
///////////////////////////////////////////////////////////////////////////////

void CCollisionAttribute::updateCollision(CWorldObject* object)
{
	//Boxes.
	CListNodeContainer boxes;
	//Collision.
	CCollisionMethod collision;
	//Itself
	CBoxObject* itself = (CBoxObject *)_NULL;

#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Enumeration.
	CListNodeEnumeration iterator1;
	//Get enumeration.
	getEnumeration(iterator1);
	//Do while.
	while(iterator1.hasMoreElements())
	{
		//Get object.
		CWorldObject* worldObject = (CWorldObject *)iterator1.nextElement();
#ifdef _DEBUG
		assert(worldObject != _NULL);
#endif
		//Get box object.
		CBoxObject* box = CBoxObject::getBoxObject(worldObject);
#ifdef _DEBUG
		assert(box != _NULL);
#endif
		//Add it into list.
		boxes.addTail(box);
		//Check world object.
		if(worldObject->getCount() == 0)
		{
			//Check object.
			if(worldObject == object) itself = box;
		}
		else if(worldObject->getCount() > 0)
		{
			//Get top object.
			if(CWorldObject::getTopParent(object) == worldObject) itself = box;
		}
	}
#ifdef _DEBUG
	assert(itself != NULL);
#endif

	//Reset.
	iterator1.reset();
	//Clear collision status.
	clearCollision();

	//Enumeration.
	CListNodeEnumeration iterator2;
	//Get enumeration.
	boxes.getEnumeration(&iterator2);
	//Do while.
	while(iterator1.hasMoreElements() && iterator2.hasMoreElements())
	{
		//Get box object.
		CBoxObject* box = (CBoxObject *)iterator2.nextElement();
#ifdef _DEBUG
		assert(box != _NULL);
#endif
		//Get world object.
		CWorldObject* object = (CWorldObject *)iterator1.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check boxes.
		if(box != itself)
		{
			//Check collision.
			_INTEGER result = collision.collision3(itself,box);
			//Check result.
			if(result == CCollisionMethod::intersect)
			{
				//Check renderable.
				if(object->isRenderableObject())
				{
					//Set collision.
					((CD3DXRenderableObject *)object->getRenderable())->setCollision(_TRUE);
				}
			}
		}
	}
	//Reset.
	iterator2.reset();
	//Do while.
	while(iterator2.hasMoreElements())
	{
		//Get box object.
		CBoxObject* box = (CBoxObject *)iterator2.nextElement();
#ifdef _DEBUG
		assert(box != _NULL);
#endif
		//Delete box object.
		box->recycle();
	}
}
