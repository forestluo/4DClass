///////////////////////////////////////////////////////////////////////////////
//
// EffectManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "EffectManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "ResourceManager.h"

#include "D3DXEffect.h"

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
const C4DBase CEffectManager::base(L"CEffectManager",L"CD3DXResourceGroup");

///////////////////////////////////////////////////////////////////////////////
//
// Resource Description
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXEffectDescription
{
	const _STRING pClassName;
	const _STRING pName;
	const _STRING pFileName;
	_BOOL		  bReserved;

} D3DXEffectDescription;

//Resources
static const D3DXEffectDescription d3dxEffects[] =
{
	//Effect
	{L"CD3DXEffect",			EFFECT_SKETCH0,			L"Misc\\Effect\\Sketch.fx",			_TRUE},
	{L"CD3DXEffect",			EFFECT_ORIGIN,			L"Misc\\Effect\\Origin.fx",			_FALSE},
	{L"CD3DXEffect",			EFFECT_BASIC,			L"Misc\\Effect\\Basic.fx",			_FALSE},
	{L"CD3DXEffect",			EFFECT_DEFAULT,			L"Misc\\Effect\\Default.fx",		_FALSE},
	{L"CD3DXEffect",			EFFECT_REFLECT,			L"Misc\\Effect\\Reflect.fx",		_FALSE},
	{L"CD3DXEffect",			EFFECT_SPECULAR,		L"Misc\\Effect\\Specular.fx",		_FALSE},
	{L"CD3DXEffect",			EFFECT_TEXTURE,			L"Misc\\Effect\\Texture.fx",		_FALSE},
};

//Effect Count
static const int d3dxEffectCount = sizeof(d3dxEffects) / sizeof(D3DXEffectDescription);

///////////////////////////////////////////////////////////////////////////////
//
// CEffectManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CEffectManager::CEffectManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CEffectManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CEffectManager::~CEffectManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateResources
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CEffectManager::createResources(_OBJECT resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Load resources.
	for(_INTEGER i = 0;i < d3dxEffectCount;i ++)
	{
		//Get effect.
		CD3DXEffect* pEffect = (CD3DXEffect *)getResource(d3dxEffects[i].pName);
		//Prevent loading again.
		if(pEffect != _NULL) continue;
		//Get hash code.
		_LONG lClassCode = C4DString::hashCode((_STRING)d3dxEffects[i].pClassName);
		//Check result.
		if(lClassCode == CD3DXEffect::getClassCode())
		{
			//Create effect.
			pEffect = new CD3DXEffect();
#ifdef _DEBUG
			assert(pEffect != _NULL);
#endif
			//Set file name.
			((CD3DXEffect *)pEffect)->setFileName(d3dxEffects[i].pFileName);
		}
		//Set name and add it into list.
		if(pEffect != _NULL)
		{
			//Set name.
			pEffect->setName(d3dxEffects[i].pName);
			//Set reserved.
			pEffect->setReserved(d3dxEffects[i].bReserved);

			//Add effect.
			addResource(pEffect);
		}
	}
	//Return result.
	return S_OK;
}
