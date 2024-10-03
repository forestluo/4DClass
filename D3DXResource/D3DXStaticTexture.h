///////////////////////////////////////////////////////////////////////////////
//
// D3DXStaticTexture.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_STATIC_TEXTURE_H_
#define _D3DX_STATIC_TEXTURE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXStaticTexture
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXStaticTexture : public CD3DXTexture
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
	 * File name.
	 */
	CNormalString fileName;

private:
	/**
	 * Base texture.
	 */
	LPDIRECT3DBASETEXTURE9 baseTexture;

public:
	CD3DXStaticTexture(void);
	virtual ~CD3DXStaticTexture(void);

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

public:

	/**
	 * Get file name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>File name.</p>
	 */
	const CNormalString& getFileName() const;
	/**
	 * Set file name.
	 *
	 * @param wsFileName Name of file.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFileName(const CNormalString& fileName);

public:

	/**
	 * Load from file.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param fileName Name of file.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT loadFromFile(IDirect3DDevice9* pd3dDevice,const CNormalString& fileName);

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

#define IS_STATICTEXTURE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXStaticTexture::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_STATIC_TEXTURE_H_