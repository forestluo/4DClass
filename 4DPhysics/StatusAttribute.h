///////////////////////////////////////////////////////////////////////////////
//
// StatusAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _STATUS_ATTRIBUTE_H_
#define _STATUS_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"
#include "4DQuaternion.h"

///////////////////////////////////////////////////////////////////////////////
//
// StatusAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CStatusAttribute
{
	friend class CStatusKeeper;

private:

	/**
	 * Timestamp.
	 */
	_LONG timestamp;
	/**
	 * Omega.
	 */
	C4DVector3 omega;
	/**
	 * Velocity.
	 */
	C4DVector3 velocity;

	/**
	 * Scale.
	 */
	C4DVector3 scale;
	/**
	 * Position.
	 */
	C4DVector3	position;
	/**
	 * Rotation.
	 */
	C4DQuaternion rotation;

public:
	CStatusAttribute(void);
	CStatusAttribute(const CStatusAttribute& attribute);
	virtual ~CStatusAttribute(void);

	CStatusAttribute& operator = (const CStatusAttribute& attribute);

public:

	/**
	 * Get scale.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Scale of object.</p>
	 */
	const C4DVector3& getScale() const;
	/**
	 * Set scale.
	 *
	 * @param scale Scale of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setScale(const C4DVector3& scale);

	/**
	 * Get position.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Position of object.</p>
	 */
	const C4DVector3& getPosition() const;
	/**
	 * Set position.
	 *
	 * @param position Vector of position.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPosition(const C4DVector3& position);

	/**
	 * Get rotation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Rotation of object.</p>
	 */
	const C4DQuaternion& getRotation() const;
	/**
	 * Set rotation.
	 *
	 * @param rotation Rotation of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRotation(const C4DQuaternion& rotation);

};

////////////////////////////////////////////////////////////////////////////////
#endif //_STATUS_ATTRIBUTE_H_
