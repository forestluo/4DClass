///////////////////////////////////////////////////////////////////////////////
//
// D3DXClassicUpVectorJointObjectProxy.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXClassicUpVectorJointObjectProxy.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
///////////////////////////////////////////////////////////////////////////////

#define JOINT_INSTANCE(p)									((CD3DXJointObject *)(p))

#define CYLINDER_RADIUS										0.009505f
#define DEFAULT_LENGTH										0.5f
#define DEFAULT_DIRECTION									C4DVector3(0.0f,+0.5f,0.0f)
#define DEFAULT_RAW_DIRECTION								C4DVector3(0.0f,+1.0f,0.0f)
#define DEFAULT_CHILD_POSITION								C4DVector3(0.0f,+0.5f,0.0f)
#define GREEN_LIGHT_COLOR									D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXClassicUpVectorJointObjectProxy
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXClassicUpVectorJointObjectProxy::CD3DXClassicUpVectorJointObjectProxy(CD3DXJointObject* joint)
	: CD3DXJointObjectProxy(joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(joint->getJointType() == CJointAttribute::classicUpVectorJoint);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXClassicUpVectorJointObjectProxy
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXClassicUpVectorJointObjectProxy::~CD3DXClassicUpVectorJointObjectProxy(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SetupChildObjects
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXClassicUpVectorJointObjectProxy::setupChildObjects(CListNodeEnumeration& iterator)
{
	//Renderable object.
	CD3DXRenderableObject* object;
	//Controller.
	CObjectController* controller;

#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Get child.
	CPhysicsObject* child = getPhysicsChild();
	//Check child.
	if(child != _NULL)
	{
		//Move joint to the center of child.
		JOINT_INSTANCE(joint)->setPosition(child->getPosition());
	}

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get first object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//The first object is a ball.

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//The first object is a rod of child.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Child vector.
	C4DVector3 vector;

#ifdef _DEBUG
	assert(childHandle != _NULL);
#endif
	//Set default value.
	vector = childHandle->getPosition();
	//Get length.
	_FLOAT length = vector.length();
	//Check length of vector.
	if(length < 0.1f)
	{
		//Set default value.
		vector = DEFAULT_CHILD_POSITION;
		//Set default child position.
		childHandle->setPosition(DEFAULT_CHILD_POSITION);
	}
	//Set major direction.
	JOINT_INSTANCE(joint)->setMajorDirection(vector);
	//Get rotation.
	C4DQuaternion rotation(DEFAULT_RAW_DIRECTION,vector);

	//Set position.
	object->setPosition(vector / 2.0f);
	//Get object controller.
	controller = object->getController();
	//Check result.
	if(controller == _NULL)
	{
		//Set rotation.
		object->setRotation(rotation);
	}
	else
	{
		//Set rotation.
		controller->setRotation(rotation);
	}
	//Scale it.
	object->setScale(CYLINDER_RADIUS,length,CYLINDER_RADIUS);

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//The first object is a rod of child.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set position.
	object->setPosition(vector);
	//Get object controller.
	controller = object->getController();
	//Check result.
	if(controller == _NULL)
	{
		//Set rotation.
		object->setRotation(rotation);
	}
	else
	{
		//Set rotation.
		controller->setRotation(rotation);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateChildObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXClassicUpVectorJointObjectProxy::createChildObjects(CResourceManager* resourceManager)
{
	//Primitive object.
	CD3DXPrimitiveObject* object;

#ifdef _DEBUG
	assert(joint != _NULL);
	assert(resourceManager != _NULL);
#endif

	//Add subobject.
	object = new CD3DXPrimitiveObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Add object.
	JOINT_INSTANCE(joint)->addObject(object);
	//Select renderable.
	object->selectRenderable(resourceManager,PRIMITIVE_SPHERE0);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Set name.
	object->setAlias(L"链接球（",L"）");
	//Scale it.
	object->setScale(0.04f,0.04f,0.04f);
	//Set color.
	object->setLightColor(D3DXVECTOR4(0,1.0f,0.0f,1.0f));

	//Add subobject.
	object = new CD3DXPrimitiveObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Add object.
	JOINT_INSTANCE(joint)->addObject(object);
	//Select renderable.
	object->selectRenderable(resourceManager,PRIMITIVE_CYLINDER0);
	//Set name.
	object->setAlias(L"主轴（",L"）");
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
	JOINT_INSTANCE(joint)->addObject(childHandle);
	//Select renderable.
	childHandle->selectRenderable(resourceManager,PRIMITIVE_CONE0);
	//Set name.
	childHandle->setAlias(L"方向锥（",L"）");
	//Set color.
	childHandle->setLightColor(GREEN_LIGHT_COLOR);
	//Set action.
	childHandle->setMovable(_TRUE);
	childHandle->setScalable(_FALSE);
	childHandle->setRotatable(_FALSE);
	//Scale it.
	childHandle->setScale(CYLINDER_RADIUS + 0.01f,0.10f,CYLINDER_RADIUS + 0.01f);

	//Return result.
	return S_OK;
}
