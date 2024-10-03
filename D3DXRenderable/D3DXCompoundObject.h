///////////////////////////////////////////////////////////////////////////////
//
// D3DXCompoundObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_COMPOUND_OBJECT_H_
#define _D3DX_COMPOUND_OBJECT_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXPrimitiveObject.h"
#include "ResourceApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXCompoundObject
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXCompoundObject :
	public CD3DXRenderableObject
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
	CD3DXCompoundObject(void);
	virtual ~CD3DXCompoundObject(void);

public:

	/**
	 * Clear texture.
	 *
	 * @param name Name of texture.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearTexture(const CNormalString& name);

protected:

	/**
	 * Add object.
	 *
	 * @param object Basic object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void addObject(CD3DXRenderableObject* object);
	/**
	 * Add primitive object.
	 *
	 * @param resourceManager Resource manager.
	 * @param name Name of model.
	 * @return
	 *     <p>Created primitive object.</p>
	 */
	CD3DXPrimitiveObject* addObject(CResourceManager* resourceManager,const CNormalString& name);

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
	 * @param resourceApplication Resource application.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL createObjects(CResourceApplication* resourceApplication);

protected:

	/**
	 * Initialize objects of world.
	 *
	 * @param resourceApplication Resource application.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeObjects(CResourceApplication* resourceApplication);

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
#endif //_D3DX_COMPOUND_OBJECT_H_
