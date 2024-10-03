///////////////////////////////////////////////////////////////////////////////
//
// KinectDevice.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KINECT_DEVICE_H_
#define _KINECT_DEVICE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DLock.h"
#include "KinectImageAttribute.h"
#include "KinectDepthAttribute.h"
#include "OpenCVImageAttribute.h"
#include "KinectProcessAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// KinectDevice
//
///////////////////////////////////////////////////////////////////////////////

class CKinectDevice :
	private C4DLock,
	public CD3DXDevice,
	public COpenCVImageAttribute,
	public CKinectImageAttribute,
	public CKinectDepthAttribute,
	public CKinectProcessAttribute
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
	 * Depth buffer.
	 */
	_SHORT* depthBuffer;

public:
	CKinectDevice(void);
	virtual ~CKinectDevice(void);

public:

	/** 
	 * Get kinect count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of kinect.</p>
	 */
	static _INTEGER getKinectCount();

public:

	/**
	 * Get depth buffer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Raw values of depth.</p>
	 */
	_SHORT* getDepthBuffer() const;

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

protected:

	/**
	 * Nui process thread.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Result of thread.</p>
	 */
	virtual DWORD WINAPI nuiProcessThread();

public:

	/** 
	 * Close device.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void closeDevice();

	/** 
	 * Open device.
	 *
	 * @param index Index of device.
	 * @param mode Resolution mode.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL openDevice(_INTEGER index,_INTEGER mode = CKinectInstanceAttribute::vgaResolution);

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

#define IS_KINECTDEVICE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CKinectDevice::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_KINECT_DEVICE_H_