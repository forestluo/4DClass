///////////////////////////////////////////////////////////////////////////////
//
// ControllerAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CONTROLLER_ATTRIBUTE_H_
#define _CONTROLLER_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPort.h"
#include "ObjectController.h"

///////////////////////////////////////////////////////////////////////////////
//
// ControllerAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CControllerAttribute :
	public virtual CWorldObject
{
private:

	/**
	 * Controller.
	 */
	CObjectController* controller;

public:
	CControllerAttribute(void);
	virtual ~CControllerAttribute(void);

public:

	/**
	 * Get object controller.
	 *
	 * @param None No parameters needed.
	 * @return
	 *    <p>Sketcher of object.</p>
	 */
	virtual CObjectController* getController();

public:

	/**
	 * Whether is picked.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is picked.</p>
	 */
	virtual _BOOL isPicked() const;
	/**
	 * Set picked.
	 *
	 * @param picked Picked status.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setPicked(_BOOL picked);

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
#endif //_CONTROLLER_ATTRIBUTE_H_