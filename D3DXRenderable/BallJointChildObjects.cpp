///////////////////////////////////////////////////////////////////////////////
//
// BallJointChildObjects.h
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
// Definitions.
//
///////////////////////////////////////////////////////////////////////////////

#define CYLINDER_RADIUS										0.009505f
#define DEFAULT_DIRECTION									C4DVector3(0.0f,-1.0f,0.0f)
#define DEFAULT_RAW_DIRECTION								C4DVector3(0.0f,+1.0f,0.0f)
#define DEFAULT_CHILD_POSITION								C4DVector3(0.0f,-0.1f,0.0f)
#define DEFAULT_PARENT_POSITION								C4DVector3(0.0f,+0.1f,0.0f)
#define BLUE_LIGHT_COLOR									D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CreateChildObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObject::createBallJointChildObjects(CResourceManager* resourceManager)
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
	object->selectRenderable(resourceManager,PRIMITIVE_SPHERE0);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Set name.
	object->setAlias(L"Çò¹Ø½Ú£¨",L"£©");
	//Scale it.
	object->setScale(0.04f,0.04f,0.04f);
	//Set color.
	object->setLightColor(D3DXVECTOR4(0,1.0f,0.0f,1.0f));

	//Return result.
	return createJointChildObjects(resourceManager);
}
