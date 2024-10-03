///////////////////////////////////////////////////////////////////////////////
//
// D3DXInputTexture.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_INPUT_TEXTURE_H_
#define _D3DX_INPUT_TEXTURE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXDevice.h"
#include "ResourceManager.h"
#include "D3DXDynamicTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXInputTexture
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXInputTexture :
	public CD3DXDynamicTexture
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
	 * Source.
	 */
	CD3DXResource* source;
	/** 
	 * Name of source.
	 */
	CNormalString sourceName;

public:
	CD3DXInputTexture(void);
	virtual ~CD3DXInputTexture(void);

public:

	/**
	 * Get source.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Source of resouse.</p>
	 */
	CD3DXResource* getSource() const;

	/**
	 * Get source name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Source name.</p>
	 */
	const CNormalString& getSourceName() const;

public:

	/** 
	 * Select source.
	 *
	 * @param resourceManager Resource manager.
	 * @param name Name of device or filter.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL selectSource(CResourceManager* resourceManager,const CNormalString& name);

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

#define IS_INPUTTEXTURE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXInputTexture::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_INPUT_TEXTURE_H_