///////////////////////////////////////////////////////////////////////////////
//
// D3DXClassicSliderJointObjectProxy.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXClassicSliderJointObjectProxy.h"

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

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXClassicSliderJointObjectProxy
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXClassicSliderJointObjectProxy::CD3DXClassicSliderJointObjectProxy(CD3DXJointObject* joint)
	: CD3DXJointObjectProxy(joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(joint->getJointType() == CJointAttribute::classicSliderJoint);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXClassicSliderJointObjectProxy
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXClassicSliderJointObjectProxy::~CD3DXClassicSliderJointObjectProxy(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SetupCommonObjects
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXClassicSliderJointObjectProxy::setupCommonObjects(CListNodeEnumeration& iterator)
{
	CD3DXRenderableObject* object;

#ifdef _DEBUG
	assert(joint != _NULL);
#endif

	//Child rod direction.
	C4DVector3 childRodDirection(0.0f,0.0f,0.0f);
	//Get child.
	CPhysicsObject* child = getPhysicsChild();
	//Check child.
	if(child != _NULL)
	{
		//Get direction.
		childRodDirection = child->getRotationAccompany(- getRelativeDirection(_TRUE))
															+ child->getPosition() - JOINT_INSTANCE(joint)->getPosition();
	}
	//Parent rod direction.
	C4DVector3 parentRodDirection(0.0f,0.0f,0.0f);
	//Get parent.
	CPhysicsObject* parent = getPhysicsParent();
	//Check parent.
	if(parent != _NULL)
	{
		//Get direction.
		parentRodDirection = parent->getRotationAccompany(- getRelativeDirection(_FALSE))
															+ parent->getPosition() - JOINT_INSTANCE(joint)->getPosition();
	}
	//Length.
	_FLOAT length = childRodDirection.length() + parentRodDirection.length();

	//Get joint attribute.
	C4DVector3 direction = JOINT_INSTANCE(joint)->getMajorDirection();

	//Get direction in child axis.
	C4DVector3 direction1;
	//Check child.
	if(child == _NULL)
	{
		//Set default direction.
		direction1 = direction;
	}
	else
	{
		//Get current direction.
		direction1 = child->getRotationAccompany(direction);
	}

	//Get direction in parent axis.
	C4DVector3 direction2;
	//Check parent.
	if(parent == _NULL)
	{
		//Set default direction.
		direction2 = direction;
	}
	else
	{
		//Get current direction.
		direction2 = parent->getRotationAccompany(direction);
	}

	//Rotation.
	C4DQuaternion rotation(DEFAULT_DIRECTION,(direction1 + direction2) / 2.0f);

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
	object->setScale(C4DVector3(length + 0.24f,0.08f,0.08f));

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
	if(parent != _NULL)
	{
		//Calculate the middle position of the rod.
		//The position of object is a relative position in joint axis.
		object->setPosition(parentRodDirection);
	}
	else
	{
#ifdef _DEBUG
		assert(parentHandle != _NULL);
#endif
		//Set default value.
		object->setPosition(C4DVector3(0.0f,0.0f,0.0f));
	}

	//Call function.
	CD3DXJointObjectProxy::setupCommonObjects(iterator);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCommonObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXClassicSliderJointObjectProxy::createCommonObjects(CResourceManager* resourceManager)
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
	object->selectRenderable(resourceManager,PRIMITIVE_CUBOID0);
	//Set name.
	object->setAlias(L"Ö÷»¬¿é£¨",L"£©");
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.24f,0.08f,0.08f);
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
	object->selectRenderable(resourceManager,PRIMITIVE_CUBOID0);
	//Set name.
	object->setAlias(L"»¬¶¯²Û£¨",L"£©");
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.20f,0.096f,0.096f);
	//Set color.
	object->setLightColor(D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f));

	//Return result.
	return CD3DXJointObjectProxy::createCommonObjects(resourceManager);
}