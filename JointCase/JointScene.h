///////////////////////////////////////////////////////////////////////////////
//
// JointScene.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _JOINT_SCENE_H_
#define _JOINT_SCENE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "JointObject.h"
#include "ForegroundScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// JointScene
//
///////////////////////////////////////////////////////////////////////////////

class CJointScene : public CForegroundScene
{
private:
	/**
	 * Index.
	 */
	_INTEGER index;
	/**
	 * Joint object.
	 */
	CJointObject* joint;
	/**
	 * Child object.
	 */
	CPrimitiveObject* child;
	/**
	 * Parent object.
	 */
	CPrimitiveObject* parent;

public:
	CJointScene(void);
	virtual ~CJointScene(void);

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
#endif //_JOINT_SCENE_H_
