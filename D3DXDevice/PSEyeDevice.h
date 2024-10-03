///////////////////////////////////////////////////////////////////////////////
//
// PSEyeDevice.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PSEYE_DEVICE_H_
#define _PSEYE_DEVICE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ImageDevice.h"

///////////////////////////////////////////////////////////////////////////////
//
// PSEyeDevice
//
///////////////////////////////////////////////////////////////////////////////

class CPSEyeDevice : public CImageDevice
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
	 * Guid of device.
	 */
	GUID guid;
	/** 
	 * Camera instance.
	 *
	 * <p>CLEyeCameraInstance</p>
	 */
	_OBJECT camera;

private:

	/** 
	 * Image buffer.
	 */
	_BYTE* imageBuffer;

private:

	/** 
	 * Flips per second.
	 */
	_FLOAT fps;
	/** 
	 * Camera color mode.
	 *
	 * <p>CLEyeCameraColorMode</p>
	 */
	_INTEGER colorMode;
	/** 
	 * Camera resolution.
	 *
	 * <p>CLEyeCameraResolution</p>
	 */
	_INTEGER resolution;

public:
	CPSEyeDevice(GUID guid);
	virtual ~CPSEyeDevice(void);

public:

	/** 
	 * Get camera count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of camera.</p>
	 */
	static _INTEGER getCameraCount();

	/** 
	 * Get camera count.
	 *
	 * @param index Index of camera.
	 * @return
	 *     <p>GUID of camera.</p>
	 */
	static GUID getCameraGuid(_INTEGER index);

	/** 
	 * Get color mode description.
	 *
	 * @param colorMode Color mode.
	 * @return
	 *     <p>Description of color mode.</p>
	 */
	static _STRING getColorModeDescription(_INTEGER colorMode);

	/** 
	 * Get resolution description.
	 *
	 * @param resolution Resolution.
	 * @return
	 *     <p>Description of resolution.</p>
	 */
	static _STRING getResolutionDescription(_INTEGER resolution);

public:

	/** 
	 * Get FPS.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>FPS value.</p>
	 */
	_FLOAT getFps() const;

	/** 
	 * Get color mode.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>Color mode.</p>
	 */
	_INTEGER getColorMode() const;

	/** 
	 * Get resolution.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>Resolution.</p>
	 */
	_INTEGER getResolution() const;

public:

	/**
	 * Get value of parameter.
	 *
	 * @param parameter Parameter identity.
	 * @return
	 *     <p>Value of parameter.</p>
	 */
	_INTEGER getValue(_INTEGER parameter);

	/**
	 * Set value of parameter.
	 *
	 * @param parameter Parameter identity.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setValue(_INTEGER parameter,_INTEGER value);

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
	 * @param colorMode Color mode.
	 * @param resolution Resolution.
	 * @param fps Flips per second.
	 * @return
	 *     <p>Return true, if successfully created.</p>
	 */
	_BOOL openDevice(_INTEGER colorMode = 1,_INTEGER resolution = 1,_FLOAT fps = 30.0f);

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

#define IS_PSEYEDEVICE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CPSEyeDevice::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_PSEYE_DEVICE_H_