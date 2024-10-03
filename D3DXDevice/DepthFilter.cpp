///////////////////////////////////////////////////////////////////////////////
//
// DepthFilter.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "DepthFilter.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "cv.h"
#include "highgui.h"

#include "KinectDevice.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

const _INTEGER CDepthFilter::rawMode						= 0;
const _INTEGER CDepthFilter::grayColorMode					= 1;
const _INTEGER CDepthFilter::mixedColorMode					= 2;
const _INTEGER CDepthFilter::adjustColorMode				= 3;

//Set base of object.
const C4DBase CDepthFilter::base(L"CDepthFilter",L"CImageFilter");

///////////////////////////////////////////////////////////////////////////////
//
// CDepthFilter
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CDepthFilter::CDepthFilter(void)
{
	//Set default value.
	mode = mixedColorMode;
}

///////////////////////////////////////////////////////////////////////////////
//
// CDepthFilter
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CDepthFilter::~CDepthFilter(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// GetMode
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CDepthFilter::getMode() const
{
	//Return result.
	return mode;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetMode
//
///////////////////////////////////////////////////////////////////////////////

void CDepthFilter::setMode(_INTEGER mode)
{
	//Set mode.
	this->mode = mode;
}

///////////////////////////////////////////////////////////////////////////////
//
// DoCopy
//
///////////////////////////////////////////////////////////////////////////////

void CDepthFilter::doCopy(_INTEGER mode)
{
	//Get device.
	CD3DXDevice* device = getDevice();
#ifdef _DEBUG
	assert(device != _NULL);
#endif
	//Get depth buffer.
	_SHORT* depthBuffer = (_SHORT *)_NULL;
	//Check instance.
	if(IS_KINECTDEVICE_BASE(device))
	{
		//Get depth buffer.
		depthBuffer = ((CKinectDevice *)device)->getDepthBuffer();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

#ifdef _DEBUG
	assert(depthBuffer != _NULL);
#endif
	//Get image object.
	_OBJECT imageObject = getImageObject();
#ifdef _DEBUG
	assert(imageObject != _NULL);
#endif
	//Get image buffer.
	_INTEGER* imageBuffer = (_INTEGER *)((IplImage *)imageObject)->imageData;
#ifdef _DEBUG
	assert(imageBuffer != _NULL);
#endif
	//Check result.
	if(mode == rawMode)
	{
		//Copy raw mode.
		copyRawDepth(getWidth(),getHeight(),imageBuffer,depthBuffer);
	}
	else if(mode == grayColorMode)
	{
		//Copy gray mode.
		copyGrayDepth(getWidth(),getHeight(),imageBuffer,depthBuffer);
	}
	else if(mode == mixedColorMode)
	{
		//Copy mixed mode.
		copyMixedDepth(getWidth(),getHeight(),imageBuffer,depthBuffer);
	}
	else if(mode == adjustColorMode)
	{
		//Copy adjust mode.
		copyAdjustDepth(getWidth(),getHeight(),imageBuffer,depthBuffer);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyRawDepth
//
///////////////////////////////////////////////////////////////////////////////

void CDepthFilter::copyRawDepth(_INTEGER width,_INTEGER height,_INTEGER* imageBuffer,_SHORT* depthBuffer)
{
#ifdef _DEBUG
	assert(width > 0 && height > 0);
	assert(imageBuffer != _NULL && depthBuffer != _NULL);
#endif
	//Do while.
	for(_INTEGER i = 0;i < width * height;i ++)
	{
		//Set color buffer.
		imageBuffer[i] = depthBuffer[i] & 0xFFFF;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyGrayDepth
//
///////////////////////////////////////////////////////////////////////////////

void CDepthFilter::copyGrayDepth(_INTEGER width,_INTEGER height,_INTEGER* imageBuffer,_SHORT* depthBuffer)
{
#ifdef _DEBUG
	assert(width > 0 && height > 0);
	assert(imageBuffer != _NULL && depthBuffer != _NULL);
#endif
	//Max depth.
	_INTEGER maxDepth = -1;
	//Do while.
	for(_INTEGER i = 0;i < width * height;i ++)
	{
		//Get depth value.
		_INTEGER depthValue = depthBuffer[i] & 0xFFFF;
		//Set depth buffer.
		if(depthValue > maxDepth) maxDepth = depthValue;
	}
	//Do while.
	for(_INTEGER i = 0;i < width * height;i ++)
	{
		//Get color value.
		_INTEGER colorValue = (_INTEGER)((depthBuffer[i] & 0xFFFF) * 255.0 / maxDepth);
		//Set color buffer.
		imageBuffer[i] = (colorValue << 16) | (colorValue << 8) | colorValue;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyMixedDepth
//
///////////////////////////////////////////////////////////////////////////////

void CDepthFilter::copyMixedDepth(_INTEGER width,_INTEGER height,_INTEGER* imageBuffer,_SHORT* depthBuffer)
{
#ifdef _DEBUG
	assert(width > 0 && height > 0);
	assert(imageBuffer != _NULL && depthBuffer != _NULL);
#endif
	//Max depth.
	_INTEGER maxDepth = -1;
	//Do while.
	for(_INTEGER i = 0;i < width * height;i ++)
	{
		//Get depth value.
		_INTEGER depthValue = depthBuffer[i] & 0xFFFF;
		//Set depth buffer.
		if(depthValue > maxDepth) maxDepth = depthValue;
	}
	//Do while.
	for(_INTEGER i = 0;i < width * height;i ++)
	{
		//Get color value.
		_INTEGER colorValue = (_INTEGER)((depthBuffer[i] & 0xFFFF) * 255.0 / maxDepth);
		//Check result.
		if(depthBuffer[i] == 0)
		{
			//Set color value.
			imageBuffer[i] = 0xFFFFFFFF;
		}
		else if(depthBuffer[i] <= 850)
		{
			//Set color value.
			imageBuffer[i] = colorValue;//Blue
		}
		else if(depthBuffer[i] <= 1200)
		{
			//Set color value.
			imageBuffer[i] = colorValue << 8;//Green	
		}
		else
		{
			//Set color value.
			imageBuffer[i] = colorValue << 16;//Red	
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyAdjustDepth
//
///////////////////////////////////////////////////////////////////////////////

void CDepthFilter::copyAdjustDepth(_INTEGER width,_INTEGER height,_INTEGER* imageBuffer,_SHORT* depthBuffer)
{
#ifdef _DEBUG
	assert(width > 0 && height > 0);
	assert(imageBuffer != _NULL && depthBuffer != _NULL);
#endif
	//Max depth.
	_INTEGER maxDepth = -1;
	//Do while.
	for(_INTEGER i = 0;i < width * height;i ++)
	{
		//Get depth value.
		_INTEGER depthValue = depthBuffer[i] & 0xFFFF;
		//Set depth buffer.
		if(depthValue > maxDepth) maxDepth = depthValue;
	}
	//Min value.
	_INTEGER minValue = 850;
	//Max value.
	_INTEGER maxValue = 1200;
	//Do while.
	for(_INTEGER i = 0;i < height;i ++)
	{
		//Calculate offset.
		_INTEGER offset = i * width;
		//Calculate value.
		_INTEGER minV = (_INTEGER)((_FLOAT)(height - i) / height * 100.0f + 700.0f);
		_INTEGER maxV = (_INTEGER)((_FLOAT)(height - i) / height * 100.0f + 1100.0f);
		//Do while.
		for(_INTEGER j = 0;j < width;j ++, offset ++)
		{
			//Get color value.
			_INTEGER colorValue = (_INTEGER)((depthBuffer[offset] & 0xFFFF) * 255.0 / maxDepth);
			//Check result.
			if(depthBuffer[offset] == 0)
			{
				//Set color value.
				imageBuffer[offset] = 0xFFFFFFFF;
			}
			else if(depthBuffer[offset] <= minV)
			{
				//Set color value.
				imageBuffer[offset] = colorValue;//Blue
			}
			else if(depthBuffer[offset] <= maxV)
			{
				//Set color value.
				imageBuffer[offset] = colorValue << 8;//Green	
			}
			else
			{
				//Set color value.
				imageBuffer[offset] = colorValue << 16;//Red	
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CDepthFilter::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//On frame move.
	case d3dxOnFrameMove:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Check mode.
		doCopy(mode);
		break;
	}
	//Return result.
	return CImageFilter::handleMessage(d3dxEvent);
}
