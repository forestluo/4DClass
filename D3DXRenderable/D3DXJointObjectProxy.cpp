///////////////////////////////////////////////////////////////////////////////
//
// D3DXJointObjectProxy.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXJointObjectProxy.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "ListNodeEnumeration.h"
#include "PhysicsJointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
///////////////////////////////////////////////////////////////////////////////

#define JOINT_INSTANCE(p)									((CD3DXJointObject *)(p))

#define CYLINDER_RADIUS										0.009505f
#define DEFAULT_DIRECTION									C4DVector3(1.0f,1.0f,1.0f)
#define DEFAULT_RAW_DIRECTION								C4DVector3(0.0f,+1.0f,0.0f)
#define DEFAULT_CHILD_POSITION								C4DVector3(0.0f,-0.1f,0.0f)
#define DEFAULT_PARENT_POSITION								C4DVector3(0.0f,+0.1f,0.0f)
#define GREEN_LIGHT_COLOR									D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f)
#define YELLOW_LIGHT_COLOR									D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f)

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXJointObjectProxy
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXJointObjectProxy::CD3DXJointObjectProxy(CD3DXJointObject* joint)
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(joint->getJointType() != CJointAttribute::nullJoint);
#endif
	//Set joint.
	this->joint = joint;

	//Set default value.
	childHandle = (CD3DXPrimitiveObject *)_NULL;
	parentHandle = (CD3DXPrimitiveObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXJointObjectProxy
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXJointObjectProxy::~CD3DXJointObjectProxy(void)
{
	//Clear joint.
	joint = (CD3DXJointObject *)_NULL;
	//Clear value.
	childHandle = (CD3DXPrimitiveObject *)_NULL;
	parentHandle = (CD3DXPrimitiveObject *)_NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPhysicsChild
//
/////////////////////////////////////////////////////////////////////////////////
	
CPhysicsObject* CD3DXJointObjectProxy::getPhysicsChild() const
{
#ifdef _DEBUG
	assert(joint != _NULL);
#endif

	//Get child.
	CWorldObject* child = JOINT_INSTANCE(joint)->getJointChild();
	//Check result.
	if(child == _NULL) return (CPhysicsObject *)_NULL;
#ifdef _DEBUG
	assert(child != _NULL && child->isPhysicsObject());
	assert(child->getObjectType() != CWorldObject::jointObject);
#endif
	//Get physics object.
	CPhysicsObject* physicsChild = (CPhysicsObject *)child->getPhysics();
#ifdef _DEBUG
	assert(physicsChild != _NULL);
	assert(physicsChild->getMass() > 0.0f);
#endif
	//Return result.
	return physicsChild;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPhysicsParent
//
/////////////////////////////////////////////////////////////////////////////////
	
CPhysicsObject* CD3DXJointObjectProxy::getPhysicsParent() const
{
#ifdef _DEBUG
	assert(joint != _NULL);
#endif

	//Get parent.
	CWorldObject* parent = JOINT_INSTANCE(joint)->getJointParent();
	//Check result.
	if(parent == _NULL) return (CPhysicsObject *)_NULL;
#ifdef _DEBUG
	assert(parent->isPhysicsObject());
	assert(parent->getObjectType() != CWorldObject::jointObject);
#endif
	//Get physics object.
	CPhysicsObject* physicsParent = (CPhysicsObject *)parent->getPhysics();
#ifdef _DEBUG
	assert(physicsParent->getMass() >= 0.0f);
#endif
	//Return result.
	return physicsParent;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetRelativeDirection
//
/////////////////////////////////////////////////////////////////////////////////

C4DVector3 CD3DXJointObjectProxy::getRelativeDirection(_BOOL childFlag) const
{
#ifdef _DEBUG
	assert(joint != _NULL);
	assert(JOINT_INSTANCE(joint)->isPhysicsObject());
#endif
	//Get physics joint object.
	CPhysicsJointObject* jointObject =
		(CPhysicsJointObject *)((CPhysicsObject *)JOINT_INSTANCE(joint)->getPhysics());
#ifdef _DEBUG
	assert(jointObject != _NULL);
#endif
	//Return result.
	return jointObject->getRelativeDirection(childFlag);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetupChildObjects
//
///////////////////////////////////////////////////////////////////////////////

CD3DXRenderableObject* CD3DXJointObjectProxy::nextObject(CListNodeEnumeration& iterator)
{
#ifdef _DEBUG
	assert(iterator.hasMoreElements());
#endif
	//Get object.
	CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
	assert(object != _NULL);
	assert(object->isRenderableObject());
	assert(object->getObjectType() == CWorldObject::primitiveObject);
#endif
	//Return result.
	return (CD3DXRenderableObject *)object->getRenderable();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetupChildObjects
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXJointObjectProxy::setupChildObjects(CListNodeEnumeration& iterator)
{
	//Renderable object.
	CD3DXRenderableObject* object;

	//The first object is a rod of child.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Child vector.
	C4DVector3 vector;
#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Get child.
	CPhysicsObject* child = getPhysicsChild();
	//Check child.
	if(child != _NULL)
	{
		//Set value.
		vector = child->getPosition() - JOINT_INSTANCE(joint)->getPosition();
	}
	else
	{
#ifdef _DEBUG
		assert(childHandle != _NULL);
#endif
		//Set default value.
		vector = childHandle->getPosition();
		//Check length of vector.
		if(vector.length() < 0.1f)
		{
			//Set default value.
			vector = DEFAULT_CHILD_POSITION;
			//Set default child position.
			childHandle->setPosition(DEFAULT_CHILD_POSITION);
		}
	}

	//Get axis direction.
	C4DVector3 axisDirection;
	//Check child.
	if(child == _NULL)
	{
#ifdef _DEBUG
		assert(childHandle != _NULL);
#endif
		//Set direction.
		axisDirection = childHandle->getPosition();
	}
	else
	{
		//Set child direction.
		axisDirection = child->getRotationAccompany(- getRelativeDirection(_TRUE));
	}
	//Get length of child.
	_FLOAT length = axisDirection.length();
	//Scale it.
	object->setScale(CYLINDER_RADIUS,length,CYLINDER_RADIUS);
	//Set rotation.
	object->setRotation(C4DQuaternion(DEFAULT_RAW_DIRECTION,axisDirection));

	//Check child.
	if(child == _NULL)
	{
#ifdef _DEBUG
		assert(childHandle != _NULL);
#endif
		//Set position.
		object->setPosition(childHandle->getPosition() / 2.0f);
	}
	else
	{
		//Calculate the middle position of the rod.
		//The position of object is a relative position in joint axis.
		object->setPosition(axisDirection / 2.0f + child->getPosition() - JOINT_INSTANCE(joint)->getPosition());
	}

	//The second object is a ball of child.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set position.
	object->setPosition(vector);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetupParentObjects
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXJointObjectProxy::setupParentObjects(CListNodeEnumeration& iterator)
{
	//Renderable object.
	CD3DXRenderableObject* object;

	//The first object is a rod of child.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Parent vector.
	C4DVector3 vector;
	//Get parent.
	CPhysicsObject* parent = getPhysicsParent();
	//Check parent.
	if(parent != _NULL)
	{
		//Set value.
		vector = parent->getPosition() - JOINT_INSTANCE(joint)->getPosition();
	}
	else
	{
#ifdef _DEBUG
		assert(parentHandle != _NULL);
#endif
		//Set default value.
		vector = parentHandle->getPosition();
		//Check length of vector.
		if(vector.length() < 0.1f)
		{
			//Set default value.
			vector = DEFAULT_PARENT_POSITION;
			//Set default parent position.
			parentHandle->setPosition(DEFAULT_PARENT_POSITION);
		}
	}

	//Get axis direction.
	C4DVector3 axisDirection;
	//Check parent.
	if(parent == _NULL)
	{
#ifdef _DEBUG
		assert(parentHandle != _NULL);
#endif
		//Set direction.
		axisDirection = parentHandle->getPosition();
	}
	else
	{
		//Set parent direction.
		axisDirection = parent->getRotationAccompany(- getRelativeDirection(_FALSE));
	}
	//Get length of parent.
	_FLOAT length = axisDirection.length();
	//Scale it.
	object->setScale(CYLINDER_RADIUS,length,CYLINDER_RADIUS);
	//Set rotation.
	object->setRotation(C4DQuaternion(DEFAULT_RAW_DIRECTION,axisDirection));

	//Check parent.
	if(parent == _NULL)
	{
#ifdef _DEBUG
		assert(parentHandle != _NULL);
#endif
		//Set default value.
		object->setPosition(parentHandle->getPosition() / 2.0f);
	}
	else
	{
		//Calculate the middle position of the rod.
		//The position of object is a relative position in joint axis.
		object->setPosition(axisDirection / 2.0f + parent->getPosition() - JOINT_INSTANCE(joint)->getPosition());
	}

	//The second object is a ball of parent.
	object = nextObject(iterator);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set position.
	object->setPosition(vector);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetupCommonObjects
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXJointObjectProxy::setupCommonObjects(CListNodeEnumeration& iterator)
{
	
}

///////////////////////////////////////////////////////////////////////////////
//
// SetupObjects
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXJointObjectProxy::setupObjects()
{
	//Iterator.
	CListNodeEnumeration iterator;
#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Get enumeration.
	JOINT_INSTANCE(joint)->getEnumeration(iterator);

	//Setup common objects.
	setupCommonObjects(iterator);
	//Setup child objects.
	setupChildObjects(iterator);
	//Setup parent objects.
	setupParentObjects(iterator);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateChildObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObjectProxy::createChildObjects(CResourceManager* resourceManager)
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
	//Select rederable.
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
	JOINT_INSTANCE(joint)->addObject(childHandle);
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

///////////////////////////////////////////////////////////////////////////////
//
// CreateParentObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObjectProxy::createParentObjects(CResourceManager* resourceManager)
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
	assert(parentHandle != _NULL);
#endif
	//Add object.
	JOINT_INSTANCE(joint)->addObject(parentHandle);
	//Select rederable.
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

///////////////////////////////////////////////////////////////////////////////
//
// CreateCommonObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObjectProxy::createCommonObjects(CResourceManager* resourceManager)
{
	//Return result.
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObjectProxy::initializeObjects(CResourceManager* resourceManager)
{
	//Create objects.
	HRESULT hr;
	//Create common objects.
	V_RETURN(createCommonObjects(resourceManager));
	//Create child objects.
	V_RETURN(createChildObjects(resourceManager));
	//Create parent objects.
	V_RETURN(createParentObjects(resourceManager));
	//Create and setup objects.
	if(SUCCEEDED(hr)) setupObjects();
	//Return result.
	return hr;
}
