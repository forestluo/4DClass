///////////////////////////////////////////////////////////////////////////////
//
// PhysicsManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NewtonPhysics.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsManager
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsManager::CPhysicsManager(void)
{
	//Set physics manager.
	CPhysicsWorld::physicsManager = this;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsManager::~CPhysicsManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsManager::paragramEnd(_LONG timestamp)
{
	//Call entities manager.
	CEntityManager::paragramEnd(timestamp);
	//Call joints manager.
	CJointManager::paragramEnd(timestamp);
}

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsEnd
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsManager::physicsEnd()
{
	//Clear controllers.
	CInteractionManager::clearControllers();
	//Call entities manager.
	CEntityManager::physicsEnd();
	//Call joints manager.
	CJointManager::physicsEnd();
}

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsBegin
//
///////////////////////////////////////////////////////////////////////////////
	
void CPhysicsManager::physicsBegin()
{
	//Get timestamp.
	_LONG timestamp = CPhysicsTime::getTimeInMicroseconds();
	//Call entities manager.
	CEntityManager::physicsBegin(timestamp);
	//Call joints manager.
	CJointManager::physicsBegin(timestamp);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetParagram
//
///////////////////////////////////////////////////////////////////////////////
	
void CPhysicsManager::setParagram(_FLOAT interpolationParam)
{
	//Set paragram.
	CEntityManager::setParagram(interpolationParam);
}

/////////////////////////////////////////////////////////////////////////////////
//
// IsControlled
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CPhysicsManager::isControlled(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//A joint object cannot be dragged.
	if(object->isJointObject()) return _FALSE;
	//A static object cannot be dragged.
	if(object->getMass() <= 0.0f) return _FALSE;
	//Get collision body.
	_OBJECT collisionBody = getCollisionBody(object);
	//Check result.
	//An object without collision body cannot be dragged.
	if(collisionBody == _NULL) return _FALSE;
	//Return result.
	return CInteractionManager::isControlled(collisionBody);
}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearController
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsManager::clearController(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//A joint object cannot be dragged.
	if(object->isJointObject()) return;
	//A static object cannot be dragged.
	if(object->getMass() <= 0.0f) return;
	//Get collision body.
	_OBJECT collisionBody = getCollisionBody(object);
	//Check result.
	//An object without collision body cannot be dragged.
	if(collisionBody == _NULL) return;
	//Clear controller.
	CInteractionManager::clearController(collisionBody);
}

/////////////////////////////////////////////////////////////////////////////////
//
// PickBody
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsManager::pickBody(CPhysicsObject* object,const C4DVector3& point)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//A joint object cannot be dragged.
	if(object->isJointObject()) return;
	//A static object cannot be dragged.
	if(object->getMass() <= 0.0f) return;
	//Get collision body.
	_OBJECT collisionBody = getCollisionBody(object);
	//Check result.
	//An object without collision body cannot be dragged.
	if(collisionBody == _NULL) return;
	//Pick body.
	CInteractionManager::pickBody(collisionBody,point);
}

/////////////////////////////////////////////////////////////////////////////////
//
// MoveBody
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsManager::moveBody(CPhysicsObject* object,const C4DVector3& direction)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//A joint object cannot be dragged.
	if(object->isJointObject()) return;
	//A static object cannot be dragged.
	if(object->getMass() <= 0.0f) return;
	//Get collision body.
	_OBJECT collisionBody = getCollisionBody(object);
	//Check result.
	//An object without collision body cannot be dragged.
	if(collisionBody == _NULL) return;
	//Move body.
	CInteractionManager::moveBody(collisionBody,direction);
}