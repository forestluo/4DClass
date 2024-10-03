///////////////////////////////////////////////////////////////////////////////
//
// TextureManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "TextureManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "ResourceManager.h"

#include "D3DXStaticTexture.h"
#include "D3DXDynamicTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MANAGER_INSTANCE(p)									((CResourceManager *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Resource Description
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXTextureDescription
{
	const _STRING pClassName;
	const _STRING pName;
	const _STRING pFileName;
	_BOOL		  bReserved;

} D3DXTextureDescription;

//Resources
static const D3DXTextureDescription d3dxTextures[] =
{
	//Texture
	{L"CD3DXStaticTexture",		TEXTURE_BANANA,			L"Misc\\Texture\\banana.bmp",		_FALSE},
	{L"CD3DXStaticTexture",		TEXTURE_TULIPS,			L"Misc\\Texture\\Tulips.jpg",		_FALSE},
};

//Texture Count
static const int d3dxTextureCount = sizeof(d3dxTextures) / sizeof(D3DXTextureDescription);

///////////////////////////////////////////////////////////////////////////////
//
// CTextureManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CTextureManager::CTextureManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CTextureManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CTextureManager::~CTextureManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateResources
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CTextureManager::createResources(_OBJECT resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Load resources.
	for(_INTEGER i = 0;i < d3dxTextureCount;i ++)
	{
		//Get texture.
		CD3DXTexture* pTexture = (CD3DXTexture *)getResource(d3dxTextures[i].pName);
		//Prevent loading again.
		if(pTexture != _NULL) continue;
		//Get hash code.
		_LONG lClassCode = C4DString::hashCode((_STRING)d3dxTextures[i].pClassName);
		//Check type of resource.
		if(lClassCode == CD3DXStaticTexture::getClassCode())
		{
			//Create texture.
			pTexture = new CD3DXStaticTexture();
#ifdef _DEBUG
			assert(pTexture != _NULL);
#endif
			//Set file name.
			((CD3DXStaticTexture *)pTexture)->setFileName(d3dxTextures[i].pFileName);
		}
		//Set name and add it into list.
		if(pTexture != _NULL)
		{
			//Set name.
			pTexture->setName(d3dxTextures[i].pName);
			//Set reserved.
			pTexture->setReserved(d3dxTextures[i].bReserved);

			//Add texture.
			addResource(pTexture);
		}
	}
	//Return result.
	return S_OK;
}
