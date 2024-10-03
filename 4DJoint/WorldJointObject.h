///////////////////////////////////////////////////////////////////////////////
//
// WorldJointObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _WORLD_JOINT_OBJECT_H_
#define _WORLD_JOINT_OBJECT_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldObject.h"
#include "JointAttribute.h"
#include "JointRelationAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// WorldJointObject
//
///////////////////////////////////////////////////////////////////////////////

class CWorldJointObject :
	public virtual CWorldObject,
	protected CJointAttribute, public CJointRelationAttribute
{
public:
	CWorldJointObject(_INTEGER jointType);
	CWorldJointObject(const CJointAttribute& attribute);
	virtual ~CWorldJointObject(void);

public:

	/**
	 * Get type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of primitive.</p>
	 */
	_INTEGER getJointType() const;

	/**
	 * Joint attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>A reference of joint attribute.</p>
	 */
	CJointAttribute& getJointAttribute();

	/**
	 * Get joint attribute.
	 *
	 * @param attribute Joint attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	const CJointAttribute& getJointAttribute() const;

public:

	/**
	 * Get major direction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Major direction.</p>
	 */
	C4DVector3 getMajorDirection() const;

	/**
	 * Set major direction.
	 *
	 * @param direction Major direction.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMajorDirection(const C4DVector3& direction);

public:

	/**
	 * Get minor direction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Minor direction.</p>
	 */
	C4DVector3 getMinorDirection() const;

	/**
	 * Set minor direction.
	 *
	 * @param direction Minor direction.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMinorDirection(const C4DVector3& direction);

public:

	/**
	 * Whether is self collision.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is self collision.</p>
	 */
	_BOOL isSelfCollision() const;
	/**
	 * Set self collision.
	 *
	 * @param selfCollision Whether is self collision.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSelfCollision(_BOOL selfCollision);

public:

	/**
	 * Get default major direction.
	 *
	 * @param jointType Type of joint.
	 * @return
	 *     <p>Major direction.</p>
	 */
	static C4DVector3 getDefaultMajorDirection(_INTEGER jointType);

	/**
	 * Get default minor direction.
	 *
	 * @param jointType Type of joint.
	 * @return
	 *     <p>Minor direction.</p>
	 */
	static C4DVector3 getDefaultMinorDirection(_INTEGER jointType);

	/**
	 * Get default joint direction.
	 *
	 * @param jointType Type of joint.
	 * @return
	 *     <p>Default attribute.</p>
	 */
	static CJointAttribute getDefaultAttribute(_INTEGER jointType);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_WORLD_JOINT_OBJECT_H_
