///////////////////////////////////////////////////////////////////////////////
//
// 4DBaseMap.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DBaseMap.h"
#include "HashTreeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define INSTANCE(p)											((CHashTreeContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// C4DBaseMap
//
///////////////////////////////////////////////////////////////////////////////

C4DBaseMap::C4DBaseMap()
{
	//Create container.
	container = new CHashTreeContainer();
#ifdef _DEBUG
	assert(container != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// ~C4DBaseMap
//
///////////////////////////////////////////////////////////////////////////////

C4DBaseMap::~C4DBaseMap()
{
	//Open lock.
	openLock();
	//Check container.
	if(container != _NULL)
	{
		//Delete container.
		delete (CHashTreeContainer *)container;
		//Clear container.
		container = (CHashTreeContainer *)_NULL;
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// AddBase
//
///////////////////////////////////////////////////////////////////////////////
	
void C4DBaseMap::addBase(C4DBase* base)
{
#ifdef _DEBUG
	assert(base != _NULL);
	assert(container != _NULL);
#endif
	//Open.
	openLock();
	{
#ifndef _DEBUG
		//Set value.
		INSTANCE(container)->setValue(base->classCode(),(_OBJECT)base);
#else
		//Set value.
		assert(INSTANCE(container)->setValue(base->classCode(),(_OBJECT)base) == _NULL);
#endif
	}
	//Close.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// Exists
//
///////////////////////////////////////////////////////////////////////////////
	
_BOOL C4DBaseMap::exists(_LONG thisClass)
{
	//Value.
	_BOOL value;

#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Open.
	openLock();
	{
		//Set value.
		value = INSTANCE(container)->exists(thisClass);
	}
	//Close.
	closeLock();
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsBaseOf
//
///////////////////////////////////////////////////////////////////////////////

_BOOL C4DBaseMap::isBaseOf(_LONG thisClass,_LONG superClass)
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Check class code.
	if(thisClass == superClass) return _TRUE;

	//Value.
	_BOOL result = _FALSE;
	//Open.
	openLock();
	{
		do
		{
			//Get value.
			C4DBase* base = (C4DBase *)INSTANCE(container)->getValue(thisClass);
			//Check result.
			if(base == _NULL) break;
			//Check result.
			if(base->superCode() == superClass) {result = _TRUE;break;}
			//Set this class.
			thisClass = base->superCode();

		}while(_TRUE);
	}
	//Close.
	closeLock();
	//Return result.
	return result;
}
