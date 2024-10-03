///////////////////////////////////////////////////////////////////////////////
//
// KinectDevice.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectDevice.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "cv.h"
#include "highgui.h"

#include "MSR_NuiApi.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define NUI_INSTANCE(p)										((INuiInstance *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CKinectDevice::base(L"CKinectDevice",L"CD3DXDevice");

///////////////////////////////////////////////////////////////////////////////
//
// CKinectDevice
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectDevice::CKinectDevice(void)
{
	//Depth buffer.
	depthBuffer = (_SHORT *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CKinectDevice
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectDevice::~CKinectDevice(void)
{
	//Close device.
	closeDevice();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetKinectCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectDevice::getKinectCount()
{
	//Count.
	_INTEGER count = 0;
	//Get device count.
	MSR_NUIGetDeviceCount(&count);
	//Return result.
	return count;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetReceivedDepthBuffer
//
///////////////////////////////////////////////////////////////////////////////

_SHORT* CKinectDevice::getDepthBuffer() const
{
	//Return value.
	return depthBuffer;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWidth
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectDevice::getWidth() const
{
	//Return result.
	return CKinectInstanceAttribute::getResolutionWidth();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetHeight
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectDevice::getHeight() const
{
	//Return result.
	return CKinectInstanceAttribute::getResolutionHeight();
}

///////////////////////////////////////////////////////////////////////////////
//
// NuiProcessThread
//
///////////////////////////////////////////////////////////////////////////////

DWORD WINAPI CKinectDevice::nuiProcessThread()
{
	//Events.
	HANDLE events[3];
	// Configure events to be listened on
	events[0]= CKinectProcessAttribute::getEvent();
	events[1]= CKinectImageAttribute::getEvent();
	events[2]= CKinectDepthAttribute::getEvent();

#pragma warning(push)
	//Conditional expression is constant
#pragma warning(disable: 4127)
	//Main thread loop.
	while(_TRUE)
	{
		//Wait for an event to be signaled.
		DWORD index = WaitForMultipleObjects(sizeof(events)/sizeof(events[0]),events,FALSE,100);
		//If the stop event, stop looping and exit.
		if(index == 0) break;
		//Perform FPS processing.
		frameBegin(index);
		//Process signal events.
		switch(index)
		{
		case 1:
			//Open lock.
			openLock();
			{
				//Copy image buffer.
				CKinectImageAttribute::copyImageBuffer();
			}
			//Close lock.
			closeLock();
			break;
		case 2:
			//Open lock.
			openLock();
			{
				//Copy depth buffer.
				CKinectDepthAttribute::copyDepthBuffer();
			}
			//Close lock.
			closeLock();
			//Increase total.
			increaseTotal(index);
			break;
		case 3:
			//Nui_GotSkeletonAlert();
			break;
		}
	}
#pragma warning(pop)
	//Return result.
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// CloseDevice
//
///////////////////////////////////////////////////////////////////////////////

void CKinectDevice::closeDevice()
{
	//Destroy process.
	CKinectProcessAttribute::destroyProcess();
	//Destroy depth.
	CKinectDepthAttribute::destroyDepth();
	//Destroy buffer.
	CKinectImageAttribute::destroyImage();
	//Destroy instance.
	CKinectInstanceAttribute::destroyInstance();

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
// OpenDevice
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CKinectDevice::openDevice(_INTEGER index,_INTEGER mode)
{
#ifdef _DEBUG
	assert(index >= 0);
#endif
	//Try to create instance.
	if(CKinectInstanceAttribute::createInstance(index,mode))
	{
		//Width.
		_INTEGER width = CKinectInstanceAttribute::getResolutionWidth();
		//Height.
		_INTEGER height = CKinectInstanceAttribute::getResolutionHeight();
#ifdef _DEBUG
		assert(width > 0 && height > 0);
#endif
		//Try to create image.
		if(COpenCVImageAttribute::createImage(width,height))
		{
			//Try to create image.
			if(CKinectImageAttribute::createImage())
			{
				//Try to create depth.
				if(CKinectDepthAttribute::createDepth())
				{
					//Create depth buffer.
					depthBuffer = new _SHORT[getResolutionWidth() * getResolutionHeight()];
#ifdef _DEBUG
					assert(depthBuffer != _NULL);
#endif
					//Clear buffer.
					memset(depthBuffer,0,getResolutionWidth() * getResolutionHeight() * sizeof(_SHORT));

					//Try to create process.
					if(CKinectProcessAttribute::createProcess())
					{
						//Return true.
						return _TRUE;
					}
					//Destroy depth.
					CKinectDepthAttribute::destroyDepth();
				}
				//Destroy image.
				CKinectImageAttribute::destroyImage();
			}
			//Destroy image.
			COpenCVImageAttribute::destroyImage();
		}
		//Destroy instance.
		CKinectInstanceAttribute::destroyInstance();
	}
	//Return false.
	return _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CKinectDevice::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Close device.
		closeDevice();
		break;
	//On frame move.
	case d3dxOnFrameMove:
		//Copy object from original to current.
		//Open lock.
		openLock();
		{
			//Get image.
			_OBJECT imageObject = COpenCVImageAttribute::getImageObject();
#ifdef _DEBUG
			assert(imageObject != _NULL);
#endif
			//Get image object.
			_OBJECT receivedImage = CKinectImageAttribute::getReceivedImageObject();
#ifdef _DEBUG
			assert(receivedImage != _NULL);
#endif
			//Copy image.
			cvCopyImage((IplImage *)receivedImage,(IplImage *)imageObject);

			//Copy depth buffer.
#ifdef _DEBUG
			assert(depthBuffer != _NULL);
#endif
			//Get buffer.
			_SHORT* receivedBuffer = CKinectDepthAttribute::getReceivedDepthBuffer();
#ifdef _DEBUG
			assert(receivedBuffer != _NULL);
#endif
			//Copy buffer.
			memcpy(depthBuffer,receivedBuffer,getResolutionWidth() * getResolutionHeight() * sizeof(_SHORT));
		}
		//Close lock.
		closeLock();
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != _NULL);
#endif
		//Try to open device.
		if(!openDevice(getIndex(),getResolution())) return E_FAIL;
		break;
	}
	//Return result.
	return CD3DXDevice::handleMessage(d3dxEvent);
}
