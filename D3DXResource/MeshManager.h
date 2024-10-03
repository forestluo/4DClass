///////////////////////////////////////////////////////////////////////////////
//
// MeshManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MESH_MANAGER_H_
#define _MESH_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
//
// MeshManager
//
///////////////////////////////////////////////////////////////////////////////

class CMeshManager : public CD3DXResourceGroup
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

public:
	CMeshManager(void);
	virtual ~CMeshManager(void);

protected:

	/**
	 * Create resources.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT createResources(_OBJECT resourceManager);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_MESH_MANAGER_H_
