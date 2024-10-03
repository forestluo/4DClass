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

#include "MSR_NuiApi.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define NUI_INSTANCE(p)										((INuiInstance *)(p))
#define DEFAULT_IMAGE_WIDTH                                 640
#define DEFAULT_IMAGE_HEIGHT                                480
#define DEFAULT_DEPTH_WIDTH									320
#define DEFAULT_DEPTH_HEIGHT								240

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CKinectDevice::base(L"CKinectDevice",L"CD3DXDevice");
//Resolution mode.
const _INTEGER CKinectDevice::vgaMode						= NUI_IMAGE_RESOLUTION_320x240;
const _INTEGER CKinectDevice::qvgaMode						= NUI_IMAGE_RESOLUTION_640x480;

///////////////////////////////////////////////////////////////////////////////
//
// CKinectDevice
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectDevice::CKinectDevice(_INTEGER index)
{
#ifdef _DEBUG
	assert(index >= 0);
#endif
	//Set index.
	this->index = index;
	//Set default value.
	mode = 0;
	totalFrames = 0;
	lastFPStime = -1;
	lastTotalFrames = 0;
	//Set default value.
	imageBuffer = (_BYTE *)_NULL;
	depthBuffer = (_SHORT *)_NULL;

	//Set default value.
	nuiProcess = _NULL;
	nuiProcessEvent = _NULL;
	//Set default value.
	videoStreamHandle = _NULL;
	depthStreamHandle = _NULL;
	//Set default value.
	nextVideoFrameEvent = _NULL;
	nextDepthFrameEvent = _NULL;
	//Set default value.
	instanceID = (BSTR)_NULL;
	nuiInstance = (INuiInstance *)_NULL;
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
// NuiProcessThread
//
///////////////////////////////////////////////////////////////////////////////

DWORD WINAPI CKinectDevice::nuiProcessThread()
{
	//Events.
	HANDLE events[3];
	// Configure events to be listened on
	events[0]= nuiProcessEvent;
	events[1]= nextDepthFrameEvent;
	events[2]= nextVideoFrameEvent;

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
		int t = timeGetTime( );
		if(lastFPStime == -1)
		{
			//Set last fps time.
			lastFPStime = t;
			//Set total frames.
			lastTotalFrames = totalFrames;
		}
		//Calculate time.
		int dt = t - lastFPStime;
		//Check result.
		if(dt > 1000)
		{
			//Set last fps time.
			lastFPStime = t;
			//Calculate delta.
			int frameDelta = totalFrames - lastTotalFrames;
			//Set last total frames.
			lastTotalFrames = totalFrames;
		}

		//Process signal events.
		switch(index)
		{
		case 1:
			//Nui_GotDepthAlert();
			totalFrames ++;
			break;
		case 2:
			//Nui_GotVideoAlert();
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
// NuiProcessThread
//
///////////////////////////////////////////////////////////////////////////////

DWORD WINAPI CKinectDevice::nuiProcessThread(LPVOID pParam)
{
#ifdef _DEBUG
	assert(pParam != _NULL);
#endif
	//Return result.
	return ((CKinectDevice *)pParam)->nuiProcessThread();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetImage
//
///////////////////////////////////////////////////////////////////////////////

_BYTE* CKinectDevice::getImage() const
{
	//Return value.
	return imageBuffer;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWidth
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectDevice::getWidth() const
{
	//Check mode.
	switch(mode)
	{
	case NUI_IMAGE_RESOLUTION_640x480:
		return 640;
	case NUI_IMAGE_RESOLUTION_320x240:
		return 320;
	default:
		break;
	}
#ifdef _DEBUG
	assert(_FALSE);
#endif
	//Return -1.
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetHeight
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectDevice::getHeight() const
{
	//Check mode.
	switch(mode)
	{
	case NUI_IMAGE_RESOLUTION_640x480:
		return 480;
	case NUI_IMAGE_RESOLUTION_320x240:
		return 240;
	default:
		break;
	}
#ifdef _DEBUG
	assert(_FALSE);
#endif
	//Return -1.
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
//
// CloseDevice
//
///////////////////////////////////////////////////////////////////////////////

void CKinectDevice::closeDevice()
{
	//Stop the Nui processing thread.
	if(nuiProcessEvent != _NULL)
	{
		//Signal the thread.
		SetEvent(nuiProcessEvent);
		//Wait for thread to stop.
		if(nuiProcess != _NULL)
		{
			//Wait process to shutdown.
			WaitForSingleObject(nuiProcess,INFINITE);
			//Close and clear handle.
			CloseHandle(nuiProcess); nuiProcess = _NULL;
		}
		//Close and clear handle.
		CloseHandle(nuiProcessEvent) , nuiProcessEvent = _NULL;
	}

	//Check instance id.
	if(instanceID != _NULL)
	{
		//Free and clear string.
		::SysFreeString((BSTR)instanceID);
		//Clear system id.
		instanceID = (BSTR)_NULL;
	}
	//Check instance.
	if(nuiInstance != _NULL)
	{
		//Shutdown.
		NUI_INSTANCE(nuiInstance)->NuiShutdown();
		//Clear instance.
		nuiInstance = (INuiInstance *)_NULL;
	}
	//Check handle.
	if(nextDepthFrameEvent &&
		nextDepthFrameEvent != INVALID_HANDLE_VALUE)
	{
		//Close handle.
		CloseHandle(nextDepthFrameEvent);
		//Clear handle.
		nextDepthFrameEvent = _NULL;
	}
	//Check handle.
	if(nextVideoFrameEvent &&
		nextVideoFrameEvent != INVALID_HANDLE_VALUE)
	{
		//Close handle.
		CloseHandle(nextVideoFrameEvent);
		//Clear handle.
		nextVideoFrameEvent = _NULL;
	}

	//Check depth buffer.
	if(depthBuffer != _NULL)
	{
		//Delete depth buffer.
		delete (_SHORT *)depthBuffer;
		//Clear depth buffer.
		depthBuffer = (_SHORT *)_NULL;
	}
	//Check image buffer.
	if(imageBuffer != _NULL)
	{
		//Delete image buffer.
		delete (_BYTE *)imageBuffer;
		//Clear image buffer.
		imageBuffer = (_BYTE *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenDevice
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CKinectDevice::openDevice(_INTEGER mode)
{
#ifdef _DEBUG
	assert(index >= 0);
	assert(nuiInstance == _NULL);
#endif
	//Create instance by index.
	if(FAILED(MSR_NuiCreateInstanceByIndex(index,(INuiInstance **)&nuiInstance))) return _FALSE;
#ifdef _DEBUG
	assert(instanceID == _NULL);
#endif
	//Get instance id.
	instanceID = NUI_INSTANCE(nuiInstance)->NuiInstanceName();
#ifdef _DEBUG
	assert(instanceID != _NULL);
#endif

	//Create event.
	nextDepthFrameEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
#ifdef _DEBUG
	assert(nextDepthFrameEvent != _NULL && nextDepthFrameEvent != INVALID_HANDLE_VALUE);
#endif
	//Create event.
	nextVideoFrameEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
#ifdef _DEBUG
	assert(nextVideoFrameEvent != _NULL && nextVideoFrameEvent != INVALID_HANDLE_VALUE);
#endif

	//Initialize instance.
	if(FAILED(NUI_INSTANCE(nuiInstance)->NuiInitialize(
										NUI_INITIALIZE_FLAG_USES_DEPTH |
										NUI_INITIALIZE_FLAG_USES_COLOR))) return _FALSE;
	//Open image stream.
	if(FAILED(NUI_INSTANCE(nuiInstance)->NuiImageStreamOpen(
										NUI_IMAGE_TYPE_COLOR,
										(NUI_IMAGE_RESOLUTION)mode,
										0,
										2,
										nextVideoFrameEvent,
										&videoStreamHandle))) return _FALSE;
#ifdef _DEBUG
	assert(videoStreamHandle != _NULL && videoStreamHandle != INVALID_HANDLE_VALUE);
#endif
	//Open depth stream.
	if(FAILED(NUI_INSTANCE(nuiInstance)->NuiImageStreamOpen(
										NUI_IMAGE_TYPE_DEPTH,
										(NUI_IMAGE_RESOLUTION)mode,
										0,
										2,
										nextDepthFrameEvent,
										&depthStreamHandle))) return _FALSE;
#ifdef _DEBUG
	assert(depthStreamHandle != _NULL && depthStreamHandle != INVALID_HANDLE_VALUE);
#endif

	//Get width.
	_INTEGER width = getWidth();
	//Get height.
	_INTEGER height = getHeight();
	//Create depth buffer.
	depthBuffer = new _SHORT[width * height];
#ifdef _DEBUG
	assert(depthBuffer != _NULL);
#endif
	//Create image buffer (X8R8G8B8).
	imageBuffer = new _BYTE[width * height * (4 * sizeof(_BYTE))];
#ifdef _DEBUG
	assert(imageBuffer != _NULL);
#endif

	//Start the Nui processing thread
	nuiProcessEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
#ifdef _DEBUG
	assert(nuiProcessEvent != _NULL && nuiProcessEvent != INVALID_HANDLE_VALUE);
#endif

	//Create process.
	nuiProcess = CreateThread(NULL,0,nuiProcessThread,this,0,NULL);
#ifdef _DEBUG
	assert(nuiProcess != _NULL);
#endif
	//Return true.
	return _TRUE;
}