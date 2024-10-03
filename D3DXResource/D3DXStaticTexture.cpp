///////////////////////////////////////////////////////////////////////////////
//
// D3DXStaticTexture.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXStaticTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "SDKmisc.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXStaticTexture::base(L"CD3DXStaticTexture",L"CD3DXTexture");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXStaticTexture
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXStaticTexture::CD3DXStaticTexture(void)
{
	//Set default value.
	baseTexture = (LPDIRECT3DTEXTURE9)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXStaticTexture
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXStaticTexture::~CD3DXStaticTexture(void)
{
	//Safe release.
	SAFE_RELEASE(baseTexture);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWidth
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXStaticTexture::getWidth() const
{
	//Surface description.
	D3DSURFACE_DESC desc;
	//Clear description.
	memset(&desc,0,sizeof(desc));
#ifdef _DEBUG
	assert(baseTexture != _NULL);
#endif
	//Get description.
	((LPDIRECT3DTEXTURE9)baseTexture)->GetLevelDesc(0,&desc);
	//Return result.
	return desc.Width;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetHeight
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXStaticTexture::getHeight() const
{
	//Surface description.
	D3DSURFACE_DESC desc;
	//Clear description.
	memset(&desc,0,sizeof(desc));
#ifdef _DEBUG
	assert(baseTexture != _NULL);
#endif
	//Get description.
	((LPDIRECT3DTEXTURE9)baseTexture)->GetLevelDesc(0,&desc);
	//Return result.
	return desc.Height;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFileName
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CD3DXStaticTexture::getFileName() const
{
	//Return result.
	return fileName;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetFileName
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXStaticTexture::setFileName(const CNormalString& fileName)
{
#ifdef _DEBUG
	assert(fileName.length() > 0);
#endif
	//Set file name.
	this->fileName = fileName;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetTexture
//
///////////////////////////////////////////////////////////////////////////////

const LPDIRECT3DTEXTURE9 CD3DXStaticTexture::getTexture() const
{
#ifdef _DEBUG
	assert(baseTexture != _NULL);
#endif
	//Return result.
	return (LPDIRECT3DTEXTURE9)baseTexture;
}

///////////////////////////////////////////////////////////////////////////////
//
// LoadFromFile
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXStaticTexture::loadFromFile(IDirect3DDevice9* pd3dDevice,const CNormalString& fileName)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(baseTexture == NULL);
	assert(pd3dDevice != NULL && fileName.length() > 0);
#endif

	//Image info.
	D3DXIMAGE_INFO imageInfo;
	//Clear image info.
	memset(&imageInfo,0,sizeof(imageInfo));

	//Path.
	WCHAR wszPath[MAX_PATH];
	//Find media file.
	V_RETURN(DXUTFindDXSDKMediaFileCch(wszPath,MAX_PATH,fileName.getCString()));

	//The texture-type must be determined prior to loading it.
	V_RETURN(D3DXGetImageInfoFromFile(wszPath,&imageInfo));
	//Check result.
	if(imageInfo.ResourceType == D3DRTYPE_TEXTURE)
	{
		//Texture.
		LPDIRECT3DTEXTURE9 pTexture = NULL;
		//Create texture from file.
		V_RETURN(D3DXCreateTextureFromFile(pd3dDevice,wszPath,&pTexture));
		//Set pointer.
		baseTexture = pTexture;
	}
	else if(imageInfo.ResourceType == D3DRTYPE_CUBETEXTURE)
	{
		//Texture.
		LPDIRECT3DCUBETEXTURE9 pTexture = NULL;
		//Create texture from file.
		V_RETURN(D3DXCreateCubeTextureFromFile(pd3dDevice,wszPath,&pTexture));
		//Set pointer.
		baseTexture = pTexture;
	}
	else if(imageInfo.ResourceType == D3DRTYPE_VOLUMETEXTURE)
	{
		//Texture.
		LPDIRECT3DVOLUMETEXTURE9 pTexture = NULL;
		//Create texture from file.
		V_RETURN(D3DXCreateVolumeTextureFromFile(pd3dDevice,wszPath,&pTexture));
		//Set pointer.
		baseTexture = pTexture;
	}
	//Return failed.
	else
	{
#ifdef _DEBUG
		::MessageBox(NULL,L"无法识别的资源类型。",L"D3DXStaticTexture.LoadFromFile",MB_OK | MB_ICONERROR);
#endif
		//Return failed.
		return E_FAIL;
	}
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXStaticTexture::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Safe release.
		SAFE_RELEASE(baseTexture);
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Load from file.
		V_RETURN(loadFromFile(d3dxEvent.d3dxCreateDevice9.pd3dDevice,fileName.getCString()));
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
