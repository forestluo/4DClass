///////////////////////////////////////////////////////////////////////////////
//
// JointManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _JOINT_MANAGER_H_
#define _JOINT_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsWorld.h"
#include "PhysicsObject.h"
#include "PhysicsJointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// JointManager
//
///////////////////////////////////////////////////////////////////////////////

class CJointManager :
	public virtual CPhysicsWorld
{
private:
	/**
	 * Joints.
	 */
	_OBJECT joints;

public:
	CJointManager(void);
	virtual ~CJointManager(void);

private:

	/**
	 * Release all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void releaseAll();

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

public:

	/**
	 * Destroy joint.
	 *
	 * @param joint Joint object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void destroyJoint(_OBJECT joint);

public:

	/**
	 * Create up-vector joint.
	 *
	 * @param direction Major direction of joint.
	 * @param child Child object of joint.
	 * @return
	 *     <p>Created universal joint.</p>
	 */
	_OBJECT createUpVectorJoint(const C4DVector3& direction,
									CPhysicsObject* child);

	/**
	 * Create ball joint.
	 *
	 * @param position Position of joint.
	 * @param child Child object of joint.
	 * @param parent Parent object of joint.
	 * @return
	 *     <p>Created ball joint.</p>
	 */
	_OBJECT createBallJoint(const C4DVector3& position,
								CPhysicsObject* child,CPhysicsObject* parent = (CPhysicsObject *)_NULL);

	/**
	 * Create hinge joint.
	 *
	 * @param position Position of joint.
	 * @param direction Direction of joint.
	 * @param child Child object of joint.
	 * @param parent Parent object of joint.
	 * @return
	 *     <p>Created hinge joint.</p>
	 */
	_OBJECT createHingeJoint(const C4DVector3& position,const C4DVector3& direction,
								CPhysicsObject* child,CPhysicsObject* parent = (CPhysicsObject *)_NULL);

	/**
	 * Create slider joint.
	 *
	 * @param position Position of joint.
	 * @param direction Direction of joint.
	 * @param child Child object of joint.
	 * @param parent Parent object of joint.
	 * @return
	 *     <p>Created slider joint.</p>
	 */
	_OBJECT createSliderJoint(const C4DVector3& position,const C4DVector3& direction,
								CPhysicsObject* child,CPhysicsObject* parent = (CPhysicsObject *)_NULL);

	/**
	 * Create corkscrew joint.
	 *
	 * @param position Position of joint.
	 * @param direction Direction of joint.
	 * @param child Child object of joint.
	 * @param parent Parent object of joint.
	 * @return
	 *     <p>Created corkscrew joint.</p>
	 */
	_OBJECT createCorkscrewJoint(const C4DVector3& position,const C4DVector3& direction,
									CPhysicsObject* child,CPhysicsObject* parent = (CPhysicsObject *)_NULL);

	/**
	 * Create universal joint.
	 *
	 * @param position Position of joint.
	 * @param direction0 Major direction of joint.
	 * @param direction1 Minor direction of joint.
	 * @param child Child object of joint.
	 * @param parent Parent object of joint.
	 * @return
	 *     <p>Created universal joint.</p>
	 */
	_OBJECT createUniversalJoint(const C4DVector3& position,const C4DVector3& direction0,const C4DVector3& direction1,
									CPhysicsObject* child,CPhysicsObject* parent = (CPhysicsObject *)_NULL);

public:

	/**
	 * Add joint.
	 *
	 * <p>Add joint for simulation.</p>
	 *
	 * @param object Joint object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addJoint(CPhysicsJointObject* object);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_JOINT_MANAGER_H_
