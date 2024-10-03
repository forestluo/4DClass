///////////////////////////////////////////////////////////////////////////////
//
// 4DBase.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_BASE_H_
#define _4D_BASE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// 4DBase
//
///////////////////////////////////////////////////////////////////////////////

class C4DBase
{
private:
	//Hash code.
	_LONG thisClass;
	_LONG superClass;

private:
	//Class name.
	_STRING thisName;
	_STRING superName;

public:
	C4DBase(_STRING thisName,_STRING superName);
	virtual ~C4DBase();

	/**
	 * Get code of this class.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Code of this class.</p>
	 */
	_LONG classCode() const;

	/**
	 * Get code of super class.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Code of super class.</p>
	 */
	_LONG superCode() const;

	/**
	 * Check parent of this class.
	 *
	 * @param thisClass Hash code of this class.
	 * @param superClass Hash code of super class.
	 * @return
	 *     <p>Return true, if it is a child of super class.</p>
	 */
	static _BOOL isBaseOf(_LONG thisClass,_LONG superClass);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_BASE_H_