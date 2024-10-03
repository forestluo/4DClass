///////////////////////////////////////////////////////////////////////////////
//
// CompoundModelManager.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundModelManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundBoxObject.h"
#include "CompoundPlusObject.h"
#include "CompoundAxisObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundModelManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CCompoundModelManager::CCompoundModelManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundModelManager
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CCompoundModelManager::~CCompoundModelManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// AddCompound
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CCompoundModelManager::addCompound(CResourceApplication* resourceApplication,
											CCompoundObject* object)
{
#ifdef _DEBUG
	assert(resourceApplication != _NULL && object != _NULL);
#endif
	//Create objects.
	if(!object->createObjects(resourceApplication)) return _FALSE;
	//Add it into world group.
	CWorldGroup::addObject(object);
	//Return result.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCompound
//
///////////////////////////////////////////////////////////////////////////////

CCompoundObject* CCompoundModelManager::createCompound(CResourceApplication* resourceApplication,
														_LONG classCode,_FLOAT mass,
														const C4DVector3& scaling,
														const C4DVector3& rotation,
														const C4DVector3& position)
{
	//Compound object.
	CCompoundObject* object;

#ifdef _DEBUG
	assert(mass >= 0.0f);
	assert(resourceApplication != _NULL);
#endif

	//Check class code.
	if(classCode == CCompoundBoxObject::getClassCode())
	{
		//Create object.
		object = new CCompoundBoxObject();
	}
	else if(classCode == CCompoundAxisObject::getClassCode())
	{
		//Create object.
		object = new CCompoundAxisObject();
	}
	else if(classCode == CCompoundPlusObject::getClassCode())
	{
		//Create object.
		object = new CCompoundPlusObject();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Set mass.
	object->setMass(mass);
	//Set scaling.
	object->setScale(scaling);
	//Set rotation.
	object->setRotation(rotation);
	//Set position.
	object->setPosition(position);

	//Check class code.
	if(classCode == CCompoundBoxObject::getClassCode())
	{
		//Set name.
		object->setAlias(L"¿ÕÏäÌå£¨",L"£©");
	}
	else if(classCode == CCompoundAxisObject::getClassCode())
	{
		//Set name.
		object->setAlias(L"×ø±ê¼Ü£¨",L"£©");
	}
	else if(classCode == CCompoundPlusObject::getClassCode())
	{
		//Set name.
		object->setAlias(L"Ê®×Ö¼Ü£¨",L"£©");
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

	///////////////////////////////////////
	//
	//Create objects.
	if(!object->createObjects(resourceApplication))
	{
		//Delete object.
		delete object;
		//Return null.
		return (CCompoundObject *)_NULL;
	}
	//
	///////////////////////////////////////
	//Add it into world group.
	CWorldGroup::addObject(object);
	//Return result.
	return object;
}
