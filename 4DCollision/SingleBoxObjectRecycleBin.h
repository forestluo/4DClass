///////////////////////////////////////////////////////////////////////////////
//
// SingleBoxObjectRecycleBin.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SINGLE_BOX_OBJECT_RECYCLE_BIN_H_
#define _SINGLE_BOX_OBJECT_RECYCLE_BIN_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RecycleBin.h"

///////////////////////////////////////////////////////////////////////////////
//
// SingleBoxObjectRecycleBin
//
///////////////////////////////////////////////////////////////////////////////

class CSingleBoxObjectRecycleBin : public CRecycleBin
{
public:
	CSingleBoxObjectRecycleBin(void);
	virtual ~CSingleBoxObjectRecycleBin(void);

protected:

	/**
	 * New object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>A new object.</p>
	 */
	virtual _OBJECT newObject();

	/**
	 * Delete object.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void deleteObject(_OBJECT object);

public:

	/**
	 * Recycle.
	 *
	 * @param object Recycle object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void recycle(_OBJECT object);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SINGLE_BOX_OBJECT_RECYCLE_BIN_H_
