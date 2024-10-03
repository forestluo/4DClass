///////////////////////////////////////////////////////////////////////////////
//
// 4DBaseMap.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_BASE_MAP_H_
#define _4D_BASE_MAP_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DLock.h"
#include "4DBase.h"

///////////////////////////////////////////////////////////////////////////////
//
// 4DBaseMap
//
///////////////////////////////////////////////////////////////////////////////

class C4DBaseMap : public C4DLock
{
private:
	/**
	 * Container.
	 */
	_OBJECT container;

public:
	C4DBaseMap();
	virtual ~C4DBaseMap();

	/**
	 * Add base.
	 *
	 * @param base Base.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addBase(C4DBase* base);

	/**
	 * Whether exists.
	 *
	 * @param thisClass Code of this class.
	 * @return
	 *      <p>Return true, if it exists.</p>
	 */
	_BOOL exists(_LONG thisClass);

	/**
	 * Check parent of this class.
	 *
	 * @param thisClass Hash code of this class.
	 * @param superClass Hash code of super class.
	 * @return
	 *     <p>Return true, if it is a child of super class.</p>
	 */
	_BOOL isBaseOf(_LONG thisClass,_LONG superClass);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_BASE_MAP_H_