///////////////////////////////////////////////////////////////////////////////
//
// D3DXCustom6DOFJointObjectProxy.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXCustom6DOFJointObjectProxy.h"

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
#define DEFAULT_DIRECTION									C4DVector3(1.0f,0.0f,0.0f)
#define DEFAULT_RAW_DIRECTION								C4DVector3(0.0f,1.0f,0.0f)
#define RED_LIGHT_COLOR										D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f)
#define GREEN_LIGHT_COLOR									D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f)
#define YELLOW_LIGHT_COLOR									D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f)
#define BLUE_LIGHT_COLOR									D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCustom6DOFJointObjectProxy
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXCustom6DOFJointObjectProxy::CD3DXCustom6DOFJointObjectProxy(CD3DXJointObject* joint)
	: CD3DXJointObjectProxy(joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(joint->getJointType() == CJointAttribute::custom6DOFJoint);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCustom6DOFJointObjectProxy
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXCustom6DOFJointObjectProxy::~CD3DXCustom6DOFJointObjectProxy(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SetupCommonObjects
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXCustom6DOFJointObjectProxy::setupCommonObjects(CListNodeEnumeration& iterator)
{
	CD3DXRenderableObject* object;

#ifdef _DEBUG
	assert(joint != _NULL);
#endif

	//Child rod position.
	C4DVector3 childRodPosition;
	//Get child.
	CPhysicsObject* child = getPhysicsChild();
	//Check child.
	if(child != _NULL)
	{
		//Get position.
		childRodPosition = child->getRotationAccompany(- getRelativeDirection(_TRUE)) + child->getPosition();
	}
	//Parent rod position.
	C4DVector3 parentRodPosition;
	//Get parent.
	CPhysicsObject* parent = getPhysicsParent();
	//Check parent.
	if(parent != _NULL)
	{
		//Get position.
		parentRodPosition = parent->getRotationAccompany(- getRelativeDirection(_FALSE)) + parent->getPosition();
	}
	//Get joint attribute.
	C4DVector3 distance = childRodPosition - parentRodPosition;
	//Get length.
	_FLOAT length = distance.length();
	//Check distance.
	if(length <= 0.001f)
	{
		//Set direction.
		distance = (child != _NULL ? child->getPosition() : C4DVector3()) - 
						(parent != _NULL ? parent->getPosition() : C4DVector3());
	}
	//Check distance.
	if(distance.length() <= 0.0f)
	{
		distance = DEFAULT_DIRECTION; length = distance.length();
	}
	//Rotation.
	C4DQuaternion rotation(DEFAULT_RAW_DIRECTION,distance);

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get second object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set rotation.
	object->setRotation(rotation);
	//Scale it.
	object->setScale(C4DVector3(0.03f,(length < 0.10f ? 0.10f : length) + 0.02f,0.03f));

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get second object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set rotation.
	object->setRotation(rotation);
	//Check parent.
	if(parent == _NULL)
	{
#ifdef _DEBUG
		assert(parentHandle != _NULL);
#endif
		//Set default value.
		object->setPosition(C4DVector3(0.0f,0.0f,0.0f));
	}
	else
	{
		//Calculate the middle position of the rod.
		//The position of object is a relative position in joint axis.
		object->setPosition(parentRodPosition - JOINT_INSTANCE(joint)->getPosition());
	}

	//Call function.
	CD3DXJointObjectProxy::setupCommonObjects(iterator);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCommonObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXCustom6DOFJointObjectProxy::createCommonObjects(CResourceManager* resourceManager)
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
	object->selectRenderable(resourceManager,PRIMITIVE_CYLINDER0);
	//Set name.
	object->setAlias(L"Ö÷»¬¿é£¨",L"£©");
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.03f,0.12f,0.03f);
	//Set color.
	object->setLightColor(BLUE_LIGHT_COLOR);

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
	object->setAlias(L"»¬¶¯²Û£¨",L"£©");
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.032f,0.10f,0.032f);
	//Set color.
	object->setLightColor(YELLOW_LIGHT_COLOR);

	//Return result.
	return CD3DXJointObjectProxy::createCommonObjects(resourceManager);
}