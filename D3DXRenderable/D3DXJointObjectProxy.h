///////////////////////////////////////////////////////////////////////////////
//
// D3DXJointObjectProxy.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_JOINT_OBJECT_PROXY_H_
#define _D3DX_JOINT_OBJECT_PROXY_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXJointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXJointObjectProxy
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXJointObjectProxy
{
protected:

	/**
	 * Joint.
	 */
	_OBJECT joint;

protected:

	/**
	 * Child handle of joint.
	 */
	CD3DXPrimitiveObject* childHandle;

	/**
	 * Parent handle of joint.
	 */
	CD3DXPrimitiveObject* parentHandle;

public:
	CD3DXJointObjectProxy(CD3DXJointObject* joint);
	virtual ~CD3DXJointObjectProxy(void);

protected:

	/**
	 * Get physics child.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Physics child.</p>
	 */
	CPhysicsObject* getPhysicsChild() const;
	/**
	 * Get physics parent.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Physics parent.</p>
	 */
	CPhysicsObject* getPhysicsParent() const;

protected:

	/**
	 * Get relative direction.
	 *
	 * <p>Relative direction of child or parent.
	 * This will keep as a constant value when simulation is running.</p>
	 *
	 * @param childFlag Whether is child or not (or parent).
	 * @return
	 *     <p>Relative direction of child or parent.</p>
	 */
	C4DVector3 getRelativeDirection(_BOOL childFlag) const;

	/**
	 * Get next object.
	 *
	 * @param iterator Enumeration.
	 * @return
	 *     <p>Renderable object.</p>
	 */
	static CD3DXRenderableObject* nextObject(CListNodeEnumeration& iterator);

public:

	/**
	 * Setup objects.
	 *
	 * @param iterator List node enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setupObjects();

protected:

	/**
	 * Setup objects of child.
	 *
	 * @param iterator List node enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setupChildObjects(CListNodeEnumeration& iterator);

	/**
	 * Setup objects of parent.
	 *
	 * @param iterator List node enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setupParentObjects(CListNodeEnumeration& iterator);

	/**
	 * Setup common objects.
	 *
	 * @param iterator List node enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setupCommonObjects(CListNodeEnumeration& iterator);

public:

	/**
	 * Initialize objects of world.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeObjects(CResourceManager* resourceManager);

protected:

	/**
	 * Create objects of child.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual HRESULT createChildObjects(CResourceManager* resourceManager);

	/**
	 * Create objects of parent.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual HRESULT createParentObjects(CResourceManager* resourceManager);

	/**
	 * Create common objects.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual HRESULT createCommonObjects(CResourceManager* resourceManager);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_JOINT_OBJECT_PROXY_H_
