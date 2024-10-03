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

#include "D3DXDevice.h"

///////////////////////////////////////////////////////////////////////////////
//
// KinectDevice
//
///////////////////////////////////////////////////////////////////////////////

class CKinectDevice : public CD3DXDevice
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
	 * Index of device.
	 */
	_INTEGER index;

private:

	/** 
	 * Resolution mode.
	 */
	_INTEGER mode;
	/** 
	 * Image buffer.
	 */
	_BYTE* imageBuffer;
	/** 
	 * Depth buffer.
	 */
	_SHORT* depthBuffer;

private:

	/**
	 * Total frames.
	 */
	_INTEGER totalFrames;
	/** 
	 * Last FPS time.
	 */
	_INTEGER lastFPStime;
	/** 
	 * Last total frames.
	 */
	_INTEGER lastTotalFrames;

private:

	/** 
	 * Instance id.
	 */
	_OBJECT instanceID;
	/** 
	 * Instance.
	 */
	_OBJECT nuiInstance;

private:

	/** 
	 * Nui process.
	 */
	_OBJECT nuiProcess;
	/** 
	 * Nui process event.
	 */
	_OBJECT nuiProcessEvent;

private:

	/** 
	 * Video stream handle.
	 */
	_OBJECT videoStreamHandle;
	/** 
	 * Depth stream handle.
	 */
	_OBJECT depthStreamHandle;

private:

	/**
	 * Next depth frame event.
	 */
	_OBJECT nextDepthFrameEvent;
	/** 
	 * Next video frame event.
	 */
	_OBJECT nextVideoFrameEvent;

public:
	CKinectDevice(_INTEGER index);
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

private:

	/**
	 * Nui process thread.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Result of thread.</p>
	 */
	DWORD WINAPI nuiProcessThread();

public:

	/**
	 * Nui process thread.
	 *
	 * @param pParam Parameter of thread.
	 * @return
	 *     <p>Result of thread.</p>
	 */
	static DWORD WINAPI nuiProcessThread(LPVOID pParam);

public:

	/**
	 * Get image.
	 *
	 * <p>The image data must be RGBA format.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Raw bytes of image.</p>
	 */
	_BYTE* getImage() const;

	/** 
	 * Get width.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Width of image.</p>
	 */
	_INTEGER getWidth() const;

	/** 
	 * Get height.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>Height of image.</p>
	 */
	_INTEGER getHeight() const;

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
	 * @param mode Resolution mode.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL openDevice(_INTEGER mode = vgaMode);

};

#define IS_KINECTDEVICE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CKinectDevice::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_KINECT_DEVICE_H_