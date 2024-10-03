///////////////////////////////////////////////////////////////////////////////
//
// BumpScene.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _BUMP_SCENE_H_
#define _BUMP_SCENE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ForegroundScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// BumpScene
//
///////////////////////////////////////////////////////////////////////////////

class CBumpScene : public CForegroundScene
{
private:
	/**
	 * Index.
	 */
	_INTEGER index;
	/**
	 * Primitive object.
	 */
	CPrimitiveObject* floor;
	CPrimitiveObject* object;

public:
	CBumpScene(void);
	virtual ~CBumpScene(void);

protected:

	/**
	 * Initialize objects.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeObjects(CResourceManager* resourceManager);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent D3DXEvent.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_BUMP_SCENE_H_
