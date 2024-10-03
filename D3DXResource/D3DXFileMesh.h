///////////////////////////////////////////////////////////////////////////////
//
// D3DXFileMesh.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_FILE_MESH_H_
#define _D3DX_FILE_MESH_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXRenderable.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXFileMesh
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXFileMesh : public CD3DXRenderable
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
	 * File Mesh.
	 */
	_OBJECT mesh;
	/**
	 * File name.
	 */
	CNormalString fileName;

public:
	CD3DXFileMesh(void);
	virtual ~CD3DXFileMesh(void);

public:

	/**
	 * Get mesh handle.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Handle of mesh.</p>
	 */
	_OBJECT getMesh() const;

public:

	/**
	 * Get file name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Name of file.</p>
	 */
	const CNormalString& getFileName() const;
	/**
	 * Set file name.
	 *
	 * @param fileName Name of file.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFileName(const CNormalString& fileName);

public:

	/**
	 * Pick
	 *
	 * @param pickRay Pick ray.
	 * @return
	 *     <p>Pick intersection.</p>
	 */
	virtual CPickIntersection* pick(CPickRay& pickRay);

public:

	/**
	 * Render.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param effect Effect.
	 * @return
	 *    <p>Result of function.</p>
	 */
	virtual HRESULT render(IDirect3DDevice9* pd3dDevice,CD3DXEffect* effect);

public:

	/**
	 * Load from file.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param fileName Name of file.
	 * @return
	 *     <p>Result of function.</p>
	 */
    virtual HRESULT loadFromFile(IDirect3DDevice9* pd3dDevice,const CNormalString& fileName);

public:
	
	/**
	 * Handle message.
	 *
	 * @param d3dxEvent D3DX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);
};

#define IS_FILEMESH_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXFileMesh::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_FILE_MESH_H_