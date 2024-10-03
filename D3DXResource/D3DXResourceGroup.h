///////////////////////////////////////////////////////////////////////////////
//
// D3DXResourceGroup.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_RESOURCE_GROUP_H_
#define _D3DX_RESOURCE_GROUP_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXResource.h"
#include "D3DXDeviceReference.h"
#include "ListNodeEnumeration.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXResourceGroup
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXResourceGroup : CD3DXObject
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
	 * Resources.
	 */
	_OBJECT resources;

public:
	CD3DXResourceGroup(void);
	virtual ~CD3DXResourceGroup(void);

public:

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
	 * Get count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of resource.</p>
	 */
	_INTEGER getCount() const;

	/** 
	 * Get count.
	 *
	 * @param classCode Class code.
	 * @return
	 *     <p>Count of resource.</p>
	 */
	_INTEGER getCount(_LONG classCode);

	/**
	 * Get enumeration.
	 *
	 * @param enumeration Enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void getEnumeration(CListNodeEnumeration& enumeration);

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
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT createResources(_OBJECT resourceManager) = 0;

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
#endif //_D3DX_RESOURCE_GROUP_H_
