///////////////////////////////////////////////////////////////////////////////
//
// D3DXDynamicTexture.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_DYNAMIC_TEXTURE_H_
#define _D3DX_DYNAMIC_TEXTURE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <dshow.h>
#include "4DLock.h"
#include "D3DXTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXDynamicTexture
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXDynamicTexture :
	public CD3DXTexture
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

private:

	/** 
	 * Width of actual image size.
	 */
	_INTEGER width;
	/** 
	 * Height of actual image size.
	 */
	_INTEGER height;

	/**
	 * Ratio of allocated width for dynamicTexture to the actual width of the image it holds.
	 */
	_FLOAT widthRatio;
	/** 
	 * Ratio of allocated height for dynamicTexture to the actual height of the image it holds.
	 */
	_FLOAT heightRatio;

private:

	/**
	 * Dynamic texture.
	 */
	LPDIRECT3DTEXTURE9 dynamicTexture;

public:
	CD3DXDynamicTexture(void);
	virtual ~CD3DXDynamicTexture(void);

public:

	/** 
	 * Get width.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Width of texture.</p>
	 */
	virtual _INTEGER getWidth() const;

	/** 
	 * Get height.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Height of texture.</p>
	 */
	virtual _INTEGER getHeight() const;

public:

	/**
	 * Get texture handle.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Texture handle.</p>
	 */
	virtual const LPDIRECT3DTEXTURE9 getTexture() const;

protected:

	/**
	 * Create texture.
	 *
	 * @param d3dxDevice D3DX device.
	 * @param width Width of texture.
	 * @param height Height of texture.
	 * @return
	 *     <p>The result of function.</p>
	 */
	_BOOL createTexture(IDirect3DDevice9* d3dxDevice,_INTEGER width,_INTEGER height);

protected:

	/** 
	 * Copy media sample.
	 *
	 * @param mediaSample Media sample.
	 * @return
	 *     <p>The result of function.</p>
	 */
	HRESULT copyMediaSample(IMediaSample *mediaSample,_INTEGER samplePitch);

	/**
	 * Copy surface.
	 *
	 * @param sourceSurface Source surface.
	 * @param width Width of texture.
	 * @param height Height of texture.
	 * @return
	 *     <p>The result of function.</p>
	 */
	HRESULT copySurface(IDirect3DSurface9 *sourceSurface,_INTEGER width,_INTEGER height);

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

#define IS_DYNAMICTEXTURE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXDynamicTexture::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_DYNAMIC_TEXTURE_H_