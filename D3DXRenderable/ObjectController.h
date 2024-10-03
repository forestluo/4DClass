///////////////////////////////////////////////////////////////////////////////
//
// ObjectController.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _OBJECT_CONTROLLER_H_
#define _OBJECT_CONTROLLER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ControlBall.h"
#include "ObjectSketcher.h"

///////////////////////////////////////////////////////////////////////////////
//
// ObjectController
//
///////////////////////////////////////////////////////////////////////////////

class CObjectController : public CObjectSketcher
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
	/**
	 * Selected.
	 */
	_BOOL selected;

private:
	/**
	 * Control ball.
	 */
	CControlBall ball;

public:
	CObjectController(void);
	virtual ~CObjectController(void);

public:

	/**
	 * Detach object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void detachObject(void);
	/**
	 * Attach object.
	 *
	 * @param owner Owner object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void attachObject(CWorldObject* owner);

public:

	/**
	 * Get rotation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Eotation of controller.</p>
	 */
	C4DQuaternion getRotation() const;
	/**
	 * Set rotation.
	 *
	 * @param rotation Rotation of controller.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRotation(const C4DQuaternion& rotation);

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
#endif //_OBJECT_CONTROLLER_H_
