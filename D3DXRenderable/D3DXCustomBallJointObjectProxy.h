///////////////////////////////////////////////////////////////////////////////
//
// D3DXCustomBallJointObjectProxy.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_CUSTOM_BALL_JOINT_OBJECT_PROXY_H_
#define _D3DX_CUSTOM_BALL_JOINT_OBJECT_PROXY_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXJointObjectProxy.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXCustomBallJointObjectProxy
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXCustomBallJointObjectProxy : CD3DXJointObjectProxy
{
public:
	CD3DXCustomBallJointObjectProxy(CD3DXJointObject* joint);
	virtual ~CD3DXCustomBallJointObjectProxy(void);

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

};

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_CUSTOM_BALL_JOINT_OBJECT_PROXY_H_
