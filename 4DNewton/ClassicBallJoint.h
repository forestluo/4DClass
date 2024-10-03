///////////////////////////////////////////////////////////////////////////////
//
// ClassicBallJoint.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CLASSIC_BALL_JOINT_H_
#define _CLASSIC_BALL_JOINT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsClassicJoint.h"

///////////////////////////////////////////////////////////////////////////////
//
// ClassicBallJoint
//
///////////////////////////////////////////////////////////////////////////////

class CClassicBallJoint : public CPhysicsClassicJoint
{
	friend void ApplyBallCallBack(const NewtonJoint* ball,dFloat timestep);

public:
	CClassicBallJoint(void);
	virtual ~CClassicBallJoint(void);

public:

	/**
	 * Paragram end.
	 *
	 * @param timestamp Timestamp of paragram.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void paragramEnd(_LONG timestamp);

protected:

	/**
	 * Callback.
	 *
	 * @param joint Joint.
	 * @param timestep Timestep.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void callback(_OBJECT joint,_FLOAT timestep);

protected:

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
	virtual _OBJECT createJoint(CPhysicsManager* manager);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_CLASSIC_BALL_JOINT_H_
