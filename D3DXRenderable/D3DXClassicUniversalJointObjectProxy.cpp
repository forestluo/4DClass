///////////////////////////////////////////////////////////////////////////////
//
// D3DXClassicUniversalJointObjectProxy.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXClassicUniversalJointObjectProxy.h"

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
#define DEFAULT_RAW_DIRECTION								C4DVector3(0.0f,1.0f,0.0f)
#define DEFAULT_MAJOR_DIRECTION								C4DVector3(1.0f,0.0f,0.0f)
#define DEFAULT_MINOR_DIRECTION								C4DVector3(0.0f,0.0f,1.0f)
#define RED_LIGHT_COLOR										D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f)
#define GREEN_LIGHT_COLOR									D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f)
#define YELLOW_LIGHT_COLOR									D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXClassicUniversalJointObjectProxy
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXClassicUniversalJointObjectProxy::CD3DXClassicUniversalJointObjectProxy(CD3DXJointObject* joint)
	: CD3DXJointObjectProxy(joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(joint->getJointType() == CJointAttribute::classicUniversalJoint);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXClassicUniversalJointObjectProxy
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXClassicUniversalJointObjectProxy::~CD3DXClassicUniversalJointObjectProxy(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SetupCommonObjects
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXClassicUniversalJointObjectProxy::setupCommonObjects(CListNodeEnumeration& iterator)
{
	//Renderable object.
	CD3DXRenderableObject* object;

#ifdef _DEBUG
	assert(joint != _NULL);
#endif

	//Get joint attribute.
	C4DVector3 majorDirection = JOINT_INSTANCE(joint)->getMajorDirection();

	//Get direction in child axis.
	C4DVector3 direction1;
	//Get child.
	CPhysicsObject* child = getPhysicsChild();
	//Check child.
	if(child == _NULL)
	{
		//Set default direction.
		direction1 = majorDirection;
	}
	else
	{
		//Get current direction.
		direction1 = child->getRotationAccompany(majorDirection);
	}
	//Rotation.
	C4DQuaternion rotation1(DEFAULT_RAW_DIRECTION,direction1);

	//Get joint attribute.
	C4DVector3 minorDirection = JOINT_INSTANCE(joint)->getMinorDirection();

	//Get direction in parent axis.
	C4DVector3 direction2;
	//Get parent.
	CPhysicsObject* parent = getPhysicsParent();
	//Check parent.
	if(parent == _NULL)
	{
		//Set default direction.
		direction2 = minorDirection;
	}
	else
	{
		//Get current direction.
		direction2 = parent->getRotationAccompany(minorDirection);
	}
	//Rotation.
	C4DQuaternion rotation2(DEFAULT_RAW_DIRECTION,direction2);

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get first object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set rotation.
	object->setRotation(rotation1);

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get second object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set rotation.
	object->setRotation(rotation1);

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get first object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set rotation.
	object->setRotation(rotation2);

#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get second object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set rotation.
	object->setRotation(rotation2);

	//Call function.
	CD3DXJointObjectProxy::setupCommonObjects(iterator);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCommonObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXClassicUniversalJointObjectProxy::createCommonObjects(CResourceManager* resourceManager)
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
	object->setAlias(L"主转轴（",L"）");
	//Set color.
	object->setLightColor(GREEN_LIGHT_COLOR);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.04f,0.128f,0.04f);
	//Set position.
	object->setPosition(0.0f,+0.02f,0.0f);

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
	object->setAlias(L"主转轴套（",L"）");
	//Set color.
	object->setLightColor(YELLOW_LIGHT_COLOR);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.048f,0.096f,0.048f);
	//Set position.
	object->setPosition(0.0f,+0.02f,0.0f);

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
	object->setAlias(L"副转轴（",L"）");
	//Set color.
	object->setLightColor(GREEN_LIGHT_COLOR);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.04f,0.128f,0.04f);
	//Set position.
	object->setPosition(0.0f,-0.02f,0.0f);

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
	object->setAlias(L"副转轴套（",L"）");
	//Set color.
	object->setLightColor(YELLOW_LIGHT_COLOR);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Scale it.
	object->setScale(0.048f,0.096f,0.048f);
	//Set position.
	object->setPosition(0.0f,-0.02f,0.0f);

	//Return result.
	return CD3DXJointObjectProxy::createCommonObjects(resourceManager);
}
