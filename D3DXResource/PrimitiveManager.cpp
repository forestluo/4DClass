///////////////////////////////////////////////////////////////////////////////
//
// PrimitiveManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PrimitiveManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "ResourceManager.h"

#include "D3DXPrimitive.h"

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
const C4DBase CPrimitiveManager::base(L"CPrimitiveManager",L"CD3DXResourceGroup");

///////////////////////////////////////////////////////////////////////////////
//
// Resource Description
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXPrimitiveDescription
{
	const _STRING pClassName;
	const _STRING pName;
	const _STRING pEffectName;
	const _STRING pFileName;
	_BOOL		  bReserved;

} D3DXPrimitiveDescription;

//Resources
static const D3DXPrimitiveDescription d3dxPrimitives[] =
{
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

	{L"CGrid4x3",				PRIMITIVE_GRID4x3,		EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CGrid20x15",				PRIMITIVE_GRID20x15,	EFFECT_REFLECT,		NULL,								_FALSE},
	{L"CGrid80x60",				PRIMITIVE_GRID80x60,	EFFECT_REFLECT,		NULL,								_FALSE},
};

//Primitive Count
static const int d3dxPrimitiveCount = sizeof(d3dxPrimitives) / sizeof(D3DXPrimitiveDescription);

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CPrimitiveManager::CPrimitiveManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveManager::~CPrimitiveManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateResources
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CPrimitiveManager::createResources(_OBJECT resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Load resources.
	for(_INTEGER i = 0;i < d3dxPrimitiveCount;i ++)
	{
		//Get primitive.
		CD3DXPrimitive* pPrimitive = (CD3DXPrimitive *)getResource(d3dxPrimitives[i].pName);
		//Prevent loading again.
		if(pPrimitive != _NULL) continue;
		//Get hash code.
		_LONG lClassCode = C4DString::hashCode((_STRING)d3dxPrimitives[i].pClassName);
		//Check result.
		if(lClassCode == C4DString::hashCode(L"CTriangle0"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::triangle0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle0"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::circle0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle3"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::circle3Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle4"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::circle4Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle5"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::circle5Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCircle6"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::circle6Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon4"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::polygon4Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon6"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::polygon6Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon8"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::polygon8Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon12"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::polygon12Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CPolygon20"))
		{
			//Create triangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::polygon20Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CQuadrangle0"))
		{
			//Create quadrangle.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::quadrangle0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCuboid0"))
		{
			//Create cuboid.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cuboid0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFloor0"))
		{
			//Create cuboid.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::floor0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCone0"))
		{
			//Create cone.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cone0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCone3"))
		{
			//Create cone.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cone3Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCone4"))
		{
			//Create cone.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cone4Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCone6"))
		{
			//Create cone.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cone6Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCylinder0"))
		{
			//Create cylinder.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cylinder0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCylinder3"))
		{
			//Create cylinder.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cylinder3Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCylinder5"))
		{
			//Create cylinder.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cylinder5Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode ==  C4DString::hashCode(L"CCylinder6"))
		{
			//Create cylinder.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::cylinder6Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFrustum0"))
		{
			//Create frustum.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::frustum0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFrustum3"))
		{
			//Create frustum.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::frustum3Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFrustum4"))
		{
			//Create frustum.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::frustum4Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CFrustum6"))
		{
			//Create frustum.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::frustum6Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CSphere0"))
		{
			//Create sphere.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::sphere0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CHemisphere0"))
		{
			//Create hemisphere.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::hemisphere0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CCapsule0"))
		{
			//Create capsule.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::capsule0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CChamferCylinder0"))
		{
			//Create capsule.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::chamferCylider0Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CGrid4x3"))
		{
			//Create grid.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::grid4x3Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CGrid20x15"))
		{
			//Create grid.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::grid20x15Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
		else if(lClassCode == C4DString::hashCode(L"CGrid80x60"))
		{
			//Create grid.
			pPrimitive = new CD3DXPrimitive(CPrimitiveAttribute::ground80x60Primitive);
#ifdef _DEBUG
			assert(pPrimitive != _NULL);
#endif
		}
#ifdef _DEBUG
		else assert(_FALSE);
#endif
		//Set name and add it into list.
		if(pPrimitive != _NULL)
		{
			//Set name.
			pPrimitive->setName(d3dxPrimitives[i].pName);
			//Set reserved.
			pPrimitive->setReserved(d3dxPrimitives[i].bReserved);

			//Set basic resource.
			pPrimitive->setBasicResource(_TRUE);
			//Select effect.
			pPrimitive->selectEffect(MANAGER_INSTANCE(resourceManager),d3dxPrimitives[i].pEffectName);

			//Add primitive.
			addResource(pPrimitive);
		}
	}
	//Return result.
	return S_OK;
}
