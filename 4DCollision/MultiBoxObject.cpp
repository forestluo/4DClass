///////////////////////////////////////////////////////////////////////////////
//
// MultiBoxObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "MultiBoxObject.h"
#include "MultiBoxObjectRecycleBin.h"

///////////////////////////////////////////////////////////////////////////////
//
// Include
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
using std::vector;

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

//Box Object Vector
typedef vector<CBoxObject*>									CBoxObjectVector;
//Instance
#define INSTANCE(p)											(*((CBoxObjectVector *)(p)))

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

#pragma init_seg(".CRT$XCF")
//Recycle bin.
static CMultiBoxObjectRecycleBin multiBoxObjectBin;

///////////////////////////////////////////////////////////////////////////////
//
// CMultiBoxObject
//
///////////////////////////////////////////////////////////////////////////////

CMultiBoxObject::CMultiBoxObject(void)
{
	//Create vector.
	objects = new CBoxObjectVector();
#ifdef _DEBUG
	assert(objects != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CMultiBoxObject
//
///////////////////////////////////////////////////////////////////////////////

CMultiBoxObject::~CMultiBoxObject(void)
{
	//Check result.
	if(objects != _NULL)
	{
		//Do while.
		for(_UINT32 i = 0;i < INSTANCE(objects).size();i ++)
		{
#ifdef _DEBUG
			assert(INSTANCE(objects)[i] != _NULL);
#endif
			//Call it recursively.
			INSTANCE(objects)[i]->clearAll();INSTANCE(objects)[i]->recycle();
		}
		//Clear objects.
		INSTANCE(objects).clear();
		//Delete objects.
		delete (CBoxObjectVector *)objects;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// IsSingle
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CMultiBoxObject::isSingle()
{
	//Return result.
	return _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAll
//
///////////////////////////////////////////////////////////////////////////////

void CMultiBoxObject::clearAll()
{
	//Call clear all.
	CBoxObject::clearAll();

#ifdef _DEBUG
	assert(objects != _NULL);
#endif
	//Do while.
	for(_UINT32 i = 0;i < INSTANCE(objects).size();i ++)
	{
#ifdef _DEBUG
		assert(INSTANCE(objects)[i] != _NULL);
#endif
		//Call it recursively.
		INSTANCE(objects)[i]->clearAll();INSTANCE(objects)[i]->recycle();
	}
	//Clear objects.
	INSTANCE(objects).clear();
}

///////////////////////////////////////////////////////////////////////////////
//
// AddObject
//
///////////////////////////////////////////////////////////////////////////////

void CMultiBoxObject::addObject(CBoxObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(objects != _NULL);
#endif
	//Add object.
	INSTANCE(objects).push_back(object);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CMultiBoxObject::getCount()
{
#ifdef _DEBUG
	assert(objects != _NULL);
#endif
	//Return result.
	return INSTANCE(objects).size();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetObject
//
///////////////////////////////////////////////////////////////////////////////

CBoxObject* CMultiBoxObject::getObject(_INTEGER index)
{
#ifdef _DEBUG
	assert(objects != _NULL);
	assert(index >= 0 && (_UINT32)index < INSTANCE(objects).size());
#endif
	//Return result.
	return INSTANCE(objects)[index];
}

///////////////////////////////////////////////////////////////////////////////
//
// GetTotalCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CMultiBoxObject::getTotalCount()
{
#ifdef _DEBUG
	assert(objects != _NULL);
#endif
	//Count.
	_INTEGER count = INSTANCE(objects).size();
	//Do while.
	for(_UINT32 i = 0;i < INSTANCE(objects).size();i ++)
	{
#ifdef _DEBUG
		assert(INSTANCE(objects)[i] != _NULL);
#endif
		//Call it recursively.
		count += INSTANCE(objects)[i]->getTotalCount();
	}
	//Return result.
	return count;
}

///////////////////////////////////////////////////////////////////////////////
//
// Recycle
//
///////////////////////////////////////////////////////////////////////////////

void CMultiBoxObject::recycle()
{
	//Clear all.
	clearAll();
	//Recycle object.
	multiBoxObjectBin.recycle(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// Create
//
///////////////////////////////////////////////////////////////////////////////

CMultiBoxObject* CMultiBoxObject::create()
{
	//Return result.
	return (CMultiBoxObject *)multiBoxObjectBin.create();
}
