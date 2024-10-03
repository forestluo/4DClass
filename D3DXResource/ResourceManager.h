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
#include "D3DXResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
//
// ResourceManager
//
///////////////////////////////////////////////////////////////////////////////

class CResourceManager : public CD3DXDeviceReference
{
public:
	//Manager Type
	static const _LONG deviceManager;
	static const _LONG filterManager;
	static const _LONG textureManager;
	static const _LONG effectManager;
	static const _LONG linestripManager;
	static const _LONG primitiveManager;
	static const _LONG meshManager;

private:
	/** 
	 * Resource groups.
	 */
	_OBJECT groups;

public:
	CResourceManager(void);
	virtual ~CResourceManager(void);

private:
	
	/** 
	 * Release all groups.
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
	 * @param classCode Class code.
	 * @return
	 *     <p>Count of resource group.</p>
	 */
	_INTEGER getCount(_LONG classClode) const;

	/** 
	 * Get count.
	 *
	 * @param majorClass Major class code.
	 * @param minorClass Minor class code.
	 * @return
	 *     <p>Count of resource group.</p>
	 */
	_INTEGER getCount(_LONG majorClass,_LONG minorClass) const;

private:

	/** 
	 * Get resource group.
	 *
	 * @param classCode Class code.
	 * @return
	 *     <p>Resource group.</p>
	 */
	CD3DXResourceGroup* getGroup(_LONG classCode) const;

	/** 
	 * Add group.
	 *
	 * @param classCode Class code.
	 * @param group Group.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addGroup(_LONG classCode,CD3DXResourceGroup* group);

private:

	/**
	 * Add resource.
	 *
	 * @param classCode Class code.
	 * @param resource Resource.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addResource(_LONG classCode,CD3DXResource* resource);

	/** 
	 * Get resource.
	 *
	 * @param classCode Class code.
	 * @param name Name of resource.
	 * @return
	 *     <p>Resource group.</p>
	 */
	CD3DXResource* getResource(_LONG classCode,const CNormalString& name);

	/** 
	 * Remove resource.
	 *
	 * @param classCode Class code.
	 * @param name Name of resource.
	 * @return
	 *     <p>Resource group.</p>
	 */
	CD3DXResource* removeResource(_LONG classCode,const CNormalString& name);

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

public:

	/**
	 * Get enumeration.
	 *
	 * @param classCode Class code.
	 * @param iterator List node enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void getEnumeration(_LONG classCode,CListNodeEnumeration& iterator);

private:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage1(const D3DXEvent& d3dxEvent);

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage2(const D3DXEvent& d3dxEvent);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_RESOURCE_MANAGER_H_
