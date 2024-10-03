///////////////////////////////////////////////////////////////////////////////
//
// D3DXFilter.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_FILTER_H_
#define _D3DX_FILTER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXDevice.h"
#include "ResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXFilter
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXFilter :
	public CD3DXResource
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
	 * Device.
	 */
	CD3DXDevice* device;
	/** 
	 * Name of device.
	 */
	CNormalString deviceName;

public:
	CD3DXFilter(void);
	virtual ~CD3DXFilter(void);

public:

	/**
	 * Get device.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Device name.</p>
	 */
	CD3DXDevice* getDevice() const;

	/**
	 * Get device name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Device name.</p>
	 */
	const CNormalString& getDeviceName() const;

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

#define IS_FILTER_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXFilter::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_FILTER_H_