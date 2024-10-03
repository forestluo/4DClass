///////////////////////////////////////////////////////////////////////////////
//
// D3DXJointObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "D3DXJointObject.h"
#include "D3DXPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Defination.
//
///////////////////////////////////////////////////////////////////////////////

#define CYLINDER_RADIUS											0.009505f
#define DEFAULT_RAW_DIRECTION									C4DVector3(0.0f,+1.0f,0.0f)
#define DEFAULT_CHILD_POSITION									C4DVector3(0.0f,-0.1f,0.0f)
#define DEFAULT_PARENT_POSITION									C4DVector3(0.0f,+0.1f,0.0f)
#define GREEN_LIGHT_COLOR										D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f)
#define YELLOW_LIGHT_COLOR										D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CreateJointParentObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObject::createJointParentObjects(CResourceManager* resourceManager)
{
	//World object.
	CD3DXPrimitiveObject* object;

#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Add subobject.
	object = new CD3DXPrimitiveObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Add object.
	addObject(object);
	//Select renderable.
	object->selectRenderable(resourceManager,PRIMITIVE_CYLINDER0);
	//Set name.
	object->setAlias(L"父物体链接杆（",L"）");
	//Set color.
	object->setLightColor(YELLOW_LIGHT_COLOR);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(CYLINDER_RADIUS,0.20f,CYLINDER_RADIUS);

	//Add subobject.
	parentHandle = new CD3DXPrimitiveObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Add object.
	addObject(parentHandle);
	//Select renderable.
	parentHandle->selectRenderable(resourceManager,PRIMITIVE_SPHERE0);
	//Set name.
	parentHandle->setAlias(L"父物体链接柄（",L"）");
	//Set color.
	parentHandle->setLightColor(YELLOW_LIGHT_COLOR);
	//Set action.
	parentHandle->setMovable(_TRUE);
	parentHandle->setScalable(_FALSE);
	parentHandle->setRotatable(_FALSE);
	//Scale it.
	parentHandle->setScale(0.03f,0.03f,0.03f);
	//Set position.
	parentHandle->setPosition(DEFAULT_PARENT_POSITION);

	//Return ok.
	return S_OK;
}
