///////////////////////////////////////////////////////////////////////////////
//
// Sketch1.h
//
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _SKETCH1_H_
#define _SKETCH1_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "Sketch0.h"

///////////////////////////////////////////////////////////////////////////////
//
// Sketch1
//
///////////////////////////////////////////////////////////////////////////////

class CSketch1 : public CSketch0
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
	CSketch1(void);
	virtual ~CSketch1(void);

protected:

	/**
	 * Draw objects.
	 *
	 * @param pd3dDevice Device.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void drawObjects(IDirect3DDevice9* pd3dDevice);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_SKETCH1_H_
