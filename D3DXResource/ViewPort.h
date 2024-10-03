///////////////////////////////////////////////////////////////////////////////
//
// ViewPort.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _VIEW_PORT_H
#define _VIEW_PORT_H

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"
#include "4DMatrix4.h"
#include "D3DXObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CViewPort
//
///////////////////////////////////////////////////////////////////////////////

class CViewPort : public CD3DXObject
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
	CViewPort(_OBJECT camera);
	virtual ~CViewPort(void);

private:
	/**
	 * Camera of view port.
	 */
	_OBJECT camera;

private:
	/**
	 * Width of view port.
	 */
	_INTEGER width;
	/**
	 * Height of view port.
	 */
	_INTEGER height;

private:
	/**
	 * Frame stamp.
	 */
	_INTEGER frameStamp;
	/**
	 * Mouse position.
	 */
	_INTEGER xMouse,yMouse;

protected:
	/**
	 * Initialize camera.
	 *
	 * @param camera Camera.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initializeCamera(_OBJECT pCamera);

public:

	/**
	 * Next frame stamp.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void nextFrameStamp();
	/**
	 * Get frame stamp.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Value of frame stamp.</p>
	 */
	_INTEGER getFrameStamp();

public:

	/**
	 * Get x of mouse position.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>X of mouse position.</p>
	 */
	_INTEGER getMouseX();
	/**
	 * Get y of mouse position.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Y of mouse position.</p>
	 */
	_INTEGER getMouseY();

public:

	/**
	 * Get view direction.
	 *
	 * @param x X position in screen.
	 * @param y Y position in screen.
	 * @return
	 *     <p>View direction.</p>
	 */
	C4DVector3 getViewDirection(_INTEGER x,_INTEGER y);
	/**
	 * Get world position.
	 *
	 * @param x X position in screen.
	 * @param y Y position in screen.
	 * @return
	 *     <p>World direction.</p>
	 */
	C4DVector3 getWorldDirection(_INTEGER x,_INTEGER y);
	/**
	 * Get move direction.
	 *
	 * @param x X position.
	 * @param y Y position.
	 * @return
	 *     <p>Move direction.</p>
	 */
	C4DVector3 getMoveDirection(_INTEGER x,_INTEGER y);

public:

	/**
	 * Get width.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Width of view port.</p>
	 */
	_INTEGER getWidth();
	/**
	 * Get height.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Height of view port.</p>
	 */
	_INTEGER getHeight();

	/**
	 * Get far clip.
	 *
	 * @param None No prameters needed.
	 * @return
	 *     <p>Far clip.</p>
	 */
	_FLOAT getFarClip();
	/**
	 * Get near clip.
	 *
	 * @param None No prameters needed.
	 * @return
	 *     <p>Near clip.</p>
	 */
	_FLOAT getNearClip();
	/**
	 * Get FAspect.
	 *
	 * @param None No prameters needed.
	 * @return
	 *     <p>FAspect.</p>
	 */
	_FLOAT getFAspect();
	/**
	 * Get field of view.
	 *
	 * @param None No prameters needed.
	 * @return
	 *     <p>Field of view.</p>
	 */
	_FLOAT getFieldOfView();

	/**
	 * Get eye at.
	 *
	 * @param None No prameters needed.
	 * @return
	 *     <p>Vector of eye position.</p>
	 */
	C4DVector3 getEyeAt();
	/**
	 * Get eye look at.
	 *
	 * @param None No prameters needed.
	 * @return
	 *     <p>Vector of eye looking direction.</p>
	 */
	C4DVector3 getEyeLookAt();

	/**
	 * Get view matrix.
	 *
	 * @param None No prameters needed.
	 * @return
	 *     <p>Matrix of view.</p>
	 */
	C4DMatrix4 getViewMatrix();
	/**
	 * Get projection matrix.
	 *
	 * @param None No prameters needed.
	 * @return
	 *     <p>Matrix of projection.</p>
	 */
	C4DMatrix4 getProjectionMatrix();

	/**
	 * Set view parameters.
	 *
	 * @param eyeAt Vector of eye position.
	 * @param eyeLookAt Vector of looking direction.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setViewParameters(const C4DVector3& vEyeAt,const C4DVector3& vEyeLookAt);
	/**
	 * Set projection parameters.
	 *
	 * @param fov Field of view.
	 * @param aspect Field of aspect.
	 * @param nearPlane Near plane.
	 * @param farPlane Far plane.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setProjectionParameters(_FLOAT fov,_FLOAT aspect,_FLOAT nearPlane,_FLOAT farPlane);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent D3DX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);
};

#define IS_VIEWPORT_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CViewPort::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_VIEW_PORT_H