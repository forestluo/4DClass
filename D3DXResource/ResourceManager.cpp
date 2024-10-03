///////////////////////////////////////////////////////////////////////////////
//
// ResourceManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceManager.h"
#include "HashListContainer.h"

#include "D3DXDevice.h"
#include "D3DXFilter.h"
#include "D3DXEffect.h"
#include "D3DXTexture.h"
#include "D3DXLinestrip.h"
#include "D3DXPrimitive.h"
#include "D3DXFileMesh.h"

#include "DeviceManager.h"
#include "FilterManager.h"
#include "EffectManager.h"
#include "TextureManager.h"
#include "LinestripManager.h"
#include "PrimitiveManager.h"
#include "MeshManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
///////////////////////////////////////////////////////////////////////////////

#define GROUP_INSTANCE(p)									((CHashListContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

#pragma init_seg(".CRT$XCF")
//Manager Type
const _LONG CResourceManager::deviceManager = CDeviceManager::getClassCode();
const _LONG CResourceManager::filterManager = CFilterManager::getClassCode();
const _LONG CResourceManager::textureManager = CTextureManager::getClassCode();
const _LONG CResourceManager::effectManager = CEffectManager::getClassCode();
const _LONG CResourceManager::linestripManager = CLinestripManager::getClassCode();
const _LONG CResourceManager::primitiveManager = CPrimitiveManager::getClassCode();
const _LONG CResourceManager::meshManager = CMeshManager::getClassCode();

///////////////////////////////////////////////////////////////////////////////
//
// CResourceManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CResourceManager::CResourceManager(void)
{
	//Create groups.
	groups = new CHashListContainer();
#ifdef _DEBUG
	assert(groups != _NULL);
#endif

	//Create device manager.
	CDeviceManager* deviceManager = new CDeviceManager();
#ifdef _DEBUG
	assert(deviceManager != _NULL);
#endif
	//Add it into hash list container.
	GROUP_INSTANCE(groups)->setValue(CResourceManager::deviceManager,deviceManager);

	//Create filter manager.
	CFilterManager* filterManager = new CFilterManager();
#ifdef _DEBUG
	assert(filterManager != _NULL);
#endif
	//Add it into hash list container.
	GROUP_INSTANCE(groups)->setValue(CResourceManager::filterManager,filterManager);

	//Create texture manager.
	CTextureManager* textureManager = new CTextureManager();
#ifdef _DEBUG
	assert(textureManager != _NULL);
#endif
	//Add it into hash list container.
	GROUP_INSTANCE(groups)->setValue(CResourceManager::textureManager,textureManager);

	//Create effect manager.
	CEffectManager* effectManager = new CEffectManager();
#ifdef _DEBUG
	assert(effectManager != _NULL);
#endif
	//Add it into hash list container.
	GROUP_INSTANCE(groups)->setValue(CResourceManager::effectManager,effectManager);

	//Create linestrip manager.
	CLinestripManager* linestripManager = new CLinestripManager();
#ifdef _DEBUG
	assert(linestripManager != _NULL);
#endif
	//Add it into hash list container.
	GROUP_INSTANCE(groups)->setValue(CResourceManager::linestripManager,linestripManager);

	//Create primitive manager.
	CPrimitiveManager* primitiveManager = new CPrimitiveManager();
#ifdef _DEBUG
	assert(primitiveManager != _NULL);
#endif
	//Add it into hash list container.
	GROUP_INSTANCE(groups)->setValue(CResourceManager::primitiveManager,primitiveManager);

	//Create mesh manager.
	CMeshManager* meshManager = new CMeshManager();
#ifdef _DEBUG
	assert(meshManager != _NULL);
#endif
	//Add it into hash list container.
	GROUP_INSTANCE(groups)->setValue(CResourceManager::meshManager,meshManager);
}

