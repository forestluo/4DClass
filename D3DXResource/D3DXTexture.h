///////////////////////////////////////////////////////////////////////////////
//
// D3DXTexture.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_TEXTURE_H_
#define _D3DX_TEXTURE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXResource.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXTexture
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXTexture : public CD3DXResource
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
	CD3DXTexture(void);
	virtual ~CD3DXTexture(void);

public:

	/** 
	 * Get width.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Width of texture.</p>
	 */
	virtual _INTEGER getWidth() const = 0;

	/** 
	 * Get height.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Height of texture.</p>
	 */
	virtual _INTEGER getHeight() const = 0;

public:

	/**
	 * Get texture handle.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Texture handle.</p>
	 */
	virtual const LPDIRECT3DTEXTURE9 getTexture() const = 0;

};

#define IS_TEXTURE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXTexture::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_TEXTURE_H_