///////////////////////////////////////////////////////////////////////////////
//
// SketcherAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SKETCHER_ATTRIBUTE_H_
#define _SKETCHER_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPort.h"
#include "ObjectSketcher.h"

///////////////////////////////////////////////////////////////////////////////
//
// SketcherAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CSketcherAttribute :
	public virtual CWorldObject
{
private:

	/**
	 * Sketch.
	 */
	CObjectSketcher* sketcher;

public:
	CSketcherAttribute(void);
	virtual ~CSketcherAttribute(void);

public:

	/**
	 * Get object sketcher.
	 *
	 * @param None No parameters needed.
	 * @return
	 *    <p>Sketcher of object.</p>
	 */
	virtual CObjectSketcher* getSketcher();

	/**
	 * Set collision.
	 *
	 * @param intersect Intersect.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setCollision(_BOOL intersect);

public:

	/**
	 * Set view port before rendering.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT setViewPort(CViewPort* viewPort);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_SKETCHER_ATTRIBUTE_H_