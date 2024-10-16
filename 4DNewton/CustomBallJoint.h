///////////////////////////////////////////////////////////////////////////////
//
// CustomBallJoint.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CUSTOM_BALL_JOINT_H_
#define _CUSTOM_BALL_JOINT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsCustomJoint.h"

///////////////////////////////////////////////////////////////////////////////
//
// CustomBallJoint
//
///////////////////////////////////////////////////////////////////////////////

class CCustomBallJoint : public CPhysicsCustomJoint
{
public:
	CCustomBallJoint(void);
	virtual ~CCustomBallJoint(void);

protected:

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
#endif //_CUSTOM_BALL_JOINT_H_
