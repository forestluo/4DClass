///////////////////////////////////////////////////////////////////////////////
//
// D3DXScene.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_SCENE_H_
#define _D3DX_SCENE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "JointObject.h"
#include "PrimitiveObject.h"

#include "ArrayManager.h"
#include "ModelManager.h"
#include "JointModelManager.h"
#include "CompoundModelManager.h"

#include "PickedAttribute.h"
#include "CollisionAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXScene
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXScene :
	public CD3DXObject,
	public CArrayManager,
	public CModelManager,
	public CJointModelManager,
	public CCompoundModelManager,
	public CPickedAttribute,
	public CCollisionAttribute
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
	 * Whether initialized.
	 */
	_BOOL initialized;

public:
	CD3DXScene(void);
	virtual ~CD3DXScene(void);

protected:

	/**
	 * Initialize objects of world.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *    <p>Result of function.</p>
	 */
	virtual HRESULT initializeObjects(CResourceManager* resourceManager);

public:

	/**
	 * Add object.
	 *
	 * @param object Renderable object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void addObject(CD3DXRenderableObject* object);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent D3DX event.
	 * @return
	 *     <p>Result of handling message.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);
};

#define IS_SCENE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXScene::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_SCENE_H_
