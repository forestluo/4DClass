///////////////////////////////////////////////////////////////////////////////
//
// PhysicsApplication.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _PHYSICS_APPLICATION_H_
#define _PHYSICS_APPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXScene.h"

#include "4DLock.h"
#include "D3DXObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsApplication
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsApplication :
	public virtual C4DLock,
	public virtual CD3DXObject
{
private:
	/**
	 * Physics manager.
	 */
	_OBJECT physicsManager;

public:
	CPhysicsApplication(void);
	virtual ~CPhysicsApplication(void);

public:

	/**
	 * Shutdown.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void shutdown();

	/**
	 * Whether is running.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is running.</p>
	 */
	_BOOL isRunning();

protected:

	/**
	 * Do simulation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void doSimulation();

private:

	/**
	 * Add scene.
	 *
	 * @param scene Scene.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addScene(const CD3DXScene* scene);

protected:

	/**
	 * Startup.
	 *
	 * @param scene Scene.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void startup(const CD3DXScene* scene);

public:

	/** 
	 * Set force.
	 *
	 * @param object Physics object.
	 * @param force Force of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setForce(CPhysicsObject* object,const C4DVector3& force);

	/** 
	 * Set velocity.
	 *
	 * @param object Physics object.
	 * @param velocity Velocity of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setVelocity(CPhysicsObject* object,const C4DVector3& velocity);

	/** 
	 * Set position.
	 *
	 * @param object Physics object.
	 * @param position Position of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPosition(CPhysicsObject* object,const C4DVector3& position);

public:

	/**
	 * Whether was controlled.
	 *
	 * @param object Physics object.
	 * @return
	 *     <p>Return true, if it was controlled.</p>
	 */
	_BOOL isControlled(CPhysicsObject* object);

	/**
	 * Clear controller.
	 *
	 * @param object Physics object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearController(CPhysicsObject* object);
	
	/**
	 * Pick object by body pick controller.
	 *
	 * @param body A picked body.
	 * @param point Picked point.
	 * @param
	 *     <p>No results returned.</p>
	 */
	void pickBody(CPhysicsObject* object,const C4DVector3& point);

	/**
	 * Move object by body pick controller.
	 *
	 * @param body A picked body.
	 * @param direction Moving direction.
	 * @param
	 *     <p>No results returned.</p>
	 */
	void moveBody(CPhysicsObject* object,const C4DVector3& direction);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_PHYSICS_APPLICATION_H_
