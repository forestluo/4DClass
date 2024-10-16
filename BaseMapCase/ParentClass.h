///////////////////////////////////////////////////////////////////////////////
//
// ParentClass.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _PARENT_CLASS_H_
#define _PARENT_CLASS_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DBaseMap.h"

///////////////////////////////////////////////////////////////////////////////
//
// Resource
//
///////////////////////////////////////////////////////////////////////////////

class CParentClass
{
private:
	//Base description.
	static const C4DBase base;

public:

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	static _LONG getClassCode() {return base.classCode();}

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	virtual _LONG classCode() const {return base.classCode();}

public:
	CParentClass(void);
	virtual ~CParentClass(void);

};

#define IS_PARENT_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CParentClass::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_PARENT_CLASS_H_