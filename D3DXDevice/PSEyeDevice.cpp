///////////////////////////////////////////////////////////////////////////////
//
// PSEyeDevice.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PSEyeDevice.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "cv.h"
#include "CLEyeMulticam.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define DEFAULT_FPS											30.0f
#define DEFAULT_CLEYE_GAIN									0
#define DEFAULT_CLEYE_EXPOSURE								511
#define DEFAULT_CLEYE_ZOOM									50
#define DEFAULT_CLEYE_ROTATION								0

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CPSEyeDevice::base(L"CPSEyeDevice",L"CImageDevice");

///////////////////////////////////////////////////////////////////////////////
//
// CPSEyeDevice
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CPSEyeDevice::CPSEyeDevice(GUID guid)
{
	//Set value.
	this->guid = guid;

	//Set default value.
	imageBuffer = (_BYTE *)_NULL;
	camera = (CLEyeCameraInstance)_NULL;
	//Set default value.
	fps = DEFAULT_FPS;
	resolution = (_INTEGER)CLEYE_VGA;
	colorMode = (_INTEGER)CLEYE_COLOR_PROCESSED;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPSEyeDevice
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CPSEyeDevice::~CPSEyeDevice(void)
{
	//Close device.
	closeDevice();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCameraCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CPSEyeDevice::getCameraCount()
{
	//Return result.
	return CLEyeGetCameraCount();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCameraGuid
//
///////////////////////////////////////////////////////////////////////////////

GUID CPSEyeDevice::getCameraGuid(_INTEGER index)
{
	//Return result.
	return CLEyeGetCameraUUID(index);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetColorModeDescription
//
///////////////////////////////////////////////////////////////////////////////

_STRING CPSEyeDevice::getColorModeDescription(_INTEGER colorMode)
{
	//Check type.
	switch(colorMode)
	{
	case CLEYE_COLOR_RAW:
		return L"彩色（未经处理）";
	case CLEYE_COLOR_PROCESSED:
		return L"彩色（已经处理）";
	case CLEYE_MONO_RAW:
		return L"黑白（未经处理）";
	case CLEYE_MONO_PROCESSED:
		return L"黑白（已经处理）";
	case CLEYE_BAYER_RAW:
		return L"原始行色彩数据";
	default:
		return L"未知色彩模式";
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResolutionDescription
//
///////////////////////////////////////////////////////////////////////////////

_STRING CPSEyeDevice::getResolutionDescription(_INTEGER resolution)
{
	//Check type.
	switch(resolution)
	{
	case CLEYE_QVGA:
		return L"QVGA（320×240）";
	case CLEYE_VGA:
		return L"VGA（640×480）";
	default:
		return L"未知分辨率模式";
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFps
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CPSEyeDevice::getFps() const
{
	//Return value.
	return fps;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetColorMode
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CPSEyeDevice::getColorMode() const
{
	//Return value.
	return colorMode;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResolution
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CPSEyeDevice::getResolution() const
{
	//Return value.
	return resolution;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetValue
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CPSEyeDevice::getValue(_INTEGER parameter)
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Get value of parameter.
	return CLEyeGetCameraParameter(camera,(CLEyeCameraParameter)parameter);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetValue
//
///////////////////////////////////////////////////////////////////////////////

void CPSEyeDevice::setValue(_INTEGER parameter,_INTEGER value)
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Set value of parameter.
	CLEyeSetCameraParameter(camera,(CLEyeCameraParameter)parameter,value);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWidth
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CPSEyeDevice::getWidth() const
{
	//Check resolution.
	switch(resolution)
	{
	case CLEYE_VGA:
		return 640;
	case CLEYE_QVGA:
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

_INTEGER CPSEyeDevice::getHeight() const
{
	//Check resolution.
	switch(resolution)
	{
	case CLEYE_VGA:
		return 480;
	case CLEYE_QVGA:
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

void CPSEyeDevice::closeDevice()
{
	//Destroy image.
	destroyImage();
	//Check camera.
	if(camera != _NULL)
	{
		//Stop camera capture.
		CLEyeCameraStop(camera);
		//Destroy camera object.
		CLEyeDestroyCamera(camera);
		//Clear camera.
		camera = (CLEyeCameraInstance)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenDevice
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CPSEyeDevice::openDevice(_INTEGER colorMode,_INTEGER resolution,_FLOAT fps)
{
#ifdef _DEBUG
	assert(camera == _NULL);
#endif
	//Create camera.
	camera = CLEyeCreateCamera(guid,(CLEyeCameraColorMode)colorMode,(CLEyeCameraResolution)resolution,fps);
	//Check result.
	if(camera != NULL)
	{
		//Set some parameters.:
		CLEyeSetCameraParameter(camera,CLEYE_GAIN,DEFAULT_CLEYE_GAIN);
		CLEyeSetCameraParameter(camera,CLEYE_EXPOSURE,DEFAULT_CLEYE_EXPOSURE);
		CLEyeSetCameraParameter(camera,CLEYE_ZOOM,DEFAULT_CLEYE_ZOOM);
		CLEyeSetCameraParameter(camera,CLEYE_ROTATION,DEFAULT_CLEYE_ROTATION);
		//Dimensions.
		_INTEGER width = 0, height = 0;
		//Get camera frame dimensions.
		if(CLEyeCameraStart(camera) &&
			CLEyeCameraGetFrameDimensions(camera,width,height))
		{
			//Create image.
			if(!COpenCVImageAttribute::createImage(width,height))
			{
				//Destroy image.
				destroyImage();
			}
			else
			{
				//Get image object.
				_OBJECT imageObject = COpenCVImageAttribute::getImageObject();
#ifdef _DEBUG
				assert(imageObject != _NULL && imageBuffer == _NULL);
#endif
				//Get image raw data.
				cvGetImageRawData((IplImage *)imageObject,(uchar **)&imageBuffer);
#ifdef _DEBUG
				assert(imageBuffer != _NULL);
#endif
				//Return result.
				this->fps = fps; this->colorMode = colorMode; this->resolution = resolution; return _TRUE;
			}
		}
		//Destroy and clear camera object.
		CLEyeDestroyCamera(camera);
	}
	//Return false.
	return _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CPSEyeDevice::handleMessage(const D3DXEvent& d3dxEvent)
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
#ifdef _DEBUG
		assert(camera != _NULL && imageBuffer != _NULL);
#endif
		//Get frame.
		//Sometimes it return false.
		//It would has no effects of program.
		CLEyeCameraGetFrame(camera,(PBYTE)imageBuffer);
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != _NULL);
#endif
		//Try to open device.
		if(!openDevice(getColorMode(),getResolution(),getFps())) return E_FAIL;
		break;
	}
	//Return result.
	return CImageDevice::handleMessage(d3dxEvent);
}
