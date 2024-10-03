///////////////////////////////////////////////////////////////////////////////
//
// EntityManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsWorld.h"
#include "PhysicsCompoundObject.h"
#include "PhysicsPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// EntityManager
//
///////////////////////////////////////////////////////////////////////////////

class CEntityManager :
	public virtual CPhysicsWorld
{
private:
	/**
	 * Entities.
	 */
	_OBJECT entities;

public:
	CEntityManager(void);
	virtual ~CEntityManager(void);

private:

	/**
	 * Release all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void releaseAll();

	/**
	 * Remove entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void removeEntity(CPhysicsObject* object);

protected:

	/**
	 * Paramgram end.
	 *
	 * @param timestamp Timestamp of paragram.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void paragramEnd(_LONG timestamp);

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
	 * @param timestamp Timestamp of paragram.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void physicsBegin(_LONG timestamp);

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
	 * Get collision body.
	 *
	 * @param object World object.
	 * @return
	 *     <p>Collision body.</p>
	 */
	_OBJECT getCollisionBody(CPhysicsObject* object);

public:

	/**
	 * Set force.
	 *
	 * @param object World object.
	 * @param force Force of entity.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setForce(CPhysicsObject* object,const C4DVector3& force);

	/**
	 * Set velocity.
	 *
	 * @param object World object.
	 * @param velocity Velocity of entity.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setVelocity(CPhysicsObject* object,const C4DVector3& velocity);

	/**
	 * Set position.
	 *
	 * @param object World object.
	 * @param position Position of entity.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPosition(CPhysicsObject* object,const C4DVector3& position);

public:

	/**
	 * Add box entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addBoxEntity(CPhysicsObject* object);

	/**
	 * Add cone entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addConeEntity(CPhysicsObject* object);

	/**
	 * Add capsule entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addCapsuleEntity(CPhysicsObject* object);

	/**
	 * Add chamfer cylinder entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addChamferCylinderEntity(CPhysicsObject* object);

	/**
	 * Add cylinder entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addCylinderEntity(CPhysicsObject* object);

	/**
	 * Add sphere entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addSphereEntity(CPhysicsObject* object);

	/**
	 * Add convex entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addConvexEntity(CPhysicsObject* object);

	/**
	 * Add mesh entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addMeshEntity(CPhysicsObject* object);

	/**
	 * Add height field entity.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addHeightFieldEntity(CPhysicsObject* object);

public:

	/**
	 * Add entity.
	 *
	 * <p>Add entity for simulation.</p>
	 *
	 * @param object Compound object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addEntity(CPhysicsCompoundObject* object);

	/**
	 * Add entity.
	 *
	 * <p>Add entity for simulation.</p>
	 *
	 * @param object Primitive object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addEntity(CPhysicsPrimitiveObject* object);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_ENTITY_MANAGER_H_
