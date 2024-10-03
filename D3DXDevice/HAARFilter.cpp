///////////////////////////////////////////////////////////////////////////////
//
// HAARFilter.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "HAARFilter.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "cv.h"
#include "highgui.h"

#include "ImageDevice.h"
#include "KinectDevice.h"

#include "ViewPort.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CHAARFilter::base(L"CHAARFilter",L"CImageFilter");

///////////////////////////////////////////////////////////////////////////////
//
// CHAARFilter
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CHAARFilter::CHAARFilter(void)
{
	//Set default value.
	faceTracking = _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// CHAARFilter
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CHAARFilter::~CHAARFilter(void)
{
	//Disable detection.
	disableDetection();
}

///////////////////////////////////////////////////////////////////////////////
//
// EnableDetection
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CHAARFilter::enableDetection()
{
	//Return result.
	return CHAARAttribute::enableDetection(getWidth(),getHeight());
}

///////////////////////////////////////////////////////////////////////////////
//
// IsFaceTracking
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CHAARFilter::isFaceTracking() const
{
	//Return result.
	return faceTracking;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetFaceTracking
//
///////////////////////////////////////////////////////////////////////////////

void CHAARFilter::setFaceTracking(_BOOL faceTracking)
{
	//Set value.
	this->faceTracking = faceTracking;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CHAARFilter::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Disable detection.
		disableDetection();
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != _NULL);
#endif
		//Check detection require.
		if(isDetecting() && !enableDetection()) return E_FAIL;
		break;
	//On frame move.
	case d3dxOnFrameMove:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Copy image from source device.
		{
			//Get device.
			CD3DXDevice* device = getDevice();
#ifdef _DEBUG
			assert(device != _NULL);
#endif
			//Get input image.
			_OBJECT deviceImage = _NULL;
			//Check instance.
			if(IS_IMAGEDEVICE_BASE(device))
			{
				//Get image object.
				deviceImage = ((CImageDevice *)device)->getImageObject();
			}
			else if(IS_KINECTDEVICE_BASE(device))
			{
				//Get image object.
				deviceImage = ((CKinectDevice *)device)->getImageObject();
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
#ifdef _DEBUG
			assert(deviceImage != _NULL);
#endif
			//Get receive image.
			_OBJECT filterImage = getImageObject();
#ifdef _DEBUG
			assert(filterImage != _NULL);
#endif
			//Copy image.
			cvCopyImage((IplImage *)deviceImage,(IplImage *)filterImage);
		}
		//Check detecting.
		if(isDetecting())
		{
			//Check detection result.
			if(doDetection(getImageObject()))
			{
				//Get view port.
				CViewPort* viewPort = ((CD3DXApplication *)d3dxEvent.pUserContext)->getViewPort();
#ifdef _DEBUG
				assert(viewPort != _NULL);
#endif
				//Rotate view port.
				if(faceTracking) rotateViewPort(viewPort);
			}
		}
		break;
	}
	//Return result.
	return CImageFilter::handleMessage(d3dxEvent);
}
