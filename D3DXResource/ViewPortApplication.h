///////////////////////////////////////////////////////////////////////////////
//
// ViewPortApplication.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _VIEWPORT_APPLICATION_H_
#define _VIEWPORT_APPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DLock.h"
#include "D3DXObject.h"

#include "ViewPort.h"

///////////////////////////////////////////////////////////////////////////////
//
// ViewPortApplication
//
///////////////////////////////////////////////////////////////////////////////

class CViewPortApplication :
	public virtual C4DLock,
	public virtual CD3DXObject
{
private:
	/**
	 * View port.
	 */
	CViewPort* viewPort;

public:
	CViewPortApplication(void);
	virtual ~CViewPortApplication(void);

public:

	/**
	 * Get view port.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>View port.</p>
	 */
	CViewPort* getViewPort() const;

	/**
	 * Set view port.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setViewPort(CViewPort* viewPort);

public:

	/**
	 * View XY plane.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void zAxisView();
	/**
	 * View XZ plane.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void yAxisView();
	/**
	 * View YZ plane.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void xAxisView();

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
#endif //_VIEWPORT_APPLICATION_H_
