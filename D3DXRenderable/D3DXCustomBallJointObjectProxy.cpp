///////////////////////////////////////////////////////////////////////////////
//
// D3DXCustomBallJointObjectProxy.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXCustomBallJointObjectProxy.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "PhysicsJointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
///////////////////////////////////////////////////////////////////////////////

#define JOINT_INSTANCE(p)									((CD3DXJointObject *)(p))

#define CYLINDER_RADIUS										0.009505f
#define DEFAULT_DIRECTION									C4DVector3(0.0f,-1.0f,0.0f)
#define DEFAULT_RAW_DIRECTION								C4DVector3(0.0f,+1.0f,0.0f)
#define DEFAULT_CHILD_POSITION								C4DVector3(0.0f,-0.1f,0.0f)
#define DEFAULT_PARENT_POSITION								C4DVector3(0.0f,+0.1f,0.0f)
#define BLUE_LIGHT_COLOR									D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f)
#define YELLOW_LIGHT_COLOR									D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f)
#define GREEN_LIGHT_COLOR									D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCustomBallJointObjectProxy
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXCustomBallJointObjectProxy::CD3DXCustomBallJointObjectProxy(CD3DXJointObject* joint)
	: CD3DXJointObjectProxy(joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(joint->getJointType() == CJointAttribute::customBallJoint);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCustomBallJointObjectProxy
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXCustomBallJointObjectProxy::~CD3DXCustomBallJointObjectProxy(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SetupChildObjects
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXCustomBallJointObjectProxy::setupChildObjects(CListNodeEnumeration& iterator)
{
	//Renderable object.
	CD3DXRenderableObject* object;

	//Get first object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//The first object is a ball.
	//Let it be at center of local axis.
	object->setPosition(0.0f,0.0f,0.0f);

	//Get position.
	C4DVector3 position;
	//Get child.
	CWorldObject* child = JOINT_INSTANCE(joint)->getJointChild();
	//Check child.
	if(child == _NULL)
	{
#ifdef _DEBUG
		assert(childHandle != _NULL);
#endif
		//Set default position.
		position = childHandle->getPosition();
	}
	else
	{
		//Get child position in local axis.
		position = child->getPosition() - JOINT_INSTANCE(joint)->getPosition();
	}
	//Set rotation.
	object->setRotation(C4DQuaternion(DEFAULT_RAW_DIRECTION,position));

	//Call function.
	CD3DXJointObjectProxy::setupChildObjects(iterator);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetupParentObjects
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXCustomBallJointObjectProxy::setupParentObjects(CListNodeEnumeration& iterator)
{
	//Renderable object.
	CD3DXRenderableObject* object;

	//Get second object.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//The second object is a hemisphere.
	//Let it be at center of local axis.
	object->setPosition(0.0f,0.0f,0.0f);

	//Get position.
	C4DVector3 position;
	//Get parent.
	CWorldObject* parent = JOINT_INSTANCE(joint)->getJointParent();
	//Check parent.
	if(parent == _NULL)
	{
#ifdef _DEBUG
		assert(parentHandle != _NULL);
#endif
		//Set default position.
		position = parentHandle->getPosition();
	}
	else
	{
		//Get parent position in local axis.
		position = parent->getPosition() - JOINT_INSTANCE(joint)->getPosition();
	}
	//Set rotation.
	object->setRotation(C4DQuaternion(DEFAULT_RAW_DIRECTION,position));

	//Call function.
	CD3DXJointObjectProxy::setupParentObjects(iterator);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateChildObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXCustomBallJointObjectProxy::createChildObjects(CResourceManager* resourceManager)
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
	object->setAlias(L"球关节（",L"）");
	//Scale it.
	object->setScale(0.04f,0.04f,0.04f);
	//Set color.
	object->setLightColor(BLUE_LIGHT_COLOR);

	//Return result.
	return CD3DXJointObjectProxy::createChildObjects(resourceManager);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateParentObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXCustomBallJointObjectProxy::createParentObjects(CResourceManager* resourceManager)
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
	JOINT_INSTANCE(joint)->addObject(object);
	//Select renderable.
	object->selectRenderable(resourceManager,PRIMITIVE_HEMISPHERE0);
	//Set action.
	object->setMovable(_FALSE);
	object->setScalable(_FALSE);
	object->setRotatable(_FALSE);
	//Set name.
	object->setAlias(L"球关节座（",L"）");
	//Scale it.
	object->setScale(0.048f,0.048f,0.048f);
	//Set color.
	object->setLightColor(YELLOW_LIGHT_COLOR);

	//Return result.
	return CD3DXJointObjectProxy::createParentObjects(resourceManager);
}
