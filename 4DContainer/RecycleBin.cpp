///////////////////////////////////////////////////////////////////////////////
//
// RecycleBin.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "RecycleBin.h"
#include "ListQueueContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define NEW_COUNT											0
#define RELEASED_COUNT										1
#define RECYCLED_COUNT										2
#define REUSED_COUNT										3

#define INSTANCE(c)											((CListQueueContainer *)(c))

///////////////////////////////////////////////////////////////////////////////
//
// CRecycleBin
//
///////////////////////////////////////////////////////////////////////////////

CRecycleBin::CRecycleBin(void)
{
	//Create list queue container.
	container = new CListQueueContainer();
#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Do while.
	for(_INTEGER i = 0;i < 4;i ++) counters[i] = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// CRecycleBin
//
///////////////////////////////////////////////////////////////////////////////

CRecycleBin::CRecycleBin(_INTEGER capacity)
{
	//Create list queue container.
	container = new CListQueueContainer(capacity);
#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Do while.
	for(_INTEGER i = 0;i < 4;i ++) counters[i] = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CRecycleBin
//
///////////////////////////////////////////////////////////////////////////////

CRecycleBin::~CRecycleBin(void)
{
	//Open lock.
	openLock();
	//Check result.
	if(container != _NULL)
	{
		//Delete instance.
		delete INSTANCE(container);
		//Clear container.
		container = (CListQueueContainer *)_NULL;
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCounter
//
///////////////////////////////////////////////////////////////////////////////

_LONG CRecycleBin::getCounter(_INTEGER countKind)
{
	//Result.
	_LONG value;
	//Synchronized.
	openLock();
	{
		//Get result.
		value = counters[countKind];
	}
	//Clear synchronized.
	closeLock();
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// IncreaseCounter
//
///////////////////////////////////////////////////////////////////////////////

void CRecycleBin::increaseCounter(_INTEGER countKind)
{
	//Synchronized.
	openLock();
	{
		//Add counter.
		counters[countKind] ++;
	}
	//Clear synchronized.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAll
//
///////////////////////////////////////////////////////////////////////////////

void CRecycleBin::clearAll()
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif

	//Synchronized.
	openLock();
	{
		//Clear all.
		//Remove head.
		_OBJECT value;
		//Convert to its class and delete value.
		while((value = INSTANCE(container)->removeHead()) != _NULL) deleteObject(value);

		//Delete all objects in the container.
		INSTANCE(container)->clearAll();
		//Clear counters.
		counters[0] = counters[1] = counters[2] = counters[3] = 0;
	}
	//Clear synchronized.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSize
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CRecycleBin::getSize()
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif

	//Value.
	_INTEGER value;
	//Synchronized.
	openLock();
	{
		//Get size.
		value = INSTANCE(container)->getSize();
	}
	//Clear synchronized.
	closeLock();
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CRecycleBin::getCount()
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif

	//Value.
	_INTEGER value;
	//Synchronized.
	openLock();
	{
		//Get count.
		value = INSTANCE(container)->getCount();
	}
	//Clear synchronized.
	closeLock();
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCapacity
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CRecycleBin::getCapacity()
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif

	//Value.
	_INTEGER value;
	//Synchronized.
	openLock();
	{
		//Return capacity.
		value = INSTANCE(container)->getCapacity();
	}
	//Clear synchronized.
	closeLock();
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetCapacity
//
///////////////////////////////////////////////////////////////////////////////

void CRecycleBin::setCapacity(_INTEGER capacity)
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif

	//Synchronized.
	openLock();
	{
		//Set capacity.
		INSTANCE(container)->setCapacity(capacity);
	}
	//Clear synchronized.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// Create
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CRecycleBin::create()
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif

	//Object.
	_OBJECT object;
	//Synchronized.
	openLock();
	{
		//Check empty.
		if(INSTANCE(container)->isEmpty())
		{
			//Increase new count.
			increaseCounter(NEW_COUNT);
			//Create new object.
			object = newObject();
		}
		else
		{
			//Increase reused count.
			increaseCounter(REUSED_COUNT);
			//Return result.
			object = INSTANCE(container)->removeHead();
		}
	}
	//Clear synchronized.
	closeLock();
	//Return result.
	return object;
}

///////////////////////////////////////////////////////////////////////////////
//
// Recycle
//
///////////////////////////////////////////////////////////////////////////////

void CRecycleBin::recycle(_OBJECT object)
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif

	//Synchronized.
	openLock();
	{
		//Keep only a reasonable count in the memory.
		if(INSTANCE(container)->isFull())
		{
			//Increase released count.
			increaseCounter(RELEASED_COUNT);
		}
		else
		{
			//Add object to tail.
			INSTANCE(container)->addTail(object);
			//Increase recycled count.
			increaseCounter(RECYCLED_COUNT);
		}
	}
	//Clear synchronized.
	closeLock();
}
