///////////////////////////////////////////////////////////////////////////////
//
// D3DXClassicCorkscrewJointObjectProxy.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_CLASSIC_CORKSCREW_JOINT_OBJECT_PROXY_H_
#define _D3DX_CLASSIC_CORKSCREW_JOINT_OBJECT_PROXY_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXJointObjectProxy.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXClassicCorkscrewJointObjectProxy
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXClassicCorkscrewJointObjectProxy : CD3DXJointObjectProxy
{
public:
	CD3DXClassicCorkscrewJointObjectProxy(CD3DXJointObject* joint);
	virtual ~CD3DXClassicCorkscrewJointObjectProxy(void);

protected:

	/**
	 * Setup common objects.
	 *
	 * @param iterator List node enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setupCommonObjects(CListNodeEnumeration& iterator);

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
#endif //_D3DX_CLASSIC_CORKSCREW_JOINT_OBJECT_PROXY_H_
