///////////////////////////////////////////////////////////////////////////////
//
// LinestripManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "LinestripManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "ResourceManager.h"

#include "Axis0.h"
#include "Sketch0.h"
#include "Sketch1.h"

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
const C4DBase CLinestripManager::base(L"CLinestripManager",L"CD3DXResourceGroup");

///////////////////////////////////////////////////////////////////////////////
//
// Resource Description
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXLinestripDescription
{
	const _STRING pClassName;
	const _STRING pName;
	const _STRING pEffectName;
	const _STRING pFileName;
	_BOOL		  bReserved;

} D3DXLinestripDescription;

//Resources
static const D3DXLinestripDescription d3dxLinestrips[] =
{
	//Linestrip
	{L"CAxis0",					LINESTRIP_AXIS0,		EFFECT_BASIC,		NULL,								_TRUE},
	{L"CSketch0",				LINESTRIP_SKETCH0,		EFFECT_SKETCH0,		NULL,								_TRUE},
	{L"CSketch1",				LINESTRIP_SKETCH1,		EFFECT_SKETCH0,		NULL,								_TRUE},
};

//Linestrip Count
static const int d3dxLinestripCount = sizeof(d3dxLinestrips) / sizeof(D3DXLinestripDescription);

///////////////////////////////////////////////////////////////////////////////
//
// CLinestripManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CLinestripManager::CLinestripManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CLinestripManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CLinestripManager::~CLinestripManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateResources
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CLinestripManager::createResources(_OBJECT resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Load resources.
	for(_INTEGER i = 0;i < d3dxLinestripCount;i ++)
	{
		//Get linestrip.
		CD3DXLinestrip* pLinestrip = (CD3DXLinestrip *)getResource(d3dxLinestrips[i].pName);
		//Prevent loading again.
		if(pLinestrip != _NULL) continue;
		//Get hash code.
		_LONG lClassCode = C4DString::hashCode((_STRING)d3dxLinestrips[i].pClassName);
		//Check result.
		if(lClassCode == CAxis0::getClassCode())
		{
			//Create axis.
			pLinestrip = new CAxis0();
#ifdef _DEBUG
			assert(pLinestrip != _NULL);
#endif
		}
		else if(lClassCode == CSketch0::getClassCode())
		{
			//Create axis.
			pLinestrip = new CSketch0();
#ifdef _DEBUG
			assert(pLinestrip != _NULL);
#endif
		}
		else if(lClassCode == CSketch1::getClassCode())
		{
			//Create axis.
			pLinestrip = new CSketch1();
#ifdef _DEBUG
			assert(pLinestrip != _NULL);
#endif
		}
		//Set name and add it into list.
		if(pLinestrip != _NULL)
		{
			//Set name.
			pLinestrip->setName(d3dxLinestrips[i].pName);
			//Set reserved.
			pLinestrip->setReserved(d3dxLinestrips[i].bReserved);

			//Set basic resource.
			pLinestrip->setBasicResource(_TRUE);
			//Select effect.
			pLinestrip->selectEffect(MANAGER_INSTANCE(resourceManager),d3dxLinestrips[i].pEffectName);

			//Add linestrip.
			addResource(pLinestrip);
		}
	}
	//Return result.
	return S_OK;
}
