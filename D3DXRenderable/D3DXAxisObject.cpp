///////////////////////////////////////////////////////////////////////////////
//
// D3DXAxisObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXAxisObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXAxisObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXAxisObject::CD3DXAxisObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXAxisObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXAxisObject::~CD3DXAxisObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXAxisObject::initializeObjects(CResourceApplication* resourceApplication)
{
	//World object.
	CD3DXPrimitiveObject* object;
#ifdef _DEBUG
	assert(resourceApplication != _NULL);
#endif

	//Get resource manager.
	CResourceManager* resourceManager = resourceApplication->getResourceManager();
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Add object.
	object = addObject(resourceManager,PRIMITIVE_CONE0);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Scale it.
	object->setScale(0.0309f,0.100f,0.0309f);
	//Rotate it.
	object->setEularRotation(0.0f,0.0f,-D3DX_PI / 2.0f);
	//Translate it.
	object->setPosition(1.05f,0.0f,0.0f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f));

	//Add subobject.
	object = addObject(resourceManager,PRIMITIVE_CYLINDER0);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Scale it.
	object->setScale(0.009505f,1.0f,0.009505f);
	//Rotate it.
	object->setEularRotation(0.0f,0.0f,-D3DX_PI / 2.0f);
	//Translate it.
	object->setPosition(0.5f,0.0f,0.0f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f));

	//Add object.
	object = addObject(resourceManager,PRIMITIVE_CONE0);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Scale it.
	object->setScale(0.0309f,0.1f,0.0309f);
	//Rotate it.
	//object->setEularRotate(0.0f,0.0f,-D3DX_PI / 2.0f);
	//Translate it.
	object->setPosition(0.0f,1.05f,0.0f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f));

	//Add object.
	object = addObject(resourceManager,PRIMITIVE_CYLINDER0);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Scale it.
	object->setScale(0.009505f,1.0f,0.009505f);
	//Rotate it.
	//object->SetRotate(0.0f,0.0f,-D3DX_PI / 2.0f);
	//Translate it.
	object->setPosition(0.0f,0.5f,0.0f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f));

	//Add object.
	object = addObject(resourceManager,PRIMITIVE_CONE0);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Scale it.
	object->setScale(0.0309f,0.1f,0.0309f);
	//Rotate it.
	object->setEularRotation(D3DX_PI / 2.0f,0.0f,0.0f);
	//Translate it.
	object->setPosition(0.0f,0.0f,1.05f);
	//Set light color.
	object->setLightColor(D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f));

	//Add object.
	object = addObject(resourceManager,PRIMITIVE_CYLINDER0);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
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
