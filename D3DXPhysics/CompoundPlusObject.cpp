///////////////////////////////////////////////////////////////////////////////
//
// CompoundPlusObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundPlusObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CCompoundPlusObject::base(L"CCompoundPlusObject",L"CCompoundObject");

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundPlusObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundPlusObject::CCompoundPlusObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundPlusObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundPlusObject::~CCompoundPlusObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CCompoundPlusObject::initializeObjects(CResourceApplication* resourceApplication)
{
	//World object.
	CD3DXPrimitiveObject* object;
#ifdef _DEBUG
	assert(resourceApplication != _NULL);
#endif

	//Get resource manager.
	CResourceManager* resourceManager = resourceApplication->getResourceManager();
#ifdef _DEBUG
	assert(resourceManager != NULL);
#endif

	//Add object.
	object = addModel(resourceManager,CPrimitiveAttribute::cuboid0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"ºáÁº£¨",L"£©");
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(1.0f,0.2f,0.2f);

	//Add object.
	object = addModel(resourceManager,CPrimitiveAttribute::cuboid0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"ÊúÁº£¨",L"£©");
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.2f,1.0f,0.2f);

	//Return OK.
	return S_OK;
}
