///////////////////////////////////////////////////////////////////////////////
//
// D3DXCustomSliderJointObjectProxy.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_CUSTOM_SLIDER_JOINT_OBJECT_PROXY_H_
#define _D3DX_CUSTOM_SLIDER_JOINT_OBJECT_PROXY_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXJointObjectProxy.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXCustomSliderJointObjectProxy
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXCustomSliderJointObjectProxy : CD3DXJointObjectProxy
{
public:
	CD3DXCustomSliderJointObjectProxy(CD3DXJointObject* joint);
	virtual ~CD3DXCustomSliderJointObjectProxy(void);

protected:

	/**
	 * Setup common objects.
	 *
	 * @param iterator List node enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setupCommonObjects(CListNodeEnumeration& iterator);

protected:

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
#endif //_D3DX_CUSTOM_SLIDER_JOINT_OBJECT_PROXY_H_
