///////////////////////////////////////////////////////////////////////////////
//
// ImageDevice.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IMAGE_DEVICE_H_
#define _IMAGE_DEVICE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXDevice.h"
#include "OpenCVImageAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// ImageDevice
//
///////////////////////////////////////////////////////////////////////////////

class CImageDevice :
	public CD3DXDevice,
	public COpenCVImageAttribute
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
	CImageDevice(void);
	virtual ~CImageDevice(void);

};

#define IS_IMAGEDEVICE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CImageDevice::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_IMAGE_DEVICE_H_