///////////////////////////////////////////////////////////////////////////////
//
// ResourceManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXResource.h"
#include "DeviceManager.h"
#include "ListNodeEnumeration.h"

///////////////////////////////////////////////////////////////////////////////
//
// ResourceManager
//
///////////////////////////////////////////////////////////////////////////////

class CResourceManager : public CDeviceManager
{
private:
	/**
	 * Resources.
	 */
	_OBJECT resources;

public:
	CResourceManager(void);
	virtual ~CResourceManager(void);

protected:

	/**
	 * Release all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void releaseAll();

public:

	/**
	 * Add resource.
	 *
	 * @param resource Resource.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addResource(CD3DXResource* resource);
	/**
	 * Get resource.
	 *
	 * @param name Name of resource.
	 * @return
	 *     <p>Resource.</p>
	 */
	CD3DXResource* getResource(const CNormalString& name);
	/**
	 * Remove resource.
	 *
	 * @param name Name of resource.
	 * @return
	 *     <p>Resource.</p>
	 */
	CD3DXResource* removeResource(const CNormalString& name);
	
	/**
	 * Get enumeration.
	 *
	 * @param enumeration Enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void getEnumeration(CListNodeEnumeration& enumeration);

protected:

	/**
	 * Release resources.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT releaseResources();

	/**
	 * Create resources.
	 *
	 * @param pd3dDevice D3DX device.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT createResources(IDirect3DDevice9* pd3dDevice);

protected:

	/**
	 * Dispatch message.
	 *
	 * @param d3dxEvent D3DX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT dispatchMessage(const D3DXEvent& d3dxEvent);

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
#endif //_RESOURCE_MANAGER_H_
