///////////////////////////////////////////////////////////////////////////////
//
// D3DXCaptureTexture.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_CAPTURE_TEXTURE_H_
#define _D3DX_CAPTURE_TEXTURE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NormalStringList.h"
#include "D3DXDynamicTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXCaptureTexture
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXCaptureTexture : public CD3DXDynamicTexture
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
	CD3DXCaptureTexture(void);
	virtual ~CD3DXCaptureTexture(void);

public:

	/**
	 * Get capture names.
	 *
	 * @param names List of names.
	 * @return
	 *     <p>The result of function.</p>
	 */
	static void getCaptureNames(CNormalStringList& names);
};

#define IS_CAPTUREDYNAMICTEXTURE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXCaptureTexture::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_CAPTURE_TEXTURE_H_