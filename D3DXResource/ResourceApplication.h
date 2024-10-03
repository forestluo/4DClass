///////////////////////////////////////////////////////////////////////////////
//
// ResourceApplication.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _RESOURCE_APPLICATION_H_
#define _RESOURCE_APPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DLock.h"
#include "D3DXObject.h"

#include "ResourceManager.h"
#include "RenderableManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// ResourceApplication
//
///////////////////////////////////////////////////////////////////////////////

class CResourceApplication :
	public virtual C4DLock,
	public virtual CD3DXObject
{
private:
	/**
	 * Resource manager.
	 */
	CResourceManager* resourceManager;
	/**
	 * Renderable manager.
	 */
	CRenderableManager* renderableManager;

public:
	CResourceApplication(void);
	virtual ~CResourceApplication(void);

public:

	/**
	 * Get resource manager.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Resource manager.</p>
	 */
	CResourceManager* getResourceManager() const;

	/**
	 * Get renderable manager.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Renderable manager.</p>
	 */
	CRenderableManager* getRenderableManager() const;

public:

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
	 * Handle message.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_RESOURCE_APPLICATION_H_
