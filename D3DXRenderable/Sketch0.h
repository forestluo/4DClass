///////////////////////////////////////////////////////////////////////////////
//
// Sketch0.h
//
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _SKETCH0_H_
#define _SKETCH0_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXLinestrip.h"

///////////////////////////////////////////////////////////////////////////////
//
// Sketch0
//
///////////////////////////////////////////////////////////////////////////////

class CSketch0 : public CD3DXLinestrip
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

protected:

	/**
	 * Object sketcher.
	 */
	_OBJECT sketcher;

public:
	CSketch0(void);
	virtual ~CSketch0(void);

protected:

	/**
	 * Draw objects.
	 *
	 * @param pd3dDevice Device.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void drawObjects(IDirect3DDevice9* pd3dDevice);

public:

	/**
	 * Detach sketcher.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void detachSketcher();
	/**
	 * Attach sketcher.
	 *
	 * @param sketcher Object sketcher.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void attachSketcher(_OBJECT sketcher);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SKETCH0_H_
