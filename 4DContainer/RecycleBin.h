///////////////////////////////////////////////////////////////////////////////
//
// RecycleBin.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _RECYCLE_BIN_H_
#define _RECYCLE_BIN_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DLock.h"

///////////////////////////////////////////////////////////////////////////////
//
// RecyclBin
//
///////////////////////////////////////////////////////////////////////////////

class CRecycleBin : public C4DLock
{
private:
	//Counters.
	_LONG counters[4];
	//Containers.
	_OBJECT container;

public:
	CRecycleBin(void);
	CRecycleBin(_INTEGER capacity);
	virtual ~CRecycleBin(void);

protected:

	/**
	 * Get counter.
	 *
	 * @param countKind Kind of count.
	 * @return
	 *     <p>New count.</p>
	 */
	_LONG getCounter(_INTEGER countKind);

	/**
	 * Increase new count.
	 *
	 * @param countKind Kind of count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increaseCounter(_INTEGER countKind);

protected:

	/**
	 * New object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>A new object.</p>
	 */
	virtual _OBJECT newObject() = 0;

	/**
	 * Delete object.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void deleteObject(_OBJECT object) = 0;

public:

	/**
	 * Create
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>A new object.</p>
	 */
	virtual _OBJECT create();

	/**
	 * Recycle.
	 *
	 * @param object Recycle object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void recycle(_OBJECT object);

public:

	/**
	 * Clear all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAll();

	/**
	 * Get size of bin.
	 *
	 * @param type Type.
	 * @return
	 *     <p>Size of bin.</p>
	 */
	_INTEGER getSize();

	/**
	 * Get count of bin.
	 *
	 * @param type Type.
	 * @return
	 *     <p>Count of bin.</p>
	 */
	_INTEGER getCount();

	/**
	 * Get capacity of bin.
	 *
	 * @param type Type.
	 * @return
	 *     <p>Capacity of bin.</p>
	 */
	_INTEGER getCapacity();

	/**
	 * Set capacity of bin.
	 *
	 * @param type Type.
	 * @param capacity Capacity of bin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setCapacity(_INTEGER capacity);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_RECYCLE_BIN_H_
