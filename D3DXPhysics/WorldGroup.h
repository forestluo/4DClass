///////////////////////////////////////////////////////////////////////////////
//
// WorldGroup.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _WORLD_GROUP_H_
#define _WORLD_GROUP_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPort.h"
#include "WorldObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// WorldGroup
//
///////////////////////////////////////////////////////////////////////////////

class CWorldGroup
{
private:

	/**
	 * Objects.
	 */
	_OBJECT objects;

public:
	CWorldGroup(void);
	virtual ~CWorldGroup(void);

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
	 * Add object.
	 *
	 * @param object World object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addObject(CWorldObject* object);
	/**
	 * Remove world object.
	 *
	 * @param object World object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void removeObject(CWorldObject* object);

	/**
	 * Whether object exists.
	 *
	 * @param object World object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_BOOL objectExists(CWorldObject* object) const;
	/**
	 * Get renderable object.
	 *
	 * @param alias Alias of renderable object.
	 * @return
	 *     <p>Renderable object with specified name.</p>
	 */
	CWorldObject* getObject(const CNormalString& alias);

public:

	/**
	 * Get enumeration.
	 *
	 * @param enumeration Enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void getEnumeration(CListNodeEnumeration& enumeration) const;

public:

	/**
	 * Clear texture.
	 *
	 * @param name Name of texture.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearTexture(const CNormalString& name);

public:

	/**
	 * Set view port.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT setViewPort(CViewPort* viewPort);

public:

	/**
	 * Dispatch message to objects.
	 *
	 * @param d3dxEvent DirectX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT dispatchMessage(const D3DXEvent& d3dxEvent);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_WORLD_GROUP_H_
