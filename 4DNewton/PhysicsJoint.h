///////////////////////////////////////////////////////////////////////////////
//
// PhysicsJoint.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_JOINT_H_
#define _PHYSICS_JOINT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsJointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsJoint
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsJoint
{
	friend class CPhysicsManager;

protected:
	/**
	 * Joint.
	 */
	_OBJECT joint;
	/**
	 * Joint object.
	 *
	 * <p>The world object attached with the entity.</p>
	 */
	CPhysicsJointObject* object;

public:
	CPhysicsJoint(void);
	virtual ~CPhysicsJoint(void);

protected:

	/**
	 * Destroy.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void destroy();

	/**
	 * Set callbacks.
	 *
	 * @param joint Joint.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setCallbacks(_OBJECT joint);

	/**
	 * Set limits of joint.
	 *
	 * @param joint Joint.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setLimits(_OBJECT joint);

	/**
	 * Create joint.
	 *
	 * @param manager Physics manager.
	 * @return
	 *     <p>Created joint.</p>
	 */
	virtual _OBJECT createJoint(CPhysicsManager* manager) = 0;

protected:

	/**
	 * Get physics child.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Physics child.</p>
	 */
	CPhysicsObject* getPhysicsChild() const;

	/**
	 * Get physics parent.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Physics parent.</p>
	 */
	CPhysicsObject* getPhysicsParent() const;

public:

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
	virtual _BOOL attachObject(CPhysicsManager* manager,CPhysicsJointObject* object);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_PHYSICS_JOINT_H_
