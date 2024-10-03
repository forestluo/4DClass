///////////////////////////////////////////////////////////////////////////////
//
// ImageFilter.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IMAGE_FILTER_H_
#define _IMAGE_FILTER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXFilter.h"
#include "OpenCVImageAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// ImageFilter
//
///////////////////////////////////////////////////////////////////////////////

class CImageFilter :
	public CD3DXFilter,
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
	CImageFilter(void);
	virtual ~CImageFilter(void);

public:

	/** 
	 * Get width.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Width of image.</p>
	 */
	virtual _INTEGER getWidth() const;

	/** 
	 * Get height.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>Height of image.</p>
	 */
	virtual _INTEGER getHeight() const;

public:

	/** 
	 * Select device.
	 *
	 * @param resourceManager Resource manager.
	 * @param name Name of image device.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL selectDevice(CResourceManager* resourceManager,const CNormalString& name);

};

#define IS_IMAGEFILTER_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CImageFilter::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_IMAGE_FILTER_H_