///////////////////////////////////////////////////////////////////////////////
//
// PhysicsEntity.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_ENTITY_H_
#define _PHYSICS_ENTITY_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NewtonPhysics.h"

#include "PhysicsObject.h"
#include "PhysicsManager.h"

#include "ListNodeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsEntity
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsEntity
{
	friend class CEntityManager;

	friend void LeaveWorldCallback(const NewtonBody* body);
	friend void DestroyBodyCallback(const NewtonBody* body);
	friend void SetTransformCallback(const NewtonBody* body,const dFloat* matrix,int threadIndex);
	friend void ApplyForceAndTorqueCallback(const NewtonBody* body,dFloat timestep,int threadIndex);

protected:
	/**
	 * Physics object.
	 *
	 * <p>The basic object attached with the entity.</p>
	 */
	CPhysicsObject* object;

private:
	/**
	 * Mass
	 */
	_FLOAT mass;
	/**
	 * Newton body.
	 */
	_OBJECT collisionBody;

//These are the element to represent the position and orientation state of a graphics object in the world.
private:

	/** 
	 * Current force.
	 *
	 * <p>Current force of object.</p>
	 */
	dVector currentForce;

	/**
	 * Current position.
	 *
	 * <p>Position one physics simulation step in the future.</p>
	 */
	dVector currentPosition;
	/**
	 * Previous position.
	 *
	 * <p>Position at the current physics simulation step.</p>
	 */
	dVector previousPosition;

	/**
	 * Current rotation.
	 *
	 * <p>Rotation one physics simulation step in the future.</p>
	 */
	dQuaternion currentRotation;
	/**
	 * Previous position.
	 *
	 * <p>Rotation at the current physics simulation step.</p>
	 */
	dQuaternion previousRotation;

public:
	CPhysicsEntity(void);
	CPhysicsEntity(_FLOAT mass);
	virtual ~CPhysicsEntity(void);

protected:

	/**
	 * Paragram end.
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

private:

	/**
	 * Set paragram.
	 *
	 * @param Interpolation param.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setParagram(dFloat interpolationParam);

protected:

	/**
	 * Get body.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Body object.</p>
	 */
	_OBJECT getBody();

	/**
	 * Apply force and torque.
	 * 
	 * <p>It was called by the physics system.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void apply();

	/**
	 * Leave.
	 * 
	 * <p>It was called by the physics system.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void leave();

	/**
	 * On destroy.
	 *
	 * <p>It was called when being destroyed.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void destroy();

	/**
	 * On transform.
	 * 
	 * <p>It was called by the physics system.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void transform(const dFloat* matrix);

	/**
	 * Get bounding box.
	 *
	 * <p>Get original bounding box of entity.</p>
	 *
	 * @param minBox Minimum box.
	 * @param maxBox Maximum box.
	 * @return
	 *     <p>Box of entity.</p>
	 */
	void getBoundingBox(dVector& minBox,dVector& maxBox);

	/**
	 * Create shape.
	 *
	 * @param manager Physics manager.
	 * @param shapes Shapes of compound.
	 * @return
	 *     <p>Created shape.</p>
	 */
	virtual _OBJECT createShape(CPhysicsManager *manager,
								CListNodeContainer& shapes) = 0;

	/**
	 * Initialize body.
	 *
	 * @param manager Physics manager.
	 * @param shape Collision shape.
	 * @return
	 *     <p>Initialize body.</p>
	 */
	virtual void initialize(CPhysicsManager *manager,_OBJECT shape);

public:

	/** 
	 * Set force.
	 *
	 * @param force Force of body.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setForce(const C4DVector3& force);

	/** 
	 * Set velocity.
	 *
	 * @param velocity Velocity of body.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setVelocity(const C4DVector3& velocity);

	/** 
	 * Set position.
	 *
	 * @param position Position of body.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPosition(const C4DVector3& position);

public:

	/**
	 * Detach object.
	 *
	 * @param manager Physics manager.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void detachObject(CPhysicsManager* manager);

	/**
	 * Attach object.
	 *
	 * @param manager Physics manager.
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual _BOOL attachObject(CPhysicsManager* manager,CPhysicsObject* object);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_PHYSICS_ENTITY_H_
