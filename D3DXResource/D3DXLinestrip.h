///////////////////////////////////////////////////////////////////////////////
//
// D3DXLinestrip.h
//
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_LINESTRIP_H_
#define _D3DX_LINESTRIP_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXRenderable.h"
#include "D3DXIndexAttribute.h"
#include "D3DXVertexAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXLinestrip
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXLinestrip :
	public CD3DXRenderable,
	public CD3DXIndexAttribute,
	public CD3DXVertexAttribute
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
	CD3DXLinestrip(void);
	virtual ~CD3DXLinestrip(void);

protected:

	/**
	 * Draw objects.
	 *
	 * @param pd3dDevice D3DX device.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void drawObjects(IDirect3DDevice9* pd3dDevice) = 0;

protected:

	/**
	 * Draw box.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param box Box.
	 * @return
	 *     <p>No results retruned.</p>
	 */
	void drawBox(IDirect3DDevice9* pd3dDevice,const CSimpleBox& box);

	/**
	 * Draw cube.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param matrix World matrix.
	 * @return
	 *     <p>No results retruned.</p>
	 */
	void drawCube(IDirect3DDevice9* pd3dDevice,const C4DMatrix4& matrix);

protected:

	/**
	 * Draw sphere.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param sphere Sphere.
	 * @return
	 *     <p>No results retruned.</p>
	 */
	void drawSphere(IDirect3DDevice9* pd3dDevice,const CSimpleSphere& sphere);

	/**
	 * Draw sphere.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param origin Original point.
	 * @param majorAxis Major axis direction.
	 * @param minorAxis Minor axis direction.
	 * @return
	 *     <p>No results retruned.</p>
	 */
	void drawRing(IDirect3DDevice9* pd3dDevice,
					const C4DVector3& origin,const C4DVector3& majorAxis,const C4DVector3& minorAxis);

protected:

	/**
	 * Draw ray.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param origin Origin porint.
	 * @param direction Direction.
	 * @param normalize Whether normalize it.
	 * @return
	 *     <p>No results retruned.</p>
	 */
	void drawRay(IDirect3DDevice9* pd3dDevice,
				 const C4DVector3& origin,const C4DVector3& direction,_BOOL normalize);

public:

	/**
	 * Render.
	 *
	 * @param pd3dDevice D3DX device.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT render(IDirect3DDevice9* pd3dDevice,CD3DXEffect* effect);

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

#define IS_LINESTRIP_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXLinestrip::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_LINESTRIP_H_
