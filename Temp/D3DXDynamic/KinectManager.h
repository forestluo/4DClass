///////////////////////////////////////////////////////////////////////////////
//
// KinectManager.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KINECT_MANAGER_H_
#define _KINECT_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// KinectManager
//
///////////////////////////////////////////////////////////////////////////////

class CKinectManager : public CD3DXObject
{
private:
	/** 
	 * Context of device.
	 */
	_OBJECT context;
	/** 
	 * List of devices.
	 */
	_OBJECT deviceList;

public:
	CKinectManager();
	virtual ~CKinectManager(void);

public:
	/** 
	 * Initialize devices.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_BOOL initializeDevices();

public:

	/** 
	 * Close devices.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void closeDevices();

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

///////////////////////////////////////////////////////////////////////////////
#endif //_KINECT_MANAGER_H_