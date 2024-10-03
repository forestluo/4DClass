///////////////////////////////////////////////////////////////////////////////
//
// PhysicsCustomJoint.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_CUSTOM_JOINT_H_
#define _PHYSICS_CUSTOM_JOINT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsJoint.h"
#include "NewtonPhysics.h"

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsCustomJoint
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsCustomJoint : public CPhysicsJoint
{
	friend class CPhysicsManager;

	friend void DestroyCustomJointCallback(const NewtonUserJoint* joint);

public:
	CPhysicsCustomJoint(void);
	virtual ~CPhysicsCustomJoint(void);

protected:

	/**
	 * Set callbacks.
	 *
	 * @param joint Joint.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setCallbacks(_OBJECT joint);

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
#endif //_PHYSICS_CUSTOM_JOINT_H_
