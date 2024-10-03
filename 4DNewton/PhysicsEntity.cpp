///////////////////////////////////////////////////////////////////////////////
//
// PhysicsEntity.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsEntity.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define COLLISION_BODY(p)									((const NewtonBody *)(p))
#define COLLISION_SHAPE(p)									((const NewtonCollision *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsEntity::CPhysicsEntity(void)
	: currentForce(0.0f,0.0f,0.0f,1.0f)
	, currentPosition(0.0f,0.0f,0.0f,1.0f)
	, currentRotation(1.0f,0.0f,0.0f,0.0f)
	, previousPosition(0.0f,0.0f,0.0f,1.0f)
	, previousRotation(1.0f,0.0f,0.0f,0.0f)
{
	//Set default value.
	mass = 0.0f;
	//Set default value.
	collisionBody = _NULL;
	//Set default value.
	object = (CPhysicsObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsEntity::CPhysicsEntity(_FLOAT mass)
	: currentForce(0.0f,-9.8f * mass,0.0f,1.0f)
	, currentPosition(0.0f,0.0f,0.0f,1.0f)
	, currentRotation(1.0f,0.0f,0.0f,0.0f)
	, previousPosition(0.0f,0.0f,0.0f,1.0f)
	, previousRotation(1.0f,0.0f,0.0f,0.0f)
{
	//Set mass.
	this->mass = mass;

	//Set default value.
	collisionBody = _NULL;
	//Set default value.
	object = (CPhysicsObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsEntity
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsEntity::~CPhysicsEntity(void)
{
	//Clear value.
	collisionBody = _NULL;
	//Clear value.
	object = (CPhysicsObject *)_NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetBody
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CPhysicsEntity::getBody()
{
	//Return result.
	return collisionBody;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Apply
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::apply()
{
	dFloat Ixx;
	dFloat Iyy;
	dFloat Izz;
	dFloat mass;

#ifdef _DEBUG
	assert(collisionBody != _NULL);
#endif

	//For this tutorial the only external force in the Gravity.
	::NewtonBodyGetMassMatrix(COLLISION_BODY(collisionBody),&mass,&Ixx,&Iyy,&Izz);

#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set inertia.
	object->setInertia(C4DVector3(Ixx,Iyy,Izz));

	/**
	//Gravity force.
	//Dropping along Y axis and down to the floor.
	//dVector gravityForce(0.0f,- mass * 9.8f,0.0f);
	*/
	//Set current force.
	::NewtonBodySetForce(COLLISION_BODY(collisionBody),&currentForce[0]);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Destroy
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::destroy()
{
	//Do nothing.
}

/////////////////////////////////////////////////////////////////////////////////
//
// Leave
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::leave()
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Clear object.
	object = (CPhysicsObject *)_NULL;

	//Check collision body.
	if(collisionBody != _NULL)
	{
		//Destroy body.
		::NewtonDestroyBody(NewtonBodyGetWorld(COLLISION_BODY(collisionBody)),COLLISION_BODY(collisionBody));
		//Clear body.
		collisionBody = _NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// Transform
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::transform(const dFloat* matrix)
{
#ifdef _DEBUG
	assert(matrix != _NULL);
#endif

	//Get the position from the matrix.
	dVector posit(matrix[12],matrix[13],matrix[14],1.0f);

	//Rotation.
	dQuaternion rotation;
	//We will ignore the Rotation part of matrix and use the quaternion rotation stored in the body.
	::NewtonBodyGetRotation(COLLISION_BODY(collisionBody),&rotation.m_q0);

	//Since this tutorial run the physics and a different fps than the Graphics
	//We need to save the entity current transformation state before updating the new state.
	previousPosition = currentPosition;
	previousRotation = currentRotation;
	//Reverse it into positive, although they have the same effect.
	if(currentRotation.DotProduct(rotation) < 0.0f) previousRotation.Scale(-1.0f);

	//Set the new position and orientation for this entity.
	currentPosition = posit;
	currentRotation = rotation;
}

/////////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::paragramEnd(_LONG timestamp)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(collisionBody != _NULL);
#endif
	//Call function.
	object->paragramEnd(timestamp);
}

/////////////////////////////////////////////////////////////////////////////////
//
// PhysicsEnd
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::physicsEnd()
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(collisionBody != _NULL);
#endif
	//Call function.
	object->physicsEnd();
}

/////////////////////////////////////////////////////////////////////////////////
//
// PhysicsBegin
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::physicsBegin(_LONG timestamp)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(collisionBody != _NULL);
#endif
	//Call function.
	object->physicsBegin(timestamp);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetForce
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::setForce(const C4DVector3& force)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(collisionBody != _NULL);
#endif
	//Set current position.
	currentForce.m_x = force.x();
	currentForce.m_y = force.y();
	currentForce.m_z = force.z();
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetVelocity
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::setVelocity(const C4DVector3& velocity)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(collisionBody != _NULL);
#endif
	//Set velocity.
	::NewtonBodySetVelocity(COLLISION_BODY(collisionBody),velocity);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetPosition
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::setPosition(const C4DVector3& position)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(collisionBody != _NULL);
#endif
	//Set current position.
	currentPosition.m_x = position.x();
	currentPosition.m_y = position.y();
	currentPosition.m_z = position.z();
	//We need to set physics properties to this body.
	dMatrix matrix(currentRotation,currentPosition);
	//Set matrix.
	::NewtonBodySetMatrix(COLLISION_BODY(collisionBody),&matrix[0][0]);
}

/////////////////////////////////////////////////////////////////////////////////
//
// DetachObject
//
/////////////////////////////////////////////////////////////////////////////////
	
void CPhysicsEntity::detachObject(CPhysicsManager* manager)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
#endif
	//Check body.
	if(collisionBody != _NULL)
	{
		//Destroy body.
		manager->destroyBody(collisionBody);
		//Clear value.
		collisionBody = (NewtonBody *)_NULL;
	}
	//Clear value.
	object = (CPhysicsObject *)_NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// AttachObject
//
/////////////////////////////////////////////////////////////////////////////////
	
_BOOL CPhysicsEntity::attachObject(CPhysicsManager* manager,CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(manager != _NULL);
	assert(this->object == _NULL);
#endif
	//Set value.
	this->object = object;

	//Get rotation.
	C4DQuaternion rotation = object->getRotation();
	//Set rotation.
	previousRotation.m_q0 = rotation.w();
	previousRotation.m_q1 = rotation.x();
	previousRotation.m_q2 = rotation.y();
	previousRotation.m_q3 = rotation.z();
	//Set current rotation.
	currentRotation = previousRotation;

	//Get position.
	C4DVector3 position = object->getPosition();
	//Set position.
	previousPosition.m_x = position.x();
	previousPosition.m_y = position.y();
	previousPosition.m_z = position.z();
	previousPosition.m_w = 1.0f;
	//Set current position.
	currentPosition = previousPosition;

#ifdef _DEBUG
	assert(collisionBody == _NULL);
#endif
	//Shapes.
	CListNodeContainer shapes;
	//Create shape.
	//If it is a compound collision, the shapes should not be empty.
	_OBJECT collisionShape = createShape(manager,shapes);
	//Check result.
	if(collisionShape != _NULL)
	{
		//Initialize entity.
		initialize(manager,collisionShape);
		//Destroy shape.
		manager->destroyShape(collisionShape);
	}
	//Iterator.
	CListNodeEnumeration iterator;
	//Get enumeration.
	shapes.getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get shape.
		collisionShape = iterator.nextElement();
#ifdef _DEBUG
		assert(collisionShape != _NULL);
#endif
		//Destroy shape.
		manager->destroyShape(collisionShape);
	}
	//Return result.
	return collisionBody != _NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetBoundingBox
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::getBoundingBox(dVector& minBox,dVector& maxBox)
{
#ifdef _DEBUG
	assert(object != NULL);
	assert(object->getObjectType() != CWorldObject::jointObject);
#endif

	//Box.
	CSimpleBox box;
#ifndef _DEBUG
	((CPhysicsObject *)object)->getBox(box);
#else
	assert(((CPhysicsObject *)object)->getBox(box));
#endif
	//Get scale.
	C4DVector3 scale = object->getScale();
	//Get minimum value.
	minBox.m_w = 1.0f;
	minBox.m_x = box.x() - box.dx() * scale.x();
	minBox.m_y = box.y() - box.dy() * scale.y();
	minBox.m_z = box.z() - box.dz() * scale.z();
	//Get maximum value.
	maxBox.m_w = 1.0f;
	maxBox.m_x = box.x() + box.dx() * scale.x();
	maxBox.m_y = box.y() + box.dy() * scale.y();
	maxBox.m_z = box.z() + box.dz() * scale.z();
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetParagram
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::setParagram(dFloat interpolationParam)
{
	//Check interpolation param.
	if(interpolationParam > 1.0f) interpolationParam = 1.0f;

	//Calculate visual transform by interpolating between previous and current state.
	dQuaternion rotation(previousRotation.Slerp(currentRotation,interpolationParam));
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set quaternion.
	//m_q0 => w, m_q1 => x, m_q2 => y, mq3 => z
	object->setRotation(C4DQuaternion(rotation.m_q1,rotation.m_q2,rotation.m_q3,rotation.m_q0));

	//Get transformation.
	dVector posit(previousPosition + (currentPosition - previousPosition).Scale(interpolationParam));
#ifdef _DEBUG
	assert(posit.m_w != 0.0f);
#endif
	//Set value.
	object->setPosition(C4DVector3(posit.m_x / posit.m_w,posit.m_y / posit.m_w,posit.m_z / posit.m_w));
}

///////////////////////////////////////////////////////////////////////////////
//
// DestroyBodyCallback
//
///////////////////////////////////////////////////////////////////////////////

void DestroyBodyCallback(const NewtonBody* body)
{
	//Entity.
	CPhysicsEntity* entity;

#ifdef _DEBUG
	assert(body != _NULL);
#endif
	//Get the entity associated with this rigid body.
	entity = (CPhysicsEntity *)NewtonBodyGetUserData(body);
	//Check result.
	if(entity != _NULL) entity->destroy();
}

///////////////////////////////////////////////////////////////////////////////
//
// ApplyForceAndTorqueCallback
//
///////////////////////////////////////////////////////////////////////////////

void ApplyForceAndTorqueCallback(const NewtonBody* body,dFloat timestep,int threadIndex)
{
	//Entity.
	CPhysicsEntity* entity;

#ifdef _DEBUG
	assert(body != _NULL);
#endif
	//Get the entity associated with this rigid body.
	entity = (CPhysicsEntity *)NewtonBodyGetUserData(body);
	//Check result.
	if(entity != _NULL) entity->apply();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetTransformCallback
//
// Transform callback to set the matrix of a the visual entity.
//
///////////////////////////////////////////////////////////////////////////////

void SetTransformCallback(const NewtonBody* body,const dFloat* matrix,int threadIndex)
{
	//Entity.
	CPhysicsEntity* entity;

#ifdef _DEBUG
	assert(body != _NULL);
#endif
	//Get the entity associated with this rigid body.
	entity = (CPhysicsEntity *)NewtonBodyGetUserData(body);
	//Check result.
	if(entity != _NULL) entity->transform(matrix);
}

///////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsEntity::initialize(CPhysicsManager *manager,_OBJECT collisionShape)
{
	dVector minBox, maxBox;
	dVector origin, inertia;

#ifdef _DEBUG
	assert(manager != _NULL);
	assert(collisionShape != _NULL);
#endif
	//Now with the collision Shape we can crate a rigid body.
	collisionBody = manager->createBody(collisionShape,mass);
#ifdef _DEBUG
	assert(collisionBody != _NULL);
#endif
	//Save the entity as the user data for this body.
	::NewtonBodySetUserData(COLLISION_BODY(collisionBody),this);

	//Bodies can have a destructor. 
	//This is a function callback that can be used to destroy any local data stored
	//And that need to be destroyed before the body is destroyed. 
	::NewtonBodySetDestructorCallback(COLLISION_BODY(collisionBody),DestroyBodyCallback);

	//We need to set physics properties to this body.
	dMatrix matrix(currentRotation,currentPosition);
	::NewtonBodySetMatrix(COLLISION_BODY(collisionBody),&matrix[0][0]);

	//We need to set the proper center of mass and inertia matrix for this body
	//the inertia matrix calculated by this function does not include the mass.
	//therefore it needs to be multiplied by the mass of the body before it is used.
	::NewtonConvexCollisionCalculateInertialMatrix(COLLISION_SHAPE(collisionShape),&inertia[0],&origin[0]);	

	//Set the body mass matrix.
	::NewtonBodySetMassMatrix(COLLISION_BODY(collisionBody),mass,mass * inertia.m_x,mass * inertia.m_y,mass * inertia.m_z);

	//Set the body origin.
	::NewtonBodySetCentreOfMass(COLLISION_BODY(collisionBody),&origin[0]);

	//Set the function callback to apply the external forces and torque to the body.
	//The most common force is Gravity.
	::NewtonBodySetForceAndTorqueCallback(COLLISION_BODY(collisionBody),ApplyForceAndTorqueCallback);

	//Set the function callback to set the transformation state of the graphic entity associated with this body.
	//Each time the body change position and orientation in the physics world.
	::NewtonBodySetTransformCallback(COLLISION_BODY(collisionBody),SetTransformCallback);
}