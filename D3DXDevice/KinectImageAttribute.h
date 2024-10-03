///////////////////////////////////////////////////////////////////////////////
//
// KinectImageAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KINECT_IMAGE_ATTRIBUTE_H_
#define _KINECT_IMAGE_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectInstanceAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// KinectImageAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CKinectImageAttribute :
	public virtual CKinectInstanceAttribute
{
private:
	/** 
	 * Image buffer.
	 */
	_OBJECT imageBuffer;

private:
	/** 
	 * Next frame event.
	 */
	_OBJECT frameEvent;
	/** 
	 * Video stream handle.
	 */
	_OBJECT streamHandle;

public:
	CKinectImageAttribute(void);
	virtual ~CKinectImageAttribute(void);

protected:

	/** 
	 * Get event.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Event.</p>
	 */
	_OBJECT getEvent() const;

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
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL createImage();

protected:

	/** 
	 * Copy image buffer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyImageBuffer();

	/**
	 * Get received image object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>OpenCV image object.</p>
	 */
	_OBJECT getReceivedImageObject() const;

};

///////////////////////////////////////////////////////////////////////////////
#endif //_KINECT_IMAGE_ATTRIBUTE_H_