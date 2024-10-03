///////////////////////////////////////////////////////////////////////////////
//
// NormalStringList.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "NormalStringList.h"
#include "ListNodeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define INSTANCE(p)											((CListNodeContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CNormalStringList
//
///////////////////////////////////////////////////////////////////////////////

CNormalStringList::CNormalStringList(void)
{
	//Set default value.
	container = new CListNodeContainer();
#ifdef _DEBUG
	assert(container != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CNormalStringList
//
///////////////////////////////////////////////////////////////////////////////

CNormalStringList::~CNormalStringList(void)
{
	//Check result.
	if(container != _NULL)
	{
		//Clear all.
		clearAll();

		//Delete instance.
		delete INSTANCE(container);
		//Clear container.
		container = (CListNodeContainer *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAll
//
///////////////////////////////////////////////////////////////////////////////

void CNormalStringList::clearAll()
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Remove head.
	_OBJECT value;
	//Convert to its class and delete value.
	while((value = INSTANCE(container)->removeHead()) != _NULL) delete (CNormalString *)value;
	//Delete all objects in the container.
	INSTANCE(container)->clearAll();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CNormalStringList::getCount() const
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Return result.
	return INSTANCE(container)->getCount();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetString
//
///////////////////////////////////////////////////////////////////////////////

CNormalString& CNormalStringList::getString(_INTEGER index)
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Get string.
	CNormalString* string = (CNormalString *)INSTANCE(container)->getIndexed(index);
#ifdef _DEBUG
	assert(string != _NULL);
#endif
	//Return result.
	return *string;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetString
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CNormalStringList::getString(_INTEGER index) const
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Get string.
	CNormalString* string = (CNormalString *)INSTANCE(container)->getIndexed(index);
#ifdef _DEBUG
	assert(string != _NULL);
#endif
	//Return result.
	return *string;
}

///////////////////////////////////////////////////////////////////////////////
//
// AddString
//
///////////////////////////////////////////////////////////////////////////////

void CNormalStringList::addString(const CNormalString& string)
{
#ifdef _DEBUG
	assert(container != _NULL);
#endif
	//Create string.
	CNormalString* newString = new CNormalString(string);
#ifdef _DEBUG
	assert(newString != _NULL);
#endif
	//Add it into tail.
	INSTANCE(container)->addTail(newString);
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveString
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CNormalStringList::removeString(const CNormalString& string)
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(container != _NULL);
#endif

	//Get enumeration.
	INSTANCE(container)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CNormalString* currentString = (CNormalString *)iterator.nextElement();
#ifdef _DEBUG
		assert(currentString != _NULL);
#endif
		//Check result.
		if(string.equals(currentString))
		{
			//Remove it from list.
			INSTANCE(container)->removeValue(currentString);return _TRUE;
		}
	}
	//Return false.
	return _FALSE;
}
