///////////////////////////////////////////////////////////////////////////////
//
// D3DXDynamicTexture.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXDynamicTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define DEFAULT_FORMAT										D3DFMT_A8R8G8B8

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXDynamicTexture::base(L"CD3DXDynamicTexture",L"CD3DXTexture");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXDynamicTexture
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXDynamicTexture::CD3DXDynamicTexture(void)
{
	//Set default value.
	width = 0;
	height = 0;
	widthRatio = 1.0f;
	heightRatio = 1.0f;
	dynamicTexture = (LPDIRECT3DTEXTURE9)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXDynamicTexture
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXDynamicTexture::~CD3DXDynamicTexture(void)
{
	//Safe release.
	SAFE_RELEASE(dynamicTexture);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWidth
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXDynamicTexture::getWidth() const
{
	//Return result.
	return width;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetHeight
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXDynamicTexture::getHeight() const
{
	//Return result.
	return height;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetTexture
//
///////////////////////////////////////////////////////////////////////////////

const LPDIRECT3DTEXTURE9 CD3DXDynamicTexture::getTexture() const
{
	//Return result.
	return (LPDIRECT3DTEXTURE9)dynamicTexture;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateTexture
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXDynamicTexture::createTexture(IDirect3DDevice9* d3dxDevice,_INTEGER width,_INTEGER height)
{
	//Result.
	HRESULT hr;
	//Surface description.
	D3DSURFACE_DESC ddsd;

#ifdef _DEBUG
	assert(d3dxDevice != _NULL);
#endif
	//Release previous texture.
	if(dynamicTexture != _NULL) SAFE_RELEASE(dynamicTexture);
	//Create texture.
	V_RETURN(d3dxDevice->CreateTexture(width,height,1,0,DEFAULT_FORMAT,D3DPOOL_MANAGED,&dynamicTexture,NULL));
#ifdef _DEBUG
	assert(dynamicTexture != _NULL);
#endif
	//Get level description.
	V_RETURN(dynamicTexture->GetLevelDesc(0,&ddsd));
	//Check result.
	if(ddsd.Format != DEFAULT_FORMAT) {SAFE_RELEASE(dynamicTexture); return _TRUE;}
	//Set width.
	this->width = ddsd.Width;
	this->height = ddsd.Height;
	this->widthRatio = (_FLOAT)width  / (_FLOAT)ddsd.Width;
	this->heightRatio = (_FLOAT)height / (_FLOAT)ddsd.Height;
	//Return result.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyMediaSample
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXDynamicTexture::copyMediaSample(IMediaSample *mediaSample,_INTEGER samplePitch)
{
	//Result.
	HRESULT hr;
	//Pitch of texture.
	_INTEGER texturePitch;
	//Locked rect.
	D3DLOCKED_RECT d3dxLockedRect;
	//Sample buffer.
	BYTE* sampleBuffer = (BYTE *)_NULL;
	//Texture buffer.
	BYTE* textureBuffer = (BYTE *)_NULL;

#ifdef _DEBUG
	assert(mediaSample != _NULL);
#endif
	//Get the video bitmap buffer.
	hr = mediaSample->GetPointer(&sampleBuffer);
	//Check result.
	if(SUCCEEDED(hr))
	{
#ifdef _DEBUG
		assert(dynamicTexture != _NULL);
#endif
		//Lock texture.
		hr = dynamicTexture->LockRect(0,&d3dxLockedRect,0,0);
		//Check result.
		if(SUCCEEDED(hr))
		{
			//Set texture pitch.
			texturePitch = d3dxLockedRect.Pitch;
			//Get the texture buffer & pitch/
			textureBuffer = static_cast<byte *>(d3dxLockedRect.pBits);
			//Copy all pixels.
			for(_INTEGER row = 0;row < this->height;row ++) 
			{
				//Set head of sample head.
				BYTE* sampleBufferHead = sampleBuffer;
				//Set head of texture head.
				BYTE* textureBufferHead = textureBuffer;
				//Copy each column.
				for(_INTEGER column = 0;column < this->width;column ++) 
				{
					//Copy pixel.
					textureBuffer[0] = sampleBuffer[0];
					textureBuffer[1] = sampleBuffer[1];
					textureBuffer[2] = sampleBuffer[2];
					textureBuffer[3] = 0xFF;//(BYTE)(0xFF * y / (m_lVidHeight-1));
					//Add sample buffer.
					sampleBuffer  += 3;
					//Add texture buffer.
					textureBuffer += 4;
				}
				//Set next row.
				sampleBuffer  = sampleBufferHead + samplePitch;
				//Set next row.
				textureBuffer = textureBufferHead + texturePitch;
			}
		}
		//Unlock rect.
		dynamicTexture->UnlockRect(0);
	}
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// CopySurface
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXDynamicTexture::copySurface(IDirect3DSurface9 *sourceSurface,_INTEGER width,_INTEGER height)
{
	//Result.
	HRESULT hr;
	//Destination surface.
	IDirect3DSurface9* destinationSurface;

#ifdef _DEBUG
	assert(sourceSurface != _NULL);
	assert(dynamicTexture != _NULL);
#endif

	//Source rect.
	RECT sourceRect;
	//Set left and top.
	sourceRect.left = sourceRect.top = 0;
	//Set right.
	sourceRect.right = width;
	//Set bottom.
	sourceRect.bottom = height;

	//Destination rect.
	RECT destinationRect;
	//Set left and top.
	destinationRect.left = destinationRect.top = 0;
	//Set right.
	destinationRect.right = this->width;
	//Set bottom.
	destinationRect.bottom = this->height;

	//Get surface level.
	hr = dynamicTexture->GetSurfaceLevel(0,&destinationSurface);
	//Get surface level.
	if(SUCCEEDED(hr))
	{
#ifdef _DEBUG
		assert(destinationSurface != _NULL);
#endif
		//Get result.
		hr = D3DXLoadSurfaceFromSurface(destinationSurface,NULL,&destinationRect,
										sourceSurface,NULL,&sourceRect,D3DX_DEFAULT,0xFF000000);
		//Safe release.
		SAFE_RELEASE(destinationSurface);
	}
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXDynamicTexture::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Safe release.
		SAFE_RELEASE(dynamicTexture);
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
