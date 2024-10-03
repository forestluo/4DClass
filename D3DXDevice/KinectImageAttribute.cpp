///////////////////////////////////////////////////////////////////////////////
//
// KinectImageAttribute.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectImageAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "cv.h"
#include "MSR_NuiApi.h"

///////////////////////////////////////////////////////////////////////////////
//
// CKinectImageAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectImageAttribute::CKinectImageAttribute(void)
{
	//Set default value.
	frameEvent = _NULL;
	streamHandle = _NULL;
	imageBuffer = (IplImage *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CKinectImageAttribute
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectImageAttribute::~CKinectImageAttribute(void)
{
	//Destroy image.
	destroyImage();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEvent
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CKinectImageAttribute::getEvent() const
{
	//Return value.
	return frameEvent;
}

///////////////////////////////////////////////////////////////////////////////
//
// DestroyImage
//
///////////////////////////////////////////////////////////////////////////////

void CKinectImageAttribute::destroyImage()
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
	//Check image buffer.
	if(imageBuffer != _NULL)
	{
		//Release image buffer.
		cvReleaseImage((IplImage **)&imageBuffer);
		//Clear image buffer.
		imageBuffer = (IplImage *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateImage
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CKinectImageAttribute::createImage()
{
	//Get instance.
	INuiInstance* nuiInstance =	(INuiInstance *)getDevice();
#ifdef _DEBUG
	assert(nuiInstance != _NULL);
#endif

#ifdef _DEBUG
	assert(frameEvent == _NULL);
#endif
	//Create event.
	frameEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
#ifdef _DEBUG
	assert(frameEvent != _NULL && frameEvent != INVALID_HANDLE_VALUE);
#endif

	//Open image stream.
	if(FAILED(nuiInstance->NuiImageStreamOpen(
								NUI_IMAGE_TYPE_COLOR,
								(NUI_IMAGE_RESOLUTION)getResolution(),
								0,
								2,
								frameEvent,
								&streamHandle))) return _FALSE;
#ifdef _DEBUG
	assert(streamHandle != _NULL && streamHandle != INVALID_HANDLE_VALUE);
#endif
	//Create image buffer (X8R8G8B8).
	imageBuffer = cvCreateImage(cvSize(getResolutionWidth(),getResolutionHeight()),IPL_DEPTH_8U,4);
	//Return true.
	return imageBuffer != _NULL ? _TRUE : _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetReceivedImageObject
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CKinectImageAttribute::getReceivedImageObject() const
{
	//Return value.
	return (IplImage *)imageBuffer;
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyImageBuffer
//
///////////////////////////////////////////////////////////////////////////////

void CKinectImageAttribute::copyImageBuffer()
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
	assert(imageBuffer != _NULL);
#endif
	//Lock rect.
	NUI_LOCKED_RECT lockedRect;
	//Get frame texture.
	INuiFrameTexture* frameTexture = imageFrame->pFrameTexture;
#ifdef _DEBUG
	assert(frameTexture != _NULL);
#endif
	//Lock rect.
	frameTexture->LockRect(0,&lockedRect,NULL,0);
	//Check result.
#ifdef _DEBUG
	assert(lockedRect.Pitch > 0);
#endif
	//Copy bytes.
	memcpy(((IplImage *)imageBuffer)->imageData,(BYTE *)lockedRect.pBits,
		getResolutionWidth() * getResolutionHeight() * (4 * sizeof(BYTE)));
	//Unlock rect.
	frameTexture->UnlockRect(0);
	//Release frame.
	nuiInstance->NuiImageStreamReleaseFrame(streamHandle,imageFrame);
}
