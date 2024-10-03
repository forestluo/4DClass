///////////////////////////////////////////////////////////////////////////////
//
// D3DXDeviceReference.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_DEVICE_REFERENCE_H_
#define _D3DX_DEVICE_REFERENCE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXDeviceReference
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXDeviceReference : public CD3DXObject
{
private:
	/**
	 * DirectX device.
	 */
	IDirect3DDevice9* d3dxDevice;

public:
	CD3DXDeviceReference(void);
	virtual ~CD3DXDeviceReference(void);

public:

	/**
	 * Get device.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	IDirect3DDevice9* getDevice() const;

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
#endif //_D3DX_DEVICE_REFERENCE_H_
