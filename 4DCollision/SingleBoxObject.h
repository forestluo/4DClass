///////////////////////////////////////////////////////////////////////////////
//
// SingleBoxObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SINGLE_BOX_OBJECT_H_
#define _SINGLE_BOX_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "BoxObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// SingleBoxObject
//
///////////////////////////////////////////////////////////////////////////////

class CSingleBoxObject : public CBoxObject
{
public:
	CSingleBoxObject(void);
	virtual ~CSingleBoxObject(void);

public:

	/**
	 * Whether is single.
	 * 
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is single.</p>
	 */
	_BOOL isSingle();

	/**
	 * Get toal count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Total count of object.
	 *	   Including its children.</p>
	 */
	_INTEGER getTotalCount();

public:

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
	 *     <p>Created object.</p>
	 */
	static CSingleBoxObject* create();
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SINGLE_BOX_OBJECT_H_
