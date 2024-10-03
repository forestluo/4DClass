///////////////////////////////////////////////////////////////////////////////
//
// SceneApplication.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _SCENE_APPLICATION_H_
#define _SCENE_APPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DLock.h"
#include "D3DXObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ForegroundScene.h"
#include "BackgroundScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// SceneApplication
//
///////////////////////////////////////////////////////////////////////////////

class CSceneApplication :
	public virtual C4DLock,
	public virtual CD3DXObject
{
private:
	/**
	 * Foreground.
	 */
	CForegroundScene* foreground;
	/**
	 * Background.
	 */
	CBackgroundScene* background;

public:
	CSceneApplication(void);
	virtual ~CSceneApplication(void);

protected:

	/**
	 * Clear background.
	 *
	 * @param d3dxDevice Direct device.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearBackground(IDirect3DDevice9* d3dxDevice);

	/**
	 * Set render state before rendering.
	 *
	 * @param d3dxDevice Direct device.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initializeRenderState(IDirect3DDevice9* pd3dDevice);

public:
	

	/**
	 * Get foreground.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Foreround scene.</p>
	 */
	CForegroundScene* getForeground() const;

	/**
	 * Set foreground.
	 *
	 * @param foreground Foreground scene.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setForeground(CForegroundScene* foreground);

public:

	/**
	 * Get background.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Background scene.</p>
	 */
	CBackgroundScene* getBackground() const;

	/**
	 * Set background.
	 *
	 * @param background Background scene.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setBackground(CBackgroundScene* background);

public:

	/**
	 * Clear texture.
	 *
	 * @param name Name of texture.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearTexture(const CNormalString& name);

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
#endif //_SCENE_APPLICATION_H_
