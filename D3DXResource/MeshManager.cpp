///////////////////////////////////////////////////////////////////////////////
//
// MeshManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "MeshManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "ResourceManager.h"

#include "D3DXFileMesh.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MANAGER_INSTANCE(p)									((CResourceManager *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

#pragma init_seg(".CRT$XCE")
//Set base of object.
const C4DBase CMeshManager::base(L"CMeshManager",L"CD3DXResourceGroup");

///////////////////////////////////////////////////////////////////////////////
//
// Resource Description
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXFileMeshDescription
{
	const _STRING pClassName;
	const _STRING pName;
	const _STRING pEffectName;
	const _STRING pFileName;
	_BOOL		  bReserved;

} D3DXFileMeshDescription;

//Meshes
static const D3DXFileMeshDescription d3dxFileMeshes[] =
{
	//Mesh
	{L"CD3DXFileMesh",			MESH_ARROW0,			EFFECT_REFLECT,		L"Misc\\Mesh\\arrow.x",				_FALSE},
};

//File Mesh Count
static const int d3dxFileMeshCount = sizeof(d3dxFileMeshes) / sizeof(D3DXFileMeshDescription);

///////////////////////////////////////////////////////////////////////////////
//
// CMeshManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CMeshManager::CMeshManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CMeshManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CMeshManager::~CMeshManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateResources
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMeshManager::createResources(_OBJECT resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Load resources.
	for(_INTEGER i = 0;i < d3dxFileMeshCount;i ++)
	{
		//Get file mesh.
		CD3DXFileMesh* pFileMesh = (CD3DXFileMesh *)getResource(d3dxFileMeshes[i].pName);
		//Prevent loading again.
		if(pFileMesh != _NULL) continue;
		//Get hash code.
		_LONG lClassCode = C4DString::hashCode((_STRING)d3dxFileMeshes[i].pClassName);
		//Check type of resource.
		if(lClassCode == CD3DXFileMesh::getClassCode())
		{
			//Create file mesh.
			pFileMesh = new CD3DXFileMesh();
#ifdef _DEBUG
			assert(pFileMesh != _NULL);
#endif
			//Set file name.
			((CD3DXFileMesh *)pFileMesh)->setFileName(d3dxFileMeshes[i].pFileName);
		}
		//Set name and add it into list.
		if(pFileMesh != _NULL)
		{
			//Set name.
			pFileMesh->setName(d3dxFileMeshes[i].pName);
			//Set reserved.
			pFileMesh->setReserved(d3dxFileMeshes[i].bReserved);

			//Set basic resource.
			pFileMesh->setBasicResource(_TRUE);
			//Select effect.
			pFileMesh->selectEffect(MANAGER_INSTANCE(resourceManager),d3dxFileMeshes[i].pEffectName);

			//Add file mesh.
			addResource(pFileMesh);
		}
	}
	//Return result.
	return S_OK;
}
