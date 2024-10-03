///////////////////////////////////////////////////////////////////////////////
//
// JointForceAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _JOINT_FORCE_ATTRIBUTE_H_
#define _JOINT_FORCE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// JointForceAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CJointForceAttribute
{
private:
	/**
	 * Force.
	 */
	C4DVector3 force;

	/**
	 * Angle.
	 */
	C4DVector3 angle;
	/**
	 * Omega.
	 */
	C4DVector3 omega;

	/**
	 * Position.
	 */
	C4DVector3 position;
	/**
	 * Velocity.
	 */
	C4DVector3 velocity;

public:
	CJointForceAttribute(void);
	virtual ~CJointForceAttribute(void);

public:

	/**
	 * Get joint force.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Force of joint.</p>
	 */
	const C4DVector3& getJointForce() const;

	/**
	 * Get angle.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Relative angle.</p>
	 */
	const C4DVector3& getRelativeAngle() const;

	/**
	 * Get omega.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Relative omega.</p>
	 */
	const C4DVector3& getRelativeOmega() const;

	/**
	 * Get position.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Relative position.</p>
	 */
	const C4DVector3& getRelativePosition() const;

	/**
	 * Get velocity.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Relative velocity.</p>
	 */
	const C4DVector3& getRelativeVelocity() const;

public:

	/**
	 * Set joint force.
	 *
	 * @param angle Relative angle.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setJointForce(const C4DVector3& force);

	/**
	 * Set angle.
	 *
	 * @param angle Relative angle.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRelativeAngle(const C4DVector3& angle);

	/**
	 * Set omega.
	 *
	 * @param omega Relative of angle.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRelativeOmega(const C4DVector3& omega);

	/**
	 * Set position.
	 *
	 * @param position Relative position.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRelativePosition(const C4DVector3& position);

	/**
	 * Set velocity.
	 *
	 * @param velocity Relative velocity.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRelativeVelocity(const C4DVector3& velocity);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_JOINT_FORCE_ATTRIBUTE_H_
