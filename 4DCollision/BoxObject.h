///////////////////////////////////////////////////////////////////////////////
//
// BoxObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _BOX_OBJECT_H_
#define _BOX_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "SimpleBox.h"
#include "SimpleSphere.h"

#include "WorldObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// BoxObject
//
///////////////////////////////////////////////////////////////////////////////

class CBoxObject
{
private:
	/**
	 * Axis aligned box.
	 */
	CSimpleBox* box;
	/**
	 * Sphere box.
	 */
	CSimpleSphere* sphere;

public:
	CBoxObject(void);
	virtual ~CBoxObject(void);

public:

	/**
	 * Whether is single.
	 * 
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is single.</p>
	 */
	virtual _BOOL isSingle() = 0;

	/**
	 * Clear all of object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearAll();

	/**
	 * Get toal count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Total count of object.
	 *	   Including its children.</p>
	 */
	virtual _INTEGER getTotalCount() = 0;

	/**
	 * Clear axis aligned box.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearBox();

	/**
	 * Get axis aligned box.
	 * 
	 * @param None No parameters needed.
	 * @return
	 *     <p>Sphere of box.</p>
	 */
	CSimpleBox* getBox();

	/**
	 * Set axis aligned box.
	 * 
	 * @param box Axis aligned box.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setBox(CSimpleBox* box);

	/**
	 * Clear sphere.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearSphere();

	/**
	 * Get sphere.
	 * 
	 * @param None No parameters needed.
	 * @return
	 *     <p>Sphere of box.</p>
	 */
	CSimpleSphere* getSphere();

	/**
	 * Set sphere.
	 * 
	 * @param sphere Sphere.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSphere(CSimpleSphere* sphere);

public:

	/**
	 * Dump.
	 *
	 * @param None No parameters needed.
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
	virtual void recycle() = 0;

public:

	/**
	 * Get box object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>A box object.</p>
	 */
	static CBoxObject* getBoxObject(CWorldObject* object);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_BOX_OBJECT_H_
