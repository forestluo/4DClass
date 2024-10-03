///////////////////////////////////////////////////////////////////////////////
//
// CompoundBoxObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundBoxObject.h"

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
const C4DBase CCompoundBoxObject::base(L"CCompoundBoxObject",L"CCompoundObject");

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundBoxObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundBoxObject::CCompoundBoxObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundBoxObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundBoxObject::~CCompoundBoxObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CCompoundBoxObject::initializeObjects(CResourceApplication* resourceApplication)
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
	object = addModel(resourceManager,CPrimitiveAttribute::floor0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"底面（",L"）");
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Set position.
	object->setPosition(0.0f,-0.5f,0.0f);

	//Add object.
	object = addModel(resourceManager,CPrimitiveAttribute::floor0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"左侧面（",L"）");
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Set rotation.
	object->setEularRotation(0.0f,0.0f,D3DX_PI / 2.0f);
	//Set position.
	object->setPosition(-0.5f,0.0f,0.0f);

	//Add object.
	object = addModel(resourceManager,CPrimitiveAttribute::floor0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"右侧面（",L"）");
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Set rotation.
	object->setEularRotation(0.0f,0.0f,D3DX_PI / 2.0f);
	//Set position.
	object->setPosition(+0.5f,0.0f,0.0f);

	//Add object.
	object = addModel(resourceManager,CPrimitiveAttribute::floor0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"后立面（",L"）");
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Set rotation.
	object->setEularRotation(D3DX_PI / 2.0f,0.0f,0.0f);
	//Set position.
	object->setPosition(0.0f,0.0f,+0.5f);

	//Add object.
	object = addModel(resourceManager,CPrimitiveAttribute::floor0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"前立面（",L"）");
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Set rotation.
	object->setEularRotation(D3DX_PI / 2.0f,0.0f,0.0f);
	//Set position.
	object->setPosition(0.0f,0.0f,-0.5f);

	//Return OK.
	return S_OK;
}
