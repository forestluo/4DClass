///////////////////////////////////////////////////////////////////////////////
//
// D3DXJointObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_JOINT_OBJECT_H_
#define _D3DX_JOINT_OBJECT_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldJointObject.h"
#include "D3DXPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXJointObject
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXJointObject :
	public CD3DXRenderableObject,
	public virtual CWorldJointObject
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
	 * Proxy of joint.
	 */
	_OBJECT proxy;

private:
	/**
	 * Whether initialized.
	 */
	_BOOL initialized;

public:
	CD3DXJointObject(_INTEGER jointType);
	CD3DXJointObject(const CJointAttribute& attribute);
	virtual ~CD3DXJointObject(void);

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
	 * Pick object.
	 *
	 * @param pickRay Pick ray.
	 * @param result Pick result.
	 * @return
	 *     <p>Return true, if it is picked.</p>
	 */
	virtual _BOOL pick(CPickRay& pickRay,CPickResult& result);

public:

	/**
	 * Create objects.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createObjects(CResourceManager* resourceManager);

protected:

	/**
	 * Initialize objects of world.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeObjects(CResourceManager* resourceManager);

public:

	/**
	 * Set view port.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT setViewPort(CViewPort* viewPort);

protected:

	/**
	 * Dispatch message to objects.
	 *
	 * @param d3dxEvent DirectX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT dispatchMessage(const D3DXEvent& d3dxEvent);

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
#endif //_D3DX_JOINT_OBJECT_H_
