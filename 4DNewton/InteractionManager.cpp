///////////////////////////////////////////////////////////////////////////////
//
// InteractionManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "InteractionManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NewtonPhysics.h"
#include "InteractionItem.h"
#include "HashListContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define DEFAULT_MODE										1
#define MAX_FRICTION_ANGULAR_GRAVITY						250.0f
#define MAX_FRICTION_LINEAR_ACCELERATION					1000.0f
#define WORLD_INSTANCE(p)									((const NewtonWorld *)(p))
#define ITEMS_INSTANCE(p)									((CHashListContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CInteractionManager
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CInteractionManager::CInteractionManager(void)
{
	//Create items.
	items = new CHashListContainer();
#ifdef _DEBUG
	assert(items != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CInteractionManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CInteractionManager::~CInteractionManager(void)
{
	//Release all.
	releaseAll();
	//Check items.
	if(items != _NULL)
	{
		//Delete items.
		delete (CHashListContainer *)items;
		//Clear items.
		items = (CHashListContainer *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
///////////////////////////////////////////////////////////////////////////////

void CInteractionManager::releaseAll()
{
	//Get enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(items != _NULL);
#endif

	//Get enumeration.
	ITEMS_INSTANCE(items)->getEnumeration(&iterator);
	//Do while
	while(iterator.hasMoreElements())
	{
		//Get element.
		_OBJECT value = iterator.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Clear controller.
		((CInteractionItem *)value)->clearController();
		//Delete entity.
		delete (CInteractionItem *)value;
	}
	//Clear all.
	ITEMS_INSTANCE(items)->clearAll();
}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearControllers
//
/////////////////////////////////////////////////////////////////////////////////

void CInteractionManager::clearControllers()
{
	//Release all.
	releaseAll();
}

/////////////////////////////////////////////////////////////////////////////////
//
// IsControlled
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CInteractionManager::isControlled(_OBJECT body) const
{
#ifdef _DEBUG
	assert(items != _NULL);
#endif
	//Return result.
	return ITEMS_INSTANCE(items)->exists((_LONG)body);
}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearController
//
/////////////////////////////////////////////////////////////////////////////////

void CInteractionManager::clearController(_OBJECT body)
{
#ifdef _DEBUG
	assert(items != _NULL);
#endif
	//Get item.
	CInteractionItem* item = (CInteractionItem *)ITEMS_INSTANCE(items)->removeValue((_LONG)body);
	//Check result.
	if(item != _NULL)
	{
		//Clear controller.
		item->clearController();
		//Delete controller.
		delete (CInteractionItem *)item;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// PickBody
//
/////////////////////////////////////////////////////////////////////////////////

void CInteractionManager::pickBody(_OBJECT body,const C4DVector3& point)
{
#ifdef _DEBUG
	assert(items != _NULL);
#endif
	//Get item.
	CInteractionItem* item = (CInteractionItem *)ITEMS_INSTANCE(items)->getValue((_LONG)body);
	//Check item.
	if(item == _NULL)
	{
		//Create item.
		item = new CInteractionItem();
#ifdef _DEBUG
		assert(item != _NULL);
#endif
		//Add item into list.
		ITEMS_INSTANCE(items)->setValue((_LONG)body,item);
	}
	//Pick body.
	item->pickBody(body,point);
}

/////////////////////////////////////////////////////////////////////////////////
//
// MoveBody
//
/////////////////////////////////////////////////////////////////////////////////

void CInteractionManager::moveBody(_OBJECT body,const C4DVector3& direction)
{
#ifdef _DEBUG
	assert(items != _NULL);
#endif
	//Get item.
	CInteractionItem* item = (CInteractionItem *)ITEMS_INSTANCE(items)->getValue((_LONG)body);
	//Check item.
	if(item != _NULL) item->moveBody(body,direction);
}
