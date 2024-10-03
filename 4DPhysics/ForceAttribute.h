///////////////////////////////////////////////////////////////////////////////
//
// ForceAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _FORCE_ATTRIBUTE_H_
#define _FORCE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// ForceAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CForceAttribute
{
private:

	/**
	 * Force.
	 */
	C4DVector3 force;
	/**
	 * Torque.
	 */
	C4DVector3 torque;

	/**
	 * Omega.
	 */
	C4DVector3 omega;
	/**
	 * Velocity.
	 */
	C4DVector3 velocity;

	/**
	 * Alpha.
	 */
	C4DVector3 alpha;
	/**
	 * Acceleration.
	 */
	C4DVector3 acceleration;

public:
	CForceAttribute(void);
	CForceAttribute(const CForceAttribute& attribute);
	virtual ~CForceAttribute(void);

	CForceAttribute& operator = (const CForceAttribute& attribute);

public:

	/**
	 * Get force.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Force of object.</p>
	 */
	const C4DVector3& getForce() const;
	/**
	 * Set force.
	 *
	 * @param force Force of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setForce(const C4DVector3& force);

	/**
	 * Get torque.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Torque of object.</p>
	 */
	const C4DVector3& getTorque() const;
	/**
	 * Set torque.
	 *
	 * @param torque Torque of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setTorque(const C4DVector3& torque);

	/**
	 * Get omega.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Omega of object.</p>
	 */
	const C4DVector3& getOmega() const;
	/**
	 * Set omega.
	 *
	 * @param omega Omega of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setOmega(const C4DVector3& omega);

	/**
	 * Get velocity.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Velocity of object.</p>
	 */
	const C4DVector3& getVelocity() const;
	/**
	 * Set velocity.
	 *
	 * @param velocity Velocity of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setVelocity(const C4DVector3& velocity);

	/**
	 * Get alpha.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Alpha of object.</p>
	 */
	const C4DVector3& getAlpha() const;
	/**
	 * Set alpha.
	 *
	 * @param alpha Alpha of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setAlpha(const C4DVector3& alpha);

	/**
	 * Get acceleration.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Acceleration of object.</p>
	 */
	const C4DVector3& getAcceleration() const;
	/**
	 * Set acceleration.
	 *
	 * @param acceleration Acceleration of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setAcceleration(const C4DVector3& acceleration);

};

////////////////////////////////////////////////////////////////////////////////
#endif //_FORCE_ATTRIBUTE_H_
