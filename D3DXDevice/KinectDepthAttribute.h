///////////////////////////////////////////////////////////////////////////////
//
// KinectDepthAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KINECT_DEPTH_ATTRIBUTE_H_
#define _KINECT_DEPTH_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectInstanceAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// KinectDepthAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CKinectDepthAttribute :
	public virtual CKinectInstanceAttribute
{
private:

	/** 
	 * Depth buffer.
	 */
	_SHORT* depthBuffer;

private:

	/**
	 * Frame event.
	 */
	_OBJECT frameEvent;
	/** 
	 * Depth stream handle.
	 */
	_OBJECT streamHandle;

public:
	CKinectDepthAttribute(void);
	virtual ~CKinectDepthAttribute(void);

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
	 * Destroy depth.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void destroyDepth();

	/** 
	 * Create depth.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL createDepth();

protected:

	/** 
	 * Copy depth buffer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyDepthBuffer();

	/**
	 * Get received depth buffer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Raw values of depth.</p>
	 */
	_SHORT* getReceivedDepthBuffer() const;

};

///////////////////////////////////////////////////////////////////////////////
#endif //_KINECT_DEPTH_ATTRIBUTE_H_