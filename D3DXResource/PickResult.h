///////////////////////////////////////////////////////////////////////////////
//
// PickResult.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PICK_RESULT_H_
#define _PICK_RESULT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"
#include "PickIntersection.h"

///////////////////////////////////////////////////////////////////////////////
//
// PickResult
//
///////////////////////////////////////////////////////////////////////////////

class CPickResult
{
private:
	/**
	 * Pick results.
	 */
	_OBJECT picks;

	/**
	 * Origin.
	 */
    C4DVector3 pickOrigin;
	/**
	 * Direction.
	 */
    C4DVector3 pickDirection;

public:
	CPickResult(void);
	virtual ~CPickResult(void);

public:

	/**
	 * Release all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void releaseAll();

public:

	/**
	 * Get pick origin.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Vector of pick origin.</p>
	 */
	const C4DVector3& getPickOrigin() const;
	/** 
	 * Set pick origin.
	 *
	 * @param pickOrigin Pick origin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPickOrigin(const C4DVector3& pickOrigin);

	/**
	 * Get pick direction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Vector of pick direction.</p>
	 */
	const C4DVector3& getPickDirection() const;
	/** 
	 * Set pick direction.
	 *
	 * @param pickDirection Pick direction.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPickDirection(const C4DVector3& pickDirection);

public:

	/**
	 * Get count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of picks.</p>
	 */
	_INTEGER getCount() const;
	/**
	 * Get intersection.
	 *
	 * @param index Index of intersection.
	 * @return
	 *     <p>Pick intersection.</p>
	 */
	CPickIntersection* getIntersection(int nIndex) const;
	/**
	 * Add intersection.
	 *
	 * @param intersection Intersection.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addIntersection(CPickIntersection* intersection);

public:

	/**
	 * Get neareat intersection.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Pick intersection.</p>
	 */
	CPickIntersection* getNearestIntersection() const;
	/**
	 * Get intersection.
	 *
	 * @param alias Name of alias.
	 * @return
	 *    <p>Pick intersection.</p>
	 */
	CPickIntersection* getIntersection(const CNormalString& alias) const;
};

///////////////////////////////////////////////////////////////////////////////
#endif //_PICK_RESULT_H_
