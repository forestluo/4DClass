///////////////////////////////////////////////////////////////////////////////
//
// SimpleSphere.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SIMPLE_SPHERE_H_
#define _SIMPLE_SPHERE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DMatrix4.h"
#include "SimpleBox.h"

///////////////////////////////////////////////////////////////////////////////
//
// Declaration
//
///////////////////////////////////////////////////////////////////////////////

class C4DMatrix4;
class CSimpleBox;

///////////////////////////////////////////////////////////////////////////////
//
// SimpleSphere
//
///////////////////////////////////////////////////////////////////////////////

class CSimpleSphere
{
private:
	/**
	 * Radius
	 */
	_FLOAT radius;
	/**
	 * Center
	 */
	_FLOAT3 center;

public:
	CSimpleSphere(void);
	CSimpleSphere(_FLOAT x,_FLOAT y,_FLOAT z,_FLOAT radius);
	virtual ~CSimpleSphere(void);

	_FLOAT& x();
	_FLOAT x() const;
	_FLOAT& y();
	_FLOAT y() const;
	_FLOAT& z();
	_FLOAT z() const;
	_FLOAT& r();
	_FLOAT r() const;

	void normalize();

public:
	/**
	 * Get radius.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Radius of sphere.</p>
	 */
	_FLOAT getRadius();

	/**
	 * Set radius.
	 *
	 * @param radius Radius of sphere.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRadius(_FLOAT radius);

	/**
	 * Get center.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Coordination of center.</p>
	 */
	_FLOAT* getCenter();

	/**
	 * Set center.
	 *
	 * @param center Coordinate of center.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setCenter(_FLOAT* center);

public:

	/**
	 * Fuse another sphere into one.
	 *
	 * @param another Another sphere.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void fuse(const CSimpleSphere* another);

	/**
	 * Set sphere.
	 *
	 * @origin Original box.
	 * @world World matrix.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSphere(const CSimpleBox* origin,const C4DMatrix4* world = (C4DMatrix4 *)_NULL);

	/**
	 * Set sphere.
	 *
	 * @origin Original sphere.
	 * @world World matrix.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSphere(const CSimpleSphere* origin,const C4DMatrix4* world = (C4DMatrix4 *)_NULL);

public:

	/**
	 * Dump.
	 * 
	 * @param None No parameters needed.)
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dump();

	/**
	 * Recycle.
	 *
	 * <p>Recycle this sphere.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void recycle();

	/**
	 * Create.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Mallocated object.</p>
	 */
	static CSimpleSphere* create();
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SIMPLE_SPHERE_H_
