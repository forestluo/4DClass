///////////////////////////////////////////////////////////////////////////////
//
// OpenCVImageAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _OPENCV_IMAGE_ATTRIBUTE_H_
#define _OPENCV_IMAGE_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// OpenCVImageAttribute
//
///////////////////////////////////////////////////////////////////////////////

class COpenCVImageAttribute
{
private:
	/** 
	 * Image.
	 */
	_OBJECT image;

public:
	COpenCVImageAttribute(void);
	virtual ~COpenCVImageAttribute(void);

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
	 * Get image buffer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Buffer of image.</p>
	 */
	virtual _BYTE* getImageBuffer() const;

	/**
	 * Get image object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>OpenCV image object.</p>
	 */
	virtual _OBJECT getImageObject() const;

protected:

	/** 
	 * Destroy image.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void destroyImage();

	/** 
	 * Create image.
	 *
	 * @param width Width of image.
	 * @param height Height of image.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL createImage(_INTEGER width,_INTEGER height);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_OPENCV_IMAGE_ATTRIBUTE_H_