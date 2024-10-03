///////////////////////////////////////////////////////////////////////////////
//
// ResourceManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "HashListContainer.h"

#include "D3DXEffect.h"
#include "D3DXFileMesh.h"
#include "D3DXRenderable.h"
#include "D3DXStaticTexture.h"
#include "D3DXDynamicTexture.h"

#include "Axis0.h"
#include "Sketch0.h"
#include "Sketch1.h"
#include "D3DXPrimitive.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define RESOURCES_INSTANCE(p)								((CHashListContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Resource Description
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXResourceDescription
{
	const _STRING pClassName;
	const _STRING pName;
	const _STRING pEffectName;
	const _STRING pFileName;
	_BOOL		  bReserved;

} D3DXResourceDescription;

//Resources
static const D3DXResourceDescription d3dxResources[] =
{
	//Texture
	{L"CD3DXStaticTexture",		TEXTURE_BANANA,			NULL,				L"Misc\\Texture\\banana.bmp",		_FALSE},
	{L"CD3DXStaticTexture",		TEXTURE_TULIPS,			NULL,				L"Misc\\Texture\\Tulips.jpg",		_FALSE},

	//Effect
	{L"CD3DXEffect",			EFFECT_SKETCH0,			NULL,				L"Misc\\Effect\\Sketch.fx",			_TRUE},
	{L"CD3DXEffect",			EFFECT_ORIGIN,			NULL,				L"Misc\\Effect\\Origin.fx",			_FALSE},
	{L"CD3DXEffect",			EFFECT_BASIC,			NULL,				L"Misc\\Effect\\Basic.fx",			_FALSE},
	{L"CD3DXEffect",			EFFECT_DEFAULT,			NULL,				L"Misc\\Effect\\Default.fx",		_FALSE},
	{L"CD3DXEffect",			EFFECT_REFLECT,			NULL,				L"Misc\\Effect\\Reflect.fx",		_FALSE},
	{L"CD3DXEffect",			EFFECT_SPECULAR,		NULL,				L"Misc\\Effect\\Specular.fx",		_FALSE},
	{L"CD3DXEffect",			EFFECT_SAMPLE1,			NULL,				L"Misc\\Effect\\Texture.fx",		_FALSE},

	//Linestrip
	{L"CAxis0",					LINESTRIP_AXIS0,		EFFECT_BASIC,		NULL,								_TRUE},
	{L"CSketch0",				LINESTRIP_SKETCH0,		EFFECT_SKETCH0,		NULL,								_TRUE},
	{L"CSketch1",				LINESTRIP_SKETCH1,		EFFECT_SKETCH0,		NULL,								_TRUE},

	//Mesh
	{L"CD3DXFileMesh",			MESH_ARROW0,			EFFECT_REFLECT,		L"Misc\\Mesh\\arrow.x",				_FALSE},

	//Primitive
	{L"CTriangle0",				PRIMITIVE_TRIANGLE0,	EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CQuadrangle0",			PRIMITIVE_QUADRANGLE0,	EFFECT_REFLECT,		NULL,								_FALSE},

	{L"CCircle0",				PRIMITIVE_CIRCLE0,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCircle3",				PRIMITIVE_CIRCLE3,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCircle4",				PRIMITIVE_CIRCLE4,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCircle5",				PRIMITIVE_CIRCLE5,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCircle6",				PRIMITIVE_CIRCLE6,		EFFECT_REFLECT,		NULL,								_FALSE},

	{L"CPolygon4",				PRIMITIVE_POLYGON4,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CPolygon6",				PRIMITIVE_POLYGON6,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CPolygon8",				PRIMITIVE_POLYGON8,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CPolygon12",				PRIMITIVE_POLYGON12,	EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CPolygon20",				PRIMITIVE_POLYGON20,	EFFECT_REFLECT,		NULL,								_FALSE},

	{L"CCuboid0",				PRIMITIVE_CUBOID0,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CFloor0",				PRIMITIVE_FLOOR0,		EFFECT_REFLECT,		NULL,								_FALSE},

	{L"CCone0",					PRIMITIVE_CONE0,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCone3",					PRIMITIVE_CONE3,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCone4",					PRIMITIVE_CONE4,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCone6",					PRIMITIVE_CONE6,		EFFECT_REFLECT,		NULL,								_FALSE},

	{L"CCylinder0",				PRIMITIVE_CYLINDER0,	EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCylinder3",				PRIMITIVE_CYLINDER3,	EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCylinder5",				PRIMITIVE_CYLINDER5,	EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCylinder6",				PRIMITIVE_CYLINDER6,	EFFECT_REFLECT,		NULL,								_FALSE},

	{L"CFrustum0",				PRIMITIVE_FRUSTUM0,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CFrustum3",				PRIMITIVE_FRUSTUM3,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CFrustum4",				PRIMITIVE_FRUSTUM4,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CFrustum6",				PRIMITIVE_FRUSTUM6,		EFFECT_REFLECT,		NULL,								_FALSE},

	{L"CSphere0",				PRIMITIVE_SPHERE0,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CHemisphere0",			PRIMITIVE_HEMISPHERE0,	EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CCapsule0",				PRIMITIVE_CAPSULE0,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CChamferCylinder0",		PRIMITIVE_CHAMFERCYLINDER0,EFFECT_REFLECT,	NULL,								_FALSE},

};

//Resources Count
static const int d3dxResourceCount = sizeof(d3dxResources) / sizeof(D3DXResourceDescription);

///////////////////////////////////////////////////////////////////////////////
//
// CResourceManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CResourceManager::CResourceManager(void)
{
	//Create resources.
	resources = new CHashListContainer();
#ifdef _DEBUG
	assert(resources != _NULL);
#endif
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
	//Check resources.
	if(resources != _NULL)
	{
		//Delete resources.
		delete (CHashListContainer *)resources;
		//Clear resources.
		resources = (CHashListContainer *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ReleaseResources
//
// Some resources need reload, some need not.
// Currently, just release all of it. And reload all from file again.
// Should be careful to the reference of these object. All the references should be updated.
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CResourceManager::releaseResources()
{
	//Release all.
	releaseAll();
	//Return result.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateResources
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CResourceManager::createResources(IDirect3DDevice9* pd3dDevice)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(resources != _NULL);
	assert(pd3dDevice != _NULL);
#endif

	//Load resources.
	for(_INTEGER i = 0;i < d3dxResourceCount;i ++)
	{
		//Get resources.
		CD3DXResource* pResource = getResource(d3dxResources[i].pName);
		//Prevent loading again.
		if(pResource != _NULL) continue;
		//Get hash code.
		_LONG lClassCode = C4DString::hashCode((_STRING)d3dxResources[i].pClassName);

		//Check type of resource.
		if(lClassCode == CD3DXStaticTexture::getClassCode())
		{
			//Create texture.
			pResource = new CD3DXStaticTexture();
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
			//Set file name.
			((CD3DXStaticTexture *)pResource)->setFileName(d3dxResources[i].pFileName);
			//Load from file.
			V_RETURN(((CD3DXStaticTexture *)pResource)->loadFromFile(pd3dDevice,d3dxResources[i].pFileName));
		}
		else if(lClassCode == CD3DXEffect::getClassCode())
		{
			//Create effect.
			pResource = new CD3DXEffect();
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
			//Set file name.
			((CD3DXEffect *)pResource)->setFileName(d3dxResources[i].pFileName);
			//Load from file.
			V_RETURN(((CD3DXEffect *)pResource)->loadFromFile(pd3dDevice,d3dxResources[i].pFileName));
		}
		//Check result.
		if(pResource != _NULL)
		{
			//Set name and add it into list.
			pResource->setName(d3dxResources[i].pName); addResource(pResource);
		}
	}

	//Load resources.
	for(_INTEGER i = 0;i < d3dxResourceCount;i ++)
	{
		//Get resources.
		CD3DXResource* pResource = getResource(d3dxResources[i].pName);
		//Prevent loading again.
		if(pResource != _NULL) continue;
		//Get hash code.
		_LONG lClassCode = C4DString::hashCode((_STRING)d3dxResources[i].pClassName);

		//Check type of resource.
		if(lClassCode == CD3DXFileMesh::getClassCode())
		{
			//Create file mesh.
			pResource = new CD3DXFileMesh();
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
			//Set file name.
			((CD3DXFileMesh *)pResource)->setFileName(d3dxResources[i].pFileName);
			//Load from file.
			V_RETURN(((CD3DXFileMesh *)pResource)->loadFromFile(pd3dDevice,d3dxResources[i].pFileName));
		}
		else if(lClassCode == CAxis0::getClassCode())
		{
			//Create axis.
			pResource = new CAxis0();
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == CSketch0::getClassCode())
		{
			//Create axis.
			pResource = new CSketch0();
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == CSketch1::getClassCode())
		{
			//Create axis.
			pResource = new CSketch1();
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CTriangle0"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::triangle0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle0"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::circle0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle3"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::circle3Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle4"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::circle4Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle5"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::circle5Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle6"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::circle6Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon4"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::polygon4Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon6"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::polygon6Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon8"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::polygon8Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon12"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::polygon12Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon20"))
		{
			//Create triangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::polygon20Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CQuadrangle0"))
		{
			//Create quadrangle.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::quadrangle0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCuboid0"))
		{
			//Create cuboid.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cuboid0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFloor0"))
		{
			//Create cuboid.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::floor0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCone0"))
		{
			//Create cone.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cone0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCone3"))
		{
			//Create cone.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cone3Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCone4"))
		{
			//Create cone.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cone4Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCone6"))
		{
			//Create cone.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cone6Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCylinder0"))
		{
			//Create cylinder.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cylinder0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCylinder3"))
		{
			//Create cylinder.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cylinder3Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCylinder5"))
		{
			//Create cylinder.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cylinder5Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode ==  C4DString::hashCode(L"CCylinder6"))
		{
			//Create cylinder.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::cylinder6Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFrustum0"))
		{
			//Create frustum.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::frustum0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFrustum3"))
		{
			//Create frustum.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::frustum3Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFrustum4"))
		{
			//Create frustum.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::frustum4Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFrustum6"))
		{
			//Create frustum.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::frustum6Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CSphere0"))
		{
			//Create sphere.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::sphere0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CHemisphere0"))
		{
			//Create hemisphere.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::hemisphere0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCapsule0"))
		{
			//Create capsule.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::capsule0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CChamferCylinder0"))
		{
			//Create capsule.
			pResource = new CD3DXPrimitive(CPrimitiveAttribute::chamferCylider0Primitive);
#ifdef _DEBUG
			assert(pResource != _NULL);
#endif
		}
		//Check result.
		if(pResource != _NULL)
		{
			//Set name and add it into list.
			pResource->setName(d3dxResources[i].pName); addResource(pResource);
		}
	}

	//Select effect after all loading process.
	for(int i = 0;i < d3dxResourceCount;i ++)
	{
		//Get resources.
		CD3DXResource* pResource = getResource(d3dxResources[i].pName);

#ifdef _DEBUG
		assert(pResource != NULL);
#endif
		//Check reserved.
		pResource->setReserved(d3dxResources[i].bReserved);
		//Check renderable.
		if(IS_RENDERABLE_BASE(pResource))
		{
			//Set basic resource.
			((CD3DXRenderable *)pResource)->setBasicResource(_TRUE);
			//Select effect.
			((CD3DXRenderable *)pResource)->selectEffect(this,d3dxResources[i].pEffectName);
		}
	}
	//Return result.
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
/////////////////////////////////////////////////////////////////////////////////

void CResourceManager::releaseAll()
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(resources != _NULL);
#endif

	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get resources.
		CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
		assert(resource != _NULL);
#endif
		//Get hash code.
		_LONG hashCode = C4DString::hashCode((_STRING)resource->getName().getCString());
		//Check base.
		if(IS_RENDERABLE_BASE(resource))
		{
			//Remove value.
			RESOURCES_INSTANCE(resources)->removeValue(hashCode);
			//Delete resource.
			delete (CD3DXRenderable *)resource;
		}
	}

	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get resources.
		CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
		assert(resource != _NULL);
#endif
		//Get hash code.
		_LONG hashCode = C4DString::hashCode((_STRING)resource->getName().getCString());
		//Check base.
		if(IS_EFFECT_BASE(resource))
		{
			//Remove value.
			RESOURCES_INSTANCE(resources)->removeValue(hashCode);
			//Delete resource.
			delete (CD3DXEffect *)resource;
		}
	}

	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get resources.
		CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
		assert(resource != _NULL);
#endif
		//Get hash code.
		_LONG hashCode = C4DString::hashCode((_STRING)resource->getName().getCString());
		//Check base.
		if(IS_TEXTURE_BASE(resource))
		{
			//Remove value and delete resource.
			RESOURCES_INSTANCE(resources)->removeValue(hashCode);
			//Delete resource.
			delete (CD3DXTexture *)resource;
		}
	}

	//Clear members.
	RESOURCES_INSTANCE(resources)->clearAll();
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddResource
//
/////////////////////////////////////////////////////////////////////////////////

void CResourceManager::addResource(CD3DXResource* resource)
{
#ifdef _DEBUG
	assert(resource != _NULL);
	assert(resource->getName().length() > 0);
#endif

#ifndef _DEBUG
	//Add it into map.
	RESOURCES_INSTANCE(resources)->setValue(C4DString::hashCode((_STRING)resource->getName().getCString()),(_OBJECT)resource);
#else
	//Add it into map.
	assert(RESOURCES_INSTANCE(resources)->setValue(C4DString::hashCode((_STRING)resource->getName().getCString()),(_OBJECT)resource) == _NULL);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetResource
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXResource* CResourceManager::getResource(const CNormalString& name)
{
#ifdef _DEBUG
	assert(name.length() > 0);
	assert(resources != _NULL);
#endif
	//Get value.
	return (CD3DXResource *)RESOURCES_INSTANCE(resources)->getValue(C4DString::hashCode((_STRING)name.getCString()));
}

/////////////////////////////////////////////////////////////////////////////////
//
// RemoveResource
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXResource* CResourceManager::removeResource(const CNormalString& name)
{
#ifdef _DEBUG
	assert(name.length() > 0);
	assert(resources != _NULL);
#endif
	//Get value.
	return (CD3DXResource *)RESOURCES_INSTANCE(resources)->removeValue(C4DString::hashCode((_STRING)name.getCString()));
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetEnumeration.
//
/////////////////////////////////////////////////////////////////////////////////

void CResourceManager::getEnumeration(CListNodeEnumeration& enumeration)
{
#ifdef _DEBUG
	assert(resources != _NULL);
#endif
	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&enumeration);
}

/////////////////////////////////////////////////////////////////////////////////
//
// DispatchMessage
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CResourceManager::dispatchMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(resources != _NULL);
#endif

	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get resource.
		CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
		assert(resource != _NULL);
#endif
		//Handle message.
		if(FAILED(resource->handleMessage(d3dxEvent))) hr = E_FAIL;
	}
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
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//On frame move.
	case d3dxOnFrameMove:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		//Release resources.
		V_RETURN(releaseResources());
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Create resources.
		V_RETURN(createResources(d3dxEvent.d3dxCreateDevice9.pd3dDevice));
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	}
	//Return result.
	return CDeviceManager::handleMessage(d3dxEvent);
}