///////////////////////////////////////////////////////////////////////////////
//
// CResourceManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CResourceManager::~CResourceManager(void)
{
	//Release all.
	releaseAll();
	//Check groups.
	if(groups != _NULL)
	{
		//Delete groups.
		delete (CHashListContainer *)groups;
		//Clear groups.
		groups = (CHashListContainer *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
/////////////////////////////////////////////////////////////////////////////////

void CResourceManager::releaseAll()
{
	//Create mesh manager.
	CD3DXResourceGroup* meshManager = getGroup(CResourceManager::meshManager);
	//Check result.
	if(meshManager != _NULL)
	{
#ifndef _DEBUG
		//Remove it from group.
		GROUP_INSTANCE(groups)->removeValue(CResourceManager::meshManager);
#else
		assert(GROUP_INSTANCE(groups)->removeValue(CResourceManager::meshManager) == meshManager);
#endif
		//Delete mesh manager.
		delete (CD3DXResourceGroup *)meshManager;
	}

	//Create primitive manager.
	CD3DXResourceGroup* primitiveManager = getGroup(CResourceManager::primitiveManager);
	//Check result.
	if(primitiveManager != _NULL)
	{
#ifndef _DEBUG
		//Remove it from group.
		GROUP_INSTANCE(groups)->removeValue(CResourceManager::primitiveManager);
#else
		assert(GROUP_INSTANCE(groups)->removeValue(CResourceManager::primitiveManager) == primitiveManager);
#endif
		//Delete primitive manager.
		delete (CD3DXResourceGroup *)primitiveManager;
	}

	//Create linestrip manager.
	CD3DXResourceGroup* linestripManager = getGroup(CResourceManager::linestripManager);
	//Check result.
	if(linestripManager != _NULL)
	{
#ifndef _DEBUG
		//Remove it from group.
		GROUP_INSTANCE(groups)->removeValue(CResourceManager::linestripManager);
#else
		assert(GROUP_INSTANCE(groups)->removeValue(CResourceManager::linestripManager) == linestripManager);
#endif
		//Delete linestrip manager.
		delete (CD3DXResourceGroup *)linestripManager;
	}

	//Create effect manager.
	CD3DXResourceGroup* effectManager = getGroup(CResourceManager::effectManager);
	//Check result.
	if(effectManager != _NULL)
	{
#ifndef _DEBUG
		//Remove it from group.
		GROUP_INSTANCE(groups)->removeValue(CResourceManager::effectManager);
#else
		assert(GROUP_INSTANCE(groups)->removeValue(CResourceManager::effectManager) == effectManager);
#endif
		//Delete effect manager.
		delete (CD3DXResourceGroup *)effectManager;
	}

	//Create texture manager.
	CD3DXResourceGroup* textureManager = getGroup(CResourceManager::textureManager);
	//Check result.
	if(textureManager != _NULL)
	{
#ifndef _DEBUG
		//Remove it from group.
		GROUP_INSTANCE(groups)->removeValue(CResourceManager::textureManager);
#else
		assert(GROUP_INSTANCE(groups)->removeValue(CResourceManager::textureManager) == textureManager);
#endif
		//Delete texture manager.
		delete (CD3DXResourceGroup *)textureManager;
	}

	//Create filter manager.
	CD3DXResourceGroup* filterManager = getGroup(CResourceManager::filterManager);
	//Check result.
	if(filterManager != _NULL)
	{
#ifndef _DEBUG
		//Remove it from group.
		GROUP_INSTANCE(groups)->removeValue(CResourceManager::filterManager);
#else
		assert(GROUP_INSTANCE(groups)->removeValue(CResourceManager::filterManager) == filterManager);
#endif
		//Delete filter manager.
		delete (CD3DXResourceGroup *)filterManager;
	}

	//Create device manager.
	CD3DXResourceGroup* deviceManager = getGroup(CResourceManager::deviceManager);
	//Check result.
	if(deviceManager != _NULL)
	{
#ifndef _DEBUG
		//Remove it from group.
		GROUP_INSTANCE(groups)->removeValue(CResourceManager::deviceManager);
#else
		assert(GROUP_INSTANCE(groups)->removeValue(CResourceManager::deviceManager) == deviceManager);
#endif
		//Delete device manager.
		delete (CD3DXResourceGroup *)deviceManager;
	}

#ifdef _DEBUG
	assert(GROUP_INSTANCE(groups)->getCount() == 0);
#endif
	//Clear all.
	GROUP_INSTANCE(groups)->clearAll();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CResourceManager::getCount(_LONG classCode) const
{
	//Get resource group.
	CD3DXResourceGroup* group = getGroup(classCode);
#ifdef _DEBUG
	assert(group != _NULL);
#endif
	//Return result.
	return group->getCount();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CResourceManager::getCount(_LONG majorClass,_LONG minorClass) const
{
	//Get resource group.
	CD3DXResourceGroup* group = getGroup(majorClass);
#ifdef _DEBUG
	assert(group != _NULL);
#endif
	//Return result.
	return group->getCount(minorClass);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetGroup
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResourceGroup* CResourceManager::getGroup(_LONG classCode) const
{
#ifdef _DEBUG
	assert(groups != _NULL);
#endif
	//Return result.
	return (CD3DXResourceGroup *)GROUP_INSTANCE(groups)->getValue(classCode);
}

///////////////////////////////////////////////////////////////////////////////
//
// AddGroup
//
///////////////////////////////////////////////////////////////////////////////

void CResourceManager::addGroup(_LONG classCode,CD3DXResourceGroup* group)
{
#ifdef _DEBUG
	assert(groups != _NULL);
#endif
	//Set value.
	GROUP_INSTANCE(groups)->setValue(classCode,group);
}

///////////////////////////////////////////////////////////////////////////////
//
// AddResource
//
///////////////////////////////////////////////////////////////////////////////

void CResourceManager::addResource(_LONG classCode,CD3DXResource* resource)
{
	//Get resource group.
	CD3DXResourceGroup* group = getGroup(classCode);
#ifdef _DEBUG
	assert(group != _NULL);
#endif
	//Add resource.
	group->addResource(resource);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResource
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResource* CResourceManager::getResource(_LONG classCode,const CNormalString& name)
{
	//Get resource group.
	CD3DXResourceGroup* group = getGroup(classCode);
#ifdef _DEBUG
	assert(group != _NULL);
#endif
	//Return result.
	return group->getResource(name);
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveResource
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResource* CResourceManager::removeResource(_LONG classCode,const CNormalString& name)
{
	//Get resource group.
	CD3DXResourceGroup* group = getGroup(classCode);
#ifdef _DEBUG
	assert(group != _NULL);
#endif
	//Return result.
	return group->removeResource(name);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEnumeration
//
///////////////////////////////////////////////////////////////////////////////

void CResourceManager::getEnumeration(_LONG classCode,CListNodeEnumeration& iterator)
{
	//Get resource group.
	CD3DXResourceGroup* group = getGroup(classCode);
#ifdef _DEBUG
	assert(group != _NULL);
#endif
	//Get enumeration.
	group->getEnumeration(iterator);
}

///////////////////////////////////////////////////////////////////////////////
//
// AddResource
//
///////////////////////////////////////////////////////////////////////////////

void CResourceManager::addResource(CD3DXResource* resource)
{
	//Check instance.
	if(IS_DEVICE_BASE(resource))
	{
		//Add it into device manager.
		CResourceManager::addResource(CResourceManager::deviceManager,resource);
	}
	else if(IS_FILTER_BASE(resource))
	{
		//Add it into filter manager.
		CResourceManager::addResource(CResourceManager::filterManager,resource);
	}
	else if(IS_TEXTURE_BASE(resource))
	{
		//Add it into texture manager.
		CResourceManager::addResource(CResourceManager::textureManager,resource);
	}
	else if(IS_EFFECT_BASE(resource))
	{
		//Add it into effect manager.
		CResourceManager::addResource(CResourceManager::effectManager,resource);
	}
	else if(IS_LINESTRIP_BASE(resource))
	{
		//Add it into linestrip manager.
		CResourceManager::addResource(CResourceManager::linestripManager,resource);
	}
	else if(IS_PRIMITIVE_BASE(resource))
	{
		//Add it into primitive manager.
		CResourceManager::addResource(CResourceManager::primitiveManager,resource);
	}
	else if(IS_FILEMESH_BASE(resource))
	{
		//Add it into primitive manager.
		CResourceManager::addResource(CResourceManager::meshManager,resource);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResource
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResource* CResourceManager::getResource(const CNormalString& name)
{
	//Enumeration.
	CListNodeEnumeration iterator;
#ifdef _DEBUG
	assert(groups != _NULL);
#endif
	//Get enumeration.
	GROUP_INSTANCE(groups)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get resource group.
		CD3DXResourceGroup* group = (CD3DXResourceGroup *)iterator.nextElement();
#ifdef _DEBUG
		assert(group != _NULL);
#endif
		//Get resource.
		CD3DXResource* resource = group->getResource(name);
		//Check result.
		if(resource != _NULL) return resource;
	}
	//Return null.
	return (CD3DXResource *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveResource
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResource* CResourceManager::removeResource(const CNormalString& name)
{
	//Enumeration.
	CListNodeEnumeration iterator;
#ifdef _DEBUG
	assert(groups != _NULL);
#endif
	//Get enumeration.
	GROUP_INSTANCE(groups)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get resource group.
		CD3DXResourceGroup* group = (CD3DXResourceGroup *)iterator.nextElement();
#ifdef _DEBUG
		assert(group != _NULL);
#endif
		//Get resource.
		CD3DXResource* resource = group->removeResource(name);
		//Check result.
		if(resource != _NULL) return resource;
	}
	//Return null.
	return (CD3DXResource *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CResourceManager::handleMessage1(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;
	//Group.
	CD3DXResourceGroup* group;

	//Get group.
	group = getGroup(CResourceManager::deviceManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::filterManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::textureManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::effectManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::linestripManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::primitiveManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::meshManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CResourceManager::handleMessage2(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;
	//Group.
	CD3DXResourceGroup* group;

	//Get group.
	group = getGroup(CResourceManager::meshManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::primitiveManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::linestripManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::effectManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::textureManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::filterManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Get group.
	group = getGroup(CResourceManager::deviceManager);
	//Check result.
	if(group != _NULL && FAILED(group->handleMessage(d3dxEvent))) hr = E_FAIL;

	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CResourceManager::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//On frame move.
	case d3dxOnFrameMove:
		//Handle message.
		handleMessage1(d3dxEvent);
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Handle message.
		handleMessage2(d3dxEvent);
		break;
		//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != NULL);
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		handleMessage1(d3dxEvent);
		break;
		//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Handle message.
		handleMessage2(d3dxEvent);
		break;
		//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		handleMessage1(d3dxEvent);
		break;
	}
	//Return result.
	return CD3DXDeviceReference::handleMessage(d3dxEvent);
}
