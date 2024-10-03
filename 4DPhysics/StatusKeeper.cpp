///////////////////////////////////////////////////////////////////////////////
//
// StatusKeeper.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "StatusKeeper.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define	ORIGIN												0
#define LAST_0												1
#define LAST_1												2

#define OBJECT_INSTANCE(p)									((CPhysicsObject *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CStatusKeeper::base(L"CStatusKeeper",L"CObject");

///////////////////////////////////////////////////////////////////////////////
//
// CStatusKeeper
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CStatusKeeper::CStatusKeeper(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CStatusKeeper
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CStatusKeeper::~CStatusKeeper(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// GetScale
//
///////////////////////////////////////////////////////////////////////////////

const C4DVector3& CStatusKeeper::getScale() const
{
	//Return result.
	return attributes[ORIGIN].scale;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPosition
//
///////////////////////////////////////////////////////////////////////////////

const C4DVector3& CStatusKeeper::getPosition() const
{
	//Return result.
	return attributes[ORIGIN].position;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetRotation
//
///////////////////////////////////////////////////////////////////////////////

const C4DQuaternion& CStatusKeeper::getRotation() const
{
	//Return result.
	return attributes[ORIGIN].rotation;
}

///////////////////////////////////////////////////////////////////////////////
//
// RecoverOrigin
//
///////////////////////////////////////////////////////////////////////////////

void CStatusKeeper::recoverOrigin(_OBJECT object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Recover scale.
	OBJECT_INSTANCE(object)->setScale(attributes[ORIGIN].scale);
	//Recover position.
	OBJECT_INSTANCE(object)->setPosition(attributes[ORIGIN].position);
	//Recover rotation.
	OBJECT_INSTANCE(object)->setRotation(attributes[ORIGIN].rotation);
}

///////////////////////////////////////////////////////////////////////////////
//
// KeepOrigin
//
///////////////////////////////////////////////////////////////////////////////

void CStatusKeeper::keepOrigin(_OBJECT object,_LONG timestamp)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set timestamp.
	attributes[ORIGIN].timestamp = timestamp;
	//Clear omega.
	attributes[ORIGIN].omega = C4DVector3(0.0f,0.0f,0.0f);
	//Clear velocity.
	attributes[ORIGIN].velocity = C4DVector3(0.0f,0.0f,0.0f);
	//Keep scale.
	attributes[ORIGIN].scale = OBJECT_INSTANCE(object)->getScale();
	//Keep position.
	attributes[ORIGIN].position = OBJECT_INSTANCE(object)->getPosition();
	//Keep rotation.
	attributes[ORIGIN].rotation = OBJECT_INSTANCE(object)->getRotation();

	//Copy status.
	attributes[LAST_1] = attributes[LAST_0] = attributes[ORIGIN];
}

///////////////////////////////////////////////////////////////////////////////
//
// KeepCurrent
//
///////////////////////////////////////////////////////////////////////////////

void CStatusKeeper::keepCurrent(_OBJECT object,_LONG timestamp)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Get timespan.
	float timespan = (float)(timestamp - attributes[LAST_0].timestamp) / 1000000.0f;
	//Check value.
	if(timespan <= 0.0f) return;

	//Set velocity.
	attributes[LAST_0].velocity = (OBJECT_INSTANCE(object)->getPosition() - attributes[LAST_0].position) / timespan;
	//Set velocity.
	OBJECT_INSTANCE(object)->setVelocity(attributes[LAST_0].velocity);

	//Calculate omega.
	attributes[LAST_0].omega = (OBJECT_INSTANCE(object)->getRotation().eular() - attributes[LAST_0].rotation.eular()) / timespan;
	//Set omega.
	OBJECT_INSTANCE(object)->setOmega(attributes[LAST_0].omega);

	//Get timestamp.
	timespan = (float)(attributes[LAST_0].timestamp - attributes[LAST_1].timestamp) / 1000000.0f;
	//Check result.
	if(timespan > 0.0f)
	{
		//Get acceleration.
		C4DVector3 acceleration = (attributes[LAST_0].velocity - attributes[LAST_1].velocity) / timespan;
		//Set acceleration.
		OBJECT_INSTANCE(object)->setAcceleration(acceleration);
		//Set force.
		OBJECT_INSTANCE(object)->setForce(acceleration * OBJECT_INSTANCE(object)->getMass());

		//Get alpha.
		C4DVector3 alpha = (attributes[LAST_0].omega - attributes[LAST_1].omega) / timespan;
		//Set acceleration.
		OBJECT_INSTANCE(object)->setAlpha(alpha);
		//Get inertia.
		C4DVector3 inertia = OBJECT_INSTANCE(object)->getInertia();
		//Set torque.
		OBJECT_INSTANCE(object)->setTorque(C4DVector3(alpha.x() * inertia.x(),alpha.y() * inertia.y(),alpha.z() * inertia.z()));
	}

	//Move first one to the second one.
	attributes[LAST_1] = attributes[LAST_0];
	//Set timestamp.
	attributes[LAST_0].timestamp = timestamp;
	//Keep scale.
	attributes[LAST_0].scale = OBJECT_INSTANCE(object)->getScale();
	//Keep position.
	attributes[LAST_0].position = OBJECT_INSTANCE(object)->getPosition();
	//Keep rotation.
	attributes[LAST_0].rotation = OBJECT_INSTANCE(object)->getRotation();
}
