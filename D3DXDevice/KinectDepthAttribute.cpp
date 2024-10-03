///////////////////////////////////////////////////////////////////////////////
//
// KinectDepthAttribute.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectDepthAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "MSR_NuiApi.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define NUI_INSTANCE(p)										((INuiInstance *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CKinectDepthAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectDepthAttribute::CKinectDepthAttribute(void)
{
	//Set default value.
	frameEvent = _NULL;
	streamHandle = _NULL;
	depthBuffer = (_SHORT *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CKinectDepthAttribute
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectDepthAttribute::~CKinectDepthAttribute(void)
{
	//Destroy depth.
	destroyDepth();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEvent
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CKinectDepthAttribute::getEvent() const
{
	//Return value.
	return frameEvent;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetReceivedDepthBuffer
//
///////////////////////////////////////////////////////////////////////////////

_SHORT* CKinectDepthAttribute::getReceivedDepthBuffer() const
{
	//Return value.
	return depthBuffer;
}

///////////////////////////////////////////////////////////////////////////////
//
// DestroyDepth
//
///////////////////////////////////////////////////////////////////////////////

void CKinectDepthAttribute::destroyDepth()
{
	//Check handle.
	if(frameEvent &&
		frameEvent != INVALID_HANDLE_VALUE)
	{
		//Close handle.
		CloseHandle(frameEvent);
		//Clear handle.
		frameEvent = _NULL;
	}
	//Check depth buffer.
	if(depthBuffer != _NULL)
	{
		//Delete depth buffer.
		delete (_SHORT *)depthBuffer;
		//Clear depth buffer.
		depthBuffer = (_SHORT *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateDepth
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CKinectDepthAttribute::createDepth()
{
	//Get instance.
	INuiInstance* nuiInstance = (INuiInstance *)getDevice();
#ifdef _DEBUG
	assert(nuiInstance != _NULL);
#endif
	//Create event.
	frameEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
#ifdef _DEBUG
	assert(frameEvent != _NULL && frameEvent != INVALID_HANDLE_VALUE);
#endif
	//Open depth stream.
	if(FAILED(NUI_INSTANCE(nuiInstance)->NuiImageStreamOpen(
												NUI_IMAGE_TYPE_DEPTH,
												(NUI_IMAGE_RESOLUTION)getResolution(),
												0,
												2,
												frameEvent,
												&streamHandle))) return _FALSE;
#ifdef _DEBUG
	assert(streamHandle != _NULL && streamHandle != INVALID_HANDLE_VALUE);
#endif
	//Create depth buffer.
	depthBuffer = new _SHORT[getResolutionWidth() * getResolutionHeight()];
#ifdef _DEBUG
	assert(depthBuffer != _NULL);
#endif
	//Clear depth buffer.
	memset(depthBuffer,0,getResolutionWidth() * getResolutionHeight() * sizeof(_SHORT));
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyDepthBuffer
//
///////////////////////////////////////////////////////////////////////////////

void CKinectDepthAttribute::copyDepthBuffer()
{
	//Image frame.
	const NUI_IMAGE_FRAME* imageFrame = NULL;
#ifdef _DEBUG
	assert(streamHandle != _NULL);
#endif
	//Get instance.
	INuiInstance* nuiInstance =	(INuiInstance *)getDevice();
#ifdef _DEBUG
	assert(nuiInstance != _NULL);
#endif
	//Get next frame.
	if(FAILED(nuiInstance->NuiImageStreamGetNextFrame(streamHandle,0,&imageFrame))) return;
#ifdef _DEBUG
	assert(depthBuffer != _NULL);
#endif
	//Lock rect.
	NUI_LOCKED_RECT lockedRect;
	//Get frame texture.
	INuiFrameTexture* frameTexture = imageFrame->pFrameTexture;
#ifdef _DEBUG
	assert(frameTexture != _NULL);
#endif
	//Get width.
	_INTEGER width = getResolutionWidth();
	//Get height.
	_INTEGER height = getResolutionHeight();
	//Lock rect.
	frameTexture->LockRect(0,&lockedRect,NULL,0);
	//Check result.
#ifdef _DEBUG
	assert(lockedRect.Pitch > 0);
#endif
	//Copy bytes.
	memcpy(depthBuffer,(BYTE *)lockedRect.pBits,
		width * height * (sizeof(_SHORT)));
	//Unlock rect.
	frameTexture->UnlockRect(0);
	//Release frame.
	nuiInstance->NuiImageStreamReleaseFrame(streamHandle,imageFrame);

	//Swap value.
	for(_INTEGER i = 0;i < height;i ++)
	{
		for(_INTEGER j = 0;j < width / 2;j ++)
		{
			//Get value.
			_SHORT value = depthBuffer[i * width + j];
			//Swap value.
			depthBuffer[i * width + j] = depthBuffer[i * width + (width - j - 1)];
			//Set value.
			depthBuffer[i * width + (width - j - 1)] = value;
		}
	}
}
