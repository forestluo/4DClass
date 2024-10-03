///////////////////////////////////////////////////////////////////////////////
//
// JointChildObjects.cpp
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
// CreateJointChildObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObject::createJointChildObjects(CResourceManager* resourceManager)
{
	//Primitive object.
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
	object->setAlias(L"子物体链接杆（",L"）");
	//Set color.
	object->setLightColor(GREEN_LIGHT_COLOR);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(CYLINDER_RADIUS,0.20f,CYLINDER_RADIUS);

	//Add subobject.
	childHandle = new CD3DXPrimitiveObject();
#ifdef _DEBUG
	assert(childHandle != _NULL);
#endif
	//Add object.
	addObject(childHandle);
	//Select renderable.
	childHandle->selectRenderable(resourceManager,PRIMITIVE_SPHERE0);
	//Set name.
	childHandle->setAlias(L"子物体链接柄（",L"）");
	//Set color.
	childHandle->setLightColor(GREEN_LIGHT_COLOR);
	//Set action.
	childHandle->setMovable(_TRUE);
	childHandle->setScalable(_FALSE);
	childHandle->setRotatable(_FALSE);
	//Scale it.
	childHandle->setScale(0.03f,0.03f,0.03f);
	//Set position.
	childHandle->setPosition(DEFAULT_CHILD_POSITION);

	//Return ok.
	return S_OK;
}
