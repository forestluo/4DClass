///////////////////////////////////////////////////////////////////////////////
//
// PhysicsApplication.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MANAGER_INSTANCE(p)									((CPhysicsManager *)(p))
#define COLLISION_BODY(p)									((const NewtonBody *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsApplication
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CPhysicsApplication::CPhysicsApplication(void)
{
	//Set default value.
	physicsManager = _NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CPhysicsApplication
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CPhysicsApplication::~CPhysicsApplication(void)
{
	//Check physics manager.
	if(physicsManager != _NULL)
	{
		//Delete physics manager.
		delete (CPhysicsManager *)physicsManager;
		//Clear physics manager.
		physicsManager = (CPhysicsManager *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Startup
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::startup(const CD3DXScene* scene)
{
#ifdef _DEBUG
	assert(scene != _NULL);
	assert(physicsManager == _NULL);
#endif

	//Open lock.
	openLock();
	{
#ifdef _DEBUG
		assert(physicsManager == _NULL);
#endif
		//Create physics manager.
		physicsManager = new CPhysicsManager();
#ifdef _DEBUG
		assert(physicsManager != _NULL);
#endif	
		//Add scene.
		addScene(scene);
		//Begin simulation.
		MANAGER_INSTANCE(physicsManager)->physicsBegin();
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// Shutdown
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::shutdown()
{
#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif

	//Open lock.
	openLock();
	{
#ifdef _DEBUG
		assert(physicsManager != _NULL);
#endif
		//End of physics.
		MANAGER_INSTANCE(physicsManager)->physicsEnd();

		//Delete physics manager.
		delete (CPhysicsManager *)physicsManager;
		//Clear physics manager.
		physicsManager = (CPhysicsManager *)_NULL;
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// DoSimulation
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::doSimulation()
{
	//Check physics manager.
	if(physicsManager != _NULL)
	{
		//Do simulation.
		MANAGER_INSTANCE(physicsManager)->doSimulation();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// IsRunning
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CPhysicsApplication::isRunning()
{
	//Value.
	_BOOL value;
	//Open lock.
	openLock();
	{
		//Check physics manager.
		value = physicsManager != _NULL ? _TRUE : _FALSE;
	}
	//Close lock.
	closeLock();
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// AddScene
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::addScene(const CD3DXScene* scene)
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(scene != _NULL);
	assert(physicsManager != _NULL);
#endif

	//Get enumeration.
	scene->getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get element.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check result.
		if(object->isPhysicsObject())
		{
			//Get physics object.
			CPhysicsObject* physicsObject 
				= (CPhysicsObject *)(object->getPhysics());
#ifdef _DEBUG
			assert(physicsObject != _NULL);
#endif
			//Check type.
			if(object->isPrimitiveObject())
			{
				//Add primitive object.
				MANAGER_INSTANCE(physicsManager)->addEntity((CPhysicsPrimitiveObject *)physicsObject);
			}
			else if(object->isCompoundObject())
			{
				//Add compound object.
				MANAGER_INSTANCE(physicsManager)->addEntity((CPhysicsCompoundObject *)physicsObject);
			}
		}
	}

	//Get enumeration.
	scene->getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get element.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check result.
		if(object->isPhysicsObject())
		{
			//Get physics object.
			CPhysicsObject* physicsObject 
				= (CPhysicsObject *)(object->getPhysics());
#ifdef _DEBUG
			assert(physicsObject != _NULL);
#endif
			//Check type.
			if(object->isJointObject())
			{
				//Get physics joint object.
				CPhysicsJointObject* physicsJoint = (CPhysicsJointObject *)physicsObject;
				//Only the valid joint can take part in a simulation.
				if(physicsJoint->isPhysicsValid()) MANAGER_INSTANCE(physicsManager)->addJoint(physicsJoint);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetForce
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::setForce(CPhysicsObject* object,const C4DVector3& force)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Get body.
	MANAGER_INSTANCE(physicsManager)->setForce(object,force);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetVelocity
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::setVelocity(CPhysicsObject* object,const C4DVector3& velocity)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Get body.
	MANAGER_INSTANCE(physicsManager)->setVelocity(object,velocity);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetPosition
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::setPosition(CPhysicsObject* object,const C4DVector3& position)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Get body.
	MANAGER_INSTANCE(physicsManager)->setPosition(object,position);
}

/////////////////////////////////////////////////////////////////////////////////
//
// IsControlled
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CPhysicsApplication::isControlled(CPhysicsObject* object)
{
	//Value.
	_BOOL value = _FALSE;
	//Open lock.
	openLock();
	{
		//Check physics manager.
		if(physicsManager != _NULL)
		{
			//Pick body.
			value = MANAGER_INSTANCE(physicsManager)->isControlled(object);
		}
	}
	//Close lock.
	closeLock();
	//Return result.
	return value;
}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearController
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::clearController(CPhysicsObject* object)
{
	//Open lock.
	openLock();
	{
		//Check physics manager.
		if(physicsManager != _NULL)
		{
			//Pick body.
			MANAGER_INSTANCE(physicsManager)->clearController(object);
		}
	}
	//Close lock.
	closeLock();
}

/////////////////////////////////////////////////////////////////////////////////
//
// PickBody
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::pickBody(CPhysicsObject* object,const C4DVector3& point)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Open lock.
	openLock();
	{
		//Check physics manager.
		if(physicsManager != _NULL)
		{
			//Pick body.
			MANAGER_INSTANCE(physicsManager)->pickBody(object,point);
		}
	}
	//Close lock.
	closeLock();
}

/////////////////////////////////////////////////////////////////////////////////
//
// MoveBody
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsApplication::moveBody(CPhysicsObject* object,const C4DVector3& direction)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Open lock.
	openLock();
	{
		//Check physics manager.
		if(physicsManager != _NULL)
		{
			//Move body.
			MANAGER_INSTANCE(physicsManager)->moveBody(object,direction);
		}
	}
	//Close lock.
	closeLock();
}