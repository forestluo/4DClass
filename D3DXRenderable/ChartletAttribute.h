///////////////////////////////////////////////////////////////////////////////
//
// ChartletAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CHARTLET_ATTRIBUTE_H_
#define _CHARTLET_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXTexture.h"
#include "ResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// ChartletAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CChartletAttribute : public CD3DXObject
{
private:

	/**
	 * Scene map.
	 */
	CD3DXTexture* sceneMap;
	/**
	 * Name of scene map.
	 */
	CNormalString sceneMapName;

public:
	CChartletAttribute(void);
	virtual ~CChartletAttribute(void);

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
	 * Get scene map.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Scene map.</p>
	 */
	CD3DXTexture* getSceneMap() const;

public:

	/**
	 * Get scene map name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Name of scene map.</p>
	 */
	const CNormalString& getSceneMapName() const;
	/**
	 * Select scene map.
	 *
	 * @param resourceManager Resource manager.
	 * @param name Name of scene map.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void selectSceneMap(CResourceManager* resourceManager,const CNormalString& name);

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
#endif //_CHARTLET_ATTRIBUTE_H_