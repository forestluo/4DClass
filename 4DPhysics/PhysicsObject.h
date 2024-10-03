///////////////////////////////////////////////////////////////////////////////
//
// PhysicsObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_OBJECT_H_
#define _PHYSICS_OBJECT_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldObject.h"

#include "StatusKeeper.h"
#include "StatusAttribute.h"

#include "ForceAttribute.h"
#include "PhysicsAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsObject
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsObject :
	public virtual CWorldObject,
	public CForceAttribute,	public CPhysicsAttribute
{
private:

	/**
	 * Status keeper.
	 */
	CStatusKeeper* keeper;

public:
	CPhysicsObject(void);
	virtual ~CPhysicsObject(void);

public:

	/**
	 * Physics end.
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void physicsEnd();

	/**
	 * Paragram end.
	 *
	 * @param timestamp Timestamp of paragram.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void paragramEnd(_LONG timestamp);

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
	 * Get status keeper.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	CStatusKeeper* getKeeper() const;

public:

	/**
	 * Calculate accompany vector.
	 *
	 * <p>When an object is rotated, the accompany vector will rotate with it also.
	 * The accompany vector is the rotated vector in the world.</p>
	 *
	 * @param vector Original vector in world before rotation begins.
	 * @return
	 *     <p>An accompany vector in world.</p>
	 */
	C4DVector3 getRotationAccompany(const C4DVector3& vector) const;

};

///////////////////////////////////////////////////////////////////////////////
#endif //_PHYSICS_OBJECT_H_
