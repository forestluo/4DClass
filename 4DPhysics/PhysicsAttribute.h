///////////////////////////////////////////////////////////////////////////////
//
// PhysicsAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_ATTRIBUTE_H_
#define _PHYSICS_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsAttribute
{
private:

	/**
	 * Mass.
	 */
	_FLOAT mass;
	/**
	 * Moment of inertia.
	 */
	C4DVector3 inertia;

public:
	CPhysicsAttribute(void);
	CPhysicsAttribute(const CPhysicsAttribute& attribute);
	virtual ~CPhysicsAttribute(void);

	CPhysicsAttribute& operator = (const CPhysicsAttribute& attribute);

public:

	/**
	 * Get mass.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Mass of object.</p>
	 */
	_FLOAT getMass() const;
	/**
	 * Set mass.
	 *
	 * @param mass Mass of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMass(_FLOAT mass);

	/**
	 * Get inertia.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Inertia of object.</p>
	 */
	const C4DVector3& getInertia() const;
	/**
	 * Set inertia.
	 *
	 * @param inertia Inertia of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setInertia(const C4DVector3& inertia);

};

////////////////////////////////////////////////////////////////////////////////
#endif //_PHYSICS_ATTRIBUTE_H_
