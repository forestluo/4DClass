///////////////////////////////////////////////////////////////////////////////
//
// ChildClass.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _CHILD_CLASS_H_
#define _CHILD_CLASS_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ParentClass.h"

///////////////////////////////////////////////////////////////////////////////
//
// Resource
//
///////////////////////////////////////////////////////////////////////////////

class CChildClass : public CParentClass
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
	CChildClass(void);
	virtual ~CChildClass(void);

};

#define IS_CHILD_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CChildClass::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_CHILD_CLASS_H_