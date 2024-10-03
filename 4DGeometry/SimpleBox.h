///////////////////////////////////////////////////////////////////////////////
//
// SimpleBox.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SIMPLE_BOX_H_
#define _SIMPLE_BOX_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DMatrix4.h"

///////////////////////////////////////////////////////////////////////////////
//
// Declaration
//
///////////////////////////////////////////////////////////////////////////////

class C4DMatrix4;

///////////////////////////////////////////////////////////////////////////////
//
// SimpleBox
//
///////////////////////////////////////////////////////////////////////////////

class CSimpleBox
{
private:
	/**
	 * Center
	 */
	_FLOAT3 center;
	/**
	 * Extent
	 */
	_FLOAT3 extents;

public:
	CSimpleBox(void);
	CSimpleBox(_FLOAT x,_FLOAT y,_FLOAT z,_FLOAT dx,_FLOAT dy,_FLOAT dz);
	virtual ~CSimpleBox(void);

	_FLOAT& x();
	_FLOAT x() const;
	_FLOAT& y();
	_FLOAT y() const;
	_FLOAT& z();
	_FLOAT z() const;

	_FLOAT& dx();
	_FLOAT dx() const;
	_FLOAT& dy();
	_FLOAT dy() const;
	_FLOAT& dz();
	_FLOAT dz() const;

	_FLOAT xmin() const;
	_FLOAT ymin() const;
	_FLOAT zmin() const;
	_FLOAT xmax() const;
	_FLOAT ymax() const;
	_FLOAT zmax() const;

	void normalize();

public:
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

	/**
	 * Get extents.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Coordination of extents.</p>
	 */
	_FLOAT* getExtents();

	/**
	 * Set extents.
	 *
	 * @param extend Coordinate of extents.
	 * @return
	 *     <p>No results extents.</p>
	 */
	void setExtents(_FLOAT* extend);

public:

	/**
	 * Fuse another sphere into one.
	 *
	 * @param another Another sphere.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void fuse(const CSimpleBox* another);

	/**
	 * Rand a box.
	 *
	 * @param box Box limitation.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void randBox(const CSimpleBox* box = (CSimpleBox *)_NULL);

	/**
	 * Set box.
	 *
	 * @origin Original box.
	 * @world World matrix.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setBox(const CSimpleBox* origin,const C4DMatrix4* world = (C4DMatrix4 *)_NULL);

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
	static CSimpleBox* create();
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SIMPLE_BOX_H_
