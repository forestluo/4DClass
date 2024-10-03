///////////////////////////////////////////////////////////////////////////////
//
// ChartletAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ChartletAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CChartletAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CChartletAttribute::CChartletAttribute(void)
{
	//Set default value.
	sceneMap = (CD3DXTexture *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CChartletAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CChartletAttribute::~CChartletAttribute(void)
{
	//Check texture.
	if(sceneMap != _NULL)
	{
		//Release reference.
		sceneMap->releaseReference();
		//Clear reference.
		sceneMap = (CD3DXTexture *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearTexture
//
///////////////////////////////////////////////////////////////////////////////

void CChartletAttribute::clearTexture(const CNormalString& name)
{
	//Check result.
	if(sceneMapName == name)
	{
		//Check texture.
		if(sceneMap != _NULL)
		{
			//Release reference.
			sceneMap->releaseReference();
			//Clear reference.
			sceneMap = (CD3DXTexture *)_NULL;
		}
		//Clear name of scene map.
		sceneMapName.clearAll();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSceneMap
//
///////////////////////////////////////////////////////////////////////////////

CD3DXTexture* CChartletAttribute::getSceneMap() const
{
	//Return result.
	return sceneMap;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSceneMapName
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CChartletAttribute::getSceneMapName() const
{
	//Return result.
	return sceneMapName;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SelectSceneMap
//
/////////////////////////////////////////////////////////////////////////////////

void CChartletAttribute::selectSceneMap(CResourceManager* resourceManager,const CNormalString& name)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	///////////////////////////////////////
	//
	// Clear previous scene map.
	//
	//Check scene map.
	if(sceneMap != _NULL)
	{
		//Release reference.
		sceneMap->releaseReference();
		//Clear scene map.
		sceneMap = (CD3DXTexture *)_NULL;
	}
	//
	///////////////////////////////////////

	//Set name.
	sceneMapName = name;
	//Check name.
	if(name.length() > 0)
	{
		///////////////////////////////////////
		//
		// Select texture from resources.
		//
		//Get resource.
		CD3DXResource* resource = resourceManager->getResource(name);
#ifdef _DEBUG
		assert(resource != NULL);
		assert(IS_TEXTURE_BASE(resource));
#endif
		//Add reference.
		resource->addReference();
		//Set scene map.
		sceneMap = (CD3DXTexture *)resource;
		//
		///////////////////////////////////////
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CChartletAttribute::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	//Do not dispatch any message to its effect or property.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		///////////////////////////////////////
		//
		//Check texture.
		if(sceneMap != _NULL)
		{
			//Release reference.
			sceneMap->releaseReference();
			//Clear texture.
			sceneMap = (CD3DXTexture *)_NULL;
		}
		//
		///////////////////////////////////////
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
		assert(d3dxEvent.pUserContext != NULL);
#endif
		///////////////////////////////////////
		//
		//select scene map.
		selectSceneMap(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager(),sceneMapName);
		//
		///////////////////////////////////////
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
