///////////////////////////////////////////////////////////////////////////////
//
// KinectInstanceAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KINECT_INSTANCE_ATTRIBUTE_H_
#define _KINECT_INSTANCE_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXDevice.h"

///////////////////////////////////////////////////////////////////////////////
//
// KinectInstanceAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CKinectInstanceAttribute
{
public:
	static const _INTEGER vgaResolution;
	static const _INTEGER qvgaResolution;
	static const _INTEGER qqvgaResolution;

private:
	/** 
	 * Index.
	 */
	_INTEGER index;

private:

	/** 
	 * Instance id.
	 */
	_OBJECT instanceID;
	/** 
	 * Instance.
	 */
	_OBJECT nuiInstance;
	/** 
	 * Resolution.
	 */
	_INTEGER resolution;

public:
	CKinectInstanceAttribute(void);
	virtual ~CKinectInstanceAttribute(void);

protected:

	/** 
	 * Get index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Index of device.</p>
	 */
	_INTEGER getIndex() const;
	
	/** 
	 * Get device.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Instance of device.</p>
	 */
	_OBJECT getDevice() const;

public:

	/** 
	 * Get resolution.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Resolution of image.</p>
	 */
	_INTEGER getResolution() const;

	/** 
	 * Get resolution width.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Width of resolition.</p>
	 */
	_INTEGER getResolutionWidth() const;

	/** 
	 * Get resolution height.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>Height of resloution.</p>
	 */
	_INTEGER getResolutionHeight() const;

protected:

	/** 
	 * Destroy instance.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void destroyInstance();

	/** 
	 * Open device.
	 *
	 * @param index Index of device.
	 * @param resolution Resolution of device.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL createInstance(_INTEGER index,_INTEGER resolution);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_KINECT_INSTANCE_ATTRIBUTE_H_