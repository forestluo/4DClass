///////////////////////////////////////////////////////////////////////////////
//
// ObjectSketcher.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _OBJECT_SKETCHER_H_
#define _OBJECT_SKETCHER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPort.h"
#include "PhysicsObject.h"
#include "ResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// ObjectSketcher
//
///////////////////////////////////////////////////////////////////////////////

class CObjectSketcher : public CD3DXObject
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
	 * Draw box.
	 */
	_BOOL drawBox;
	/**
	 * Draw axis.
	 */
	_BOOL drawAxis;
	/**
	 * Draw sphere.
	 */
	_BOOL drawSphere;
	/**
	 * Draw intersected.
	 */
	_BOOL intersected;

protected:
	/**
	 * Sketch.
	 */
	_OBJECT sketch;
	/**
	 * Owner object.
	 */
	CWorldObject* owner;

public:
	CObjectSketcher(void);
	virtual ~CObjectSketcher(void);

public:

	/**
	 * Get owner.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Owner of sketcher.</p>
	 */
	CWorldObject* getOwner() const;

protected:

	/**
	 * Detach sketch.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void detachSketch();
	/**
	 * Attach sketch.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void attachSketch(CResourceManager* resourceManager);

public:

	/**
	 * Detach object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void detachObject();
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
	 * Get world box.
	 *
	 * @param box World box.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL getWorldBox(CSimpleBox& box);
	/**
	 * Get world sphere.
	 *
	 * @param sphere World sphere.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL getWorldSphere(CSimpleSphere& sphere);

public:

	/**
	 * Set view port.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT setViewPort(CViewPort* viewPort);

protected:

	/**
	 * Render.
	 *
	 * @param pd3dDevice Device.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT render(IDirect3DDevice9* pd3dDevice);

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

#define IS_OBJECTSKETCHER_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CObjectSketcher::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_OBJECT_SKETCHER_H_
