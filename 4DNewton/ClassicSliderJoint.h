///////////////////////////////////////////////////////////////////////////////
//
// ClassicSliderJoint.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CLASSIC_SLIDER_JOINT_H_
#define _CLASSIC_SLIDER_JOINT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsClassicJoint.h"

///////////////////////////////////////////////////////////////////////////////
//
// ClassicSliderJoint
//
///////////////////////////////////////////////////////////////////////////////

class CClassicSliderJoint : public CPhysicsClassicJoint
{
	friend unsigned ApplySliderCallBack(const NewtonJoint* slider,NewtonHingeSliderUpdateDesc* desc);

public:
	CClassicSliderJoint(void);
	virtual ~CClassicSliderJoint(void);

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
	 * @param accel Acceleration.
	 * @param minFriction Minimum friction.
	 * @param maxFriction Maximum friction.
	 * @param timestep Timestep.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void callback(_OBJECT joint,_FLOAT accel,_FLOAT minFricition,_FLOAT maxFricition,_FLOAT timestep);

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
#endif //_CLASSIC_SLIDER_JOINT_H_
