///////////////////////////////////////////////////////////////////////////////
//
// CompoundBoxObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _COMPOUND_BOX_OBJECT_H_
#define _COMPOUND_BOX_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CompoundBoxObject
//
///////////////////////////////////////////////////////////////////////////////

class CCompoundBoxObject : public CCompoundObject
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
	CCompoundBoxObject(void);
	virtual ~CCompoundBoxObject(void);

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
#endif //_COMPOUND_BOX_OBJECT_H_
