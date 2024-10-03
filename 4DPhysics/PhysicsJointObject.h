///////////////////////////////////////////////////////////////////////////////
//
// PhysicsJointObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_JOINT_OBJECT_H_
#define _PHYSICS_JOINT_OBJECT_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsObject.h"
#include "WorldJointObject.h"
#include "JointForceAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsJointObject
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsJointObject :
	public CPhysicsObject,
	public CJointForceAttribute,
	public virtual CWorldJointObject
{
public:
	CPhysicsJointObject(_INTEGER jointType);
	CPhysicsJointObject(const CJointAttribute& attribute);
	virtual ~CPhysicsJointObject(void);

public:

	/**
	 * Whether joint object is valid.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if joint is valid for physics simulation.</p>
	 */
	_BOOL isPhysicsValid() const;

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
	 * Get relative direction.
	 *
	 * <p>Relative direction of child or parent.
	 * This will keep as a constant value when simulation is running.</p>
	 *
	 * @param childFlag Whether is child or not (or parent).
	 * @return
	 *     <p>Relative direction of child or parent.</p>
	 */
	C4DVector3 getRelativeDirection(_BOOL childFlag) const;

};

///////////////////////////////////////////////////////////////////////////////
#endif //_PHYSICS_JOINT_OBJECT_H_
