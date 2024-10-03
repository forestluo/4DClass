///////////////////////////////////////////////////////////////////////////////
//
// D3DXInputTexture.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXInputTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ImageDevice.h"
#include "ImageFilter.h"
#include "KinectDevice.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXInputTexture::base(L"CD3DXInputTexture",L"CD3DXDynamicTexture");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXInputTexture
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXInputTexture::CD3DXInputTexture()
{
	//Set default value.
	source = (CD3DXResource *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXInputTexture
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXInputTexture::~CD3DXInputTexture(void)
{
	//Check source.
	if(source != _NULL)
	{
		//Release.
		source->releaseReference();
		//Clear source.
		source = (CD3DXResource *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSource
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResource* CD3DXInputTexture::getSource() const
{
	//Return result.
	return source;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSourceName
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CD3DXInputTexture::getSourceName() const
{
	//Return result.
	return sourceName;
}

///////////////////////////////////////////////////////////////////////////////
//
// SelectSource
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXInputTexture::selectSource(CResourceManager* resourceManager,const CNormalString& name)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL && name.length() > 0);
#endif
	//Check source.
	if(source != _NULL)
	{
		//Release source.
		source->releaseReference();
		//Clear source.
		source = (CD3DXResource *)_NULL;
	}
	//Get resource.
	CD3DXResource* resource = resourceManager->getResource(name);
#ifdef _DEBUG
	assert(resource != _NULL);
#endif
	//Get width and height.
	_INTEGER width = 0, height = 0;
	//Check result.
	if(IS_IMAGEDEVICE_BASE(resource))
	{
		//Get width.
		width = ((CImageDevice *)resource)->getWidth();
		//Get height.
		height = ((CImageDevice *)resource)->getHeight();
	}
	else if(IS_IMAGEFILTER_BASE(resource))
	{
		//Get width.
		width = ((CImageFilter *)resource)->getWidth();
		//Get height.
		height = ((CImageFilter *)resource)->getHeight();
	}
	else if(IS_KINECTDEVICE_BASE(resource))
	{
		//Get width.
		width = ((CKinectDevice *)resource)->getWidth();
		//Get height.
		height = ((CKinectDevice *)resource)->getHeight();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Add reference.
	resource->addReference();

	//Set name.
	sourceName = name;
	//Set source.
	source = (CD3DXDevice *)resource;
	//Create texture.
	return CD3DXDynamicTexture::createTexture(resourceManager->getDevice(),width,height);
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXInputTexture::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Check source.
		if(source != _NULL)
		{
			//Release source.
			source->releaseReference();
			//Clear source.
			source = (CD3DXResource *)_NULL;
		}
		break;
	//On frame move.
	case d3dxOnFrameMove:
		//Check source.
		if(source != _NULL)
		{
			//Get image buffer.
			_BYTE* imageBuffer = (_BYTE *)_NULL;
			//Check instance.
			if(IS_IMAGEDEVICE_BASE(source))
			{
				//Get image buffer.
				imageBuffer = ((CImageDevice *)source)->getImageBuffer();
			}
			else if(IS_IMAGEFILTER_BASE(source))
			{
				//Get image buffer.
				imageBuffer = ((CImageFilter *)source)->getImageBuffer();
			}
			else if(IS_KINECTDEVICE_BASE(source))
			{
				//Get image buffer.
				imageBuffer = ((CKinectDevice *)source)->getImageBuffer();
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
#ifdef _DEBUG
			assert(imageBuffer != _NULL);
#endif
			//Get dynamic texture.
			LPDIRECT3DTEXTURE9 texture = CD3DXDynamicTexture::getTexture();
#ifdef _DEBUG
			assert(texture != _NULL);
#endif
			//Locked rect.
			D3DLOCKED_RECT d3dxLockedRect;
			//Lock texture.
			if(SUCCEEDED(texture->LockRect(0,&d3dxLockedRect,0,0)))
			{
				//Copy memory.
				memcpy(static_cast<byte *>(d3dxLockedRect.pBits),
					imageBuffer,getHeight() * d3dxLockedRect.Pitch * sizeof(_BYTE));
				//Unlock rect.
				texture->UnlockRect(0);
			}
		}
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Check source name.
		if(sourceName.length() > 0)
		{
			//Select source.
			if(!selectSource(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager(),sourceName)) return E_FAIL;
		}
		break;
	}
	//Return result.
	return CD3DXDynamicTexture::handleMessage(d3dxEvent);
}
