///////////////////////////////////////////////////////////////////////////////
//
// PickIntersection.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PICK_INTERSECTION_H_
#define _PICK_INTERSECTION_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NormalString.h"

///////////////////////////////////////////////////////////////////////////////
//
// PickIntersection
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagPickIntersection
{
	//Mesh face that was intersected.
    _INTEGER dwFace;                 
	//Barycentric coords of intersection.
    _FLOAT fBary1, fBary2;         
	//Distance from ray origin to intersection.
    _FLOAT fDist;
	//Texture coords of intersection.
    _FLOAT tu, tv;

} PickIntersection;

///////////////////////////////////////////////////////////////////////////////
//
// PickIntersection
//
///////////////////////////////////////////////////////////////////////////////

class CPickIntersection
{
private:
	/**
	 * Alias of object.
	 */
	CNormalString alias;
	/**
	 * Intersections.
	 */
	_OBJECT intersections;

public:
	CPickIntersection(void);
	virtual ~CPickIntersection(void);

public:

	/**
	 * Get alias.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Name of alias.</p>
	 */
	const CNormalString& getAlias() const;
	/**
	 * Set alias.
	 *
	 * @param alias Name of alias.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setAlias(const CNormalString& alias);

public:

	/**
	 * Get nearest distance.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Nearest distance.</p>
	 */
	_FLOAT getNearestDistance() const;

public:

	/**
	 * Get count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of intersection.</p>
	 */
	_INTEGER getCount() const;
	/**
	 * Add intersection.
	 *
	 * @param intersection Intersection.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addIntersection(const PickIntersection& intersection);
	/**
	 * Get intersection.
	 *
	 * @param index Index of intersection.
	 * @return
	 *     <p>Intersection with specified index.</p>
	 */
	const PickIntersection& getIntersection(_INTEGER index) const;
};

///////////////////////////////////////////////////////////////////////////////
#endif //_PICK_INTERSECTION_H_
