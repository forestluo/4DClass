///////////////////////////////////////////////////////////////////////////////
//
// PickedAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PickedAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "D3DXCompoundObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPickedAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPickedAttribute::CPickedAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CPickedAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPickedAttribute::~CPickedAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// ClearPicked
//
///////////////////////////////////////////////////////////////////////////////

void CPickedAttribute::clearPicked()
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
		assert(object != NULL);
#endif
		//Check renderable.
		if(object->isRenderableObject())
		{
			//Clear picked.
			((CD3DXRenderableObject *)object->getRenderable())->setPicked(_FALSE);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPicked
//
///////////////////////////////////////////////////////////////////////////////

void CPickedAttribute::setPicked(const CNormalString& alias)
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
		//Check renderable.
		if(object->isRenderableObject())
		{
			//Get renderable object.
			CD3DXRenderableObject* renderableObject =
				(CD3DXRenderableObject *)object->getRenderable();
#ifdef _DEBUG
			assert(renderableObject != _NULL);
#endif
			//Check base.
			if(object->isPrimitiveObject())
			{
				//Set status.
				renderableObject->setPicked(object->getAlias() == alias);
			}
			else if(object->isCompoundObject())
			{
				//Set picked.
				renderableObject->setPicked(_FALSE);
				//Get object.
				CWorldObject* childObject =	object->getObject(alias);
				//Check result.
				if(childObject != _NULL && childObject->isRenderableObject())
				{
					//Set picked.
					renderableObject->setPicked(_TRUE);
					//Set picked.
					((CD3DXRenderableObject *)childObject->getRenderable())->setPicked(_TRUE);
				}
				else
				{
					//Check itself.
					if(renderableObject->getAlias() == alias) renderableObject->setPicked(_TRUE);
				}
			}
			else if(object->isJointObject())
			{
				//Set picked.
				renderableObject->setPicked(_FALSE);
				//Get object.
				CWorldObject* childObject =	object->getObject(alias);
				//Check result.
				if(childObject != _NULL && childObject->isRenderableObject())
				{
					//Set picked.
					renderableObject->setPicked(_TRUE);
					//Set picked.
					((CD3DXRenderableObject *)childObject->getRenderable())->setPicked(_TRUE);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPickedObject
//
/////////////////////////////////////////////////////////////////////////////////

CWorldObject* CPickedAttribute::getPickedObject()
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
		//Check renderable.
		if(object->isRenderableObject())
		{
			//Check picked.
			if(((CD3DXRenderableObject *)object->getRenderable())->isPicked()) return object;
		}
	}
	//Return null.
	return (CWorldObject *)_NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// PickObject
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CPickedAttribute::pickObject(CPickRay& pickRay,CPickResult& result)
{
	//Flag.
	_BOOL flag = _FALSE;
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
		//Check renderable.
		if(object->isRenderableObject())
		{
			//Check picked.
			if(((CD3DXRenderableObject *)object->getRenderable())->pick(pickRay,result)) flag = _TRUE;
		}
	}

	//Set origin.
	result.setPickOrigin(pickRay.getPickOrigin());
	//Set direction.
	result.setPickDirection(pickRay.getPickDirection());
	//Return result.
	return flag;
}
