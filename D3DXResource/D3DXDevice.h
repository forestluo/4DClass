///////////////////////////////////////////////////////////////////////////////
//
// D3DXDevice.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _D3DX_DEVICE_H_
#define _D3DX_DEVICE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXResource.h"

///////////////////////////////////////////////////////////////////////////////
//
// Resource
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXDevice :
	public CD3DXResource
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
	CD3DXDevice(void);
	virtual ~CD3DXDevice(void);

};

#define IS_DEVICE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXDevice::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_DEVICE_H_