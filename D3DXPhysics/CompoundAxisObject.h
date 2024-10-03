///////////////////////////////////////////////////////////////////////////////
//
// CompoundAxisObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _COMPOUND_AXIS_OBJECT_H_
#define _COMPOUND_AXIS_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CompoundAxisObject
//
///////////////////////////////////////////////////////////////////////////////

class CCompoundAxisObject : public CCompoundObject
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
	CCompoundAxisObject(void);
	virtual ~CCompoundAxisObject(void);

protected:

	/**
	 * Initialize objects of world.
	 *
	 * @param resourceApplication Resource application.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeObjects(CResourceApplication* resourceApplication);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_COMPOUND_AXIS_OBJECT_H_
