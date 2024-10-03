///////////////////////////////////////////////////////////////////////////////
//
// PhysicsManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "BodyManager.h"
#include "ShapeManager.h"
#include "JointManager.h"
#include "EntityManager.h"
#include "SimulationManager.h"
#include "InteractionManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsManager
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsManager :
	public CSimulationManager,
	public CInteractionManager,
	public CShapeManager, public CBodyManager,
	public CEntityManager, public CJointManager
{
	friend class CSimulationManager;

public:
	CPhysicsManager(void);
	virtual ~CPhysicsManager(void);

public:

	/**
	 * Physics end.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void physicsEnd();

	/**
	 * Physics begin.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void physicsBegin();

private:

	/**
	 * Paragram end.
	 *
	 * @param timestamp Timestamp of paragram.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void paragramEnd(_LONG timestamp);

	/**
	 * Set paragram.
	 *
	 * @param Interpolation param.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setParagram(_FLOAT interpolationParam);

public:

	/**
	 * Whether controlled.
	 *
	 * @param body A picked body.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_BOOL isControlled(CPhysicsObject* object);

	/**
	 * Clear controller.
	 *
	 * @param body A picked body.
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
#endif //_PHYSICS_MANAGER_H_
