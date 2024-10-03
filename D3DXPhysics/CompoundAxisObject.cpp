///////////////////////////////////////////////////////////////////////////////
//
// CompoundAxisObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundAxisObject.h"

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
const C4DBase CCompoundAxisObject::base(L"CCompoundAxisObject",L"CCompoundObject");

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundAxisObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundAxisObject::CCompoundAxisObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundAxisObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundAxisObject::~CCompoundAxisObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CCompoundAxisObject::initializeObjects(CResourceApplication* resourceApplication)
{
	//Primitive object.
	CPrimitiveObject* object;
#ifdef _DEBUG
	assert(resourceApplication != _NULL);
#endif

	//Get resource manager.
	CResourceManager* resourceManager = resourceApplication->getResourceManager();
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Add model.
	object = addModel(resourceManager,CPrimitiveAttribute::cone0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"xÖá¼ýÍ·£¨",L"£©");
	//Set mass.
	object->setMass(1.0f);
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.0309f,0.100f,0.0309f);
	//Rotate it.
	object->setEularRotation(0.0f,0.0f,-D3DX_PI / 2.0f);
	//Translate it.
	object->setPosition(1.05f,0.0f,0.0f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f));

	//Add model.
	object = addModel(resourceManager,CPrimitiveAttribute::cylinder0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"xÖá¼ý±ú£¨",L"£©");
	//Set mass.
	object->setMass(1.0f);
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.009505f,1.0f,0.009505f);
	//Rotate it.
	object->setEularRotation(0.0f,0.0f,-D3DX_PI / 2.0f);
	//Translate it.
	object->setPosition(0.5f,0.0f,0.0f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f));

	//Add model.
	object = addModel(resourceManager,CPrimitiveAttribute::cone0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"yÖá¼ýÍ·£¨",L"£©");
	//Set mass.
	object->setMass(1.0f);
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.0309f,0.1f,0.0309f);
	//Rotate it.
	//object->setEularRotate(0.0f,0.0f,-D3DX_PI / 2.0f);
	//Translate it.
	object->setPosition(0.0f,1.05f,0.0f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f));

	//Add model.
	object = addModel(resourceManager,CPrimitiveAttribute::cylinder0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"yÖá¼ý±ú£¨",L"£©");
	//Set mass.
	object->setMass(1.0f);
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.009505f,1.0f,0.009505f);
	//Rotate it.
	//object->SetRotate(0.0f,0.0f,-D3DX_PI / 2.0f);
	//Translate it.
	object->setPosition(0.0f,0.5f,0.0f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f));

	//Add model.
	object = addModel(resourceManager,CPrimitiveAttribute::cone0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"zÖá¼ýÍ·£¨",L"£©");
	//Set mass.
	object->setMass(1.0f);
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.0309f,0.1f,0.0309f);
	//Rotate it.
	object->setEularRotation(D3DX_PI / 2.0f,0.0f,0.0f);
	//Translate it.
	object->setPosition(0.0f,0.0f,1.05f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f));

	//Add model.
	object = addModel(resourceManager,CPrimitiveAttribute::cylinder0Primitive);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set name.
	object->setAlias(L"zÖá¼ý±ú£¨",L"£©");
	//Set mass.
	object->setMass(1.0f);
	//Set movable.
	object->setMovable(_FALSE);
	//Set scalable.
	object->setScalable(_FALSE);
	//Set rotatable.
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.009505f,1.0f,0.009505f);
	//Rotate it.
	object->setEularRotation(D3DX_PI / 2.0f,0.0f,0.0f);
	//Translate it.
	object->setPosition(0.0f,0.0f,0.5f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f));
	//Return OK.
	return S_OK;
}
