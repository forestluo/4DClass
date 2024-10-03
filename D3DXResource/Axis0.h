///////////////////////////////////////////////////////////////////////////////
//
// Axis0.h
//
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _AXIS0_H_
#define _AXIS0_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXLinestrip.h"

///////////////////////////////////////////////////////////////////////////////
//
// CAxis0
//
///////////////////////////////////////////////////////////////////////////////

class CAxis0 : public CD3DXLinestrip
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
	CAxis0(void);
	virtual ~CAxis0(void);

public:

	/**
	 * Draw objects.
	 *
	 * @param pd3dDevice D3DX device.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void drawObjects(IDirect3DDevice9* pd3dDevice);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_AXIS0_H_
