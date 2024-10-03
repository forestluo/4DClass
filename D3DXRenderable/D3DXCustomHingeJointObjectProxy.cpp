///////////////////////////////////////////////////////////////////////////////
//
// D3DXCustomHingeJointObjectProxy.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXCustomHingeJointObjectProxy.h"

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
#define DEFAULT_DIRECTION									C4DVector3(0.0f,0.0f,-1.0f)
#define DEFAULT_RAW_DIRECTION								C4DVector3(0.0f,+1.0f,0.0f)
#define DEFAULT_CHILD_POSITION								C4DVector3(0.0f,-0.1f,0.0f)
#define DEFAULT_PARENT_POSITION								C4DVector3(0.0f,+0.1f,0.0f)
#define RED_LIGHT_COLOR										D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f)
#define GREEN_LIGHT_COLOR									D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f)
#define YELLOW_LIGHT_COLOR									D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f)
#define BLUE_LIGHT_COLOR									D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCustomHingeJointObjectProxy
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXCustomHingeJointObjectProxy::CD3DXCustomHingeJointObjectProxy(CD3DXJointObject* joint)
	: CD3DXJointObjectProxy(joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(joint->getJointType() == CJointAttribute::customHingeJoint);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCustomHingeJointObjectProxy
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXCustomHingeJointObjectProxy::~CD3DXCustomHingeJointObjectProxy(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SetupCommonObjects
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXCustomHingeJointObjectProxy::setupCommonObjects(CListNodeEnumeration& iterator)
{
	//Renderable object.
	CD3DXRenderableObject* object;

#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Get joint attribute.
	C4DVector3 direction = JOINT_INSTANCE(joint)->getMajorDirection();

	//Get direction in child axis.
	C4DVector3 direction1;
	//Get child.
	CPhysicsObject* child = getPhysicsChild();
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
	//Get child.
	CPhysicsObject* parent = getPhysicsParent();
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
	C4DQuaternion rotation(DEFAULT_RAW_DIRECTION,(direction1 + direction2) / 2.0f);

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get first object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set rotation.
	object->setRotation(rotation);

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

	//Call function.
	CD3DXJointObjectProxy::setupCommonObjects(iterator);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCommonObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXCustomHingeJointObjectProxy::createCommonObjects(CResourceManager* resourceManager)
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
	object->setAlias(L"Ö÷×ªÖá£¨",L"£©");
	//Set color.
	object->setLightColor(BLUE_LIGHT_COLOR);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.04f,0.08f,0.04f);

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
	object->setAlias(L"×ªÖáÌ×£¨",L"£©");
	//Set color.
	object->setLightColor(YELLOW_LIGHT_COLOR);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.048f,0.048f,0.048f);

	//Return result.
	return CD3DXJointObjectProxy::createCommonObjects(resourceManager);
}
