///////////////////////////////////////////////////////////////////////////////
//
// MFCApplication.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "MFCApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DTime.h"

///////////////////////////////////////////////////////////////////////////////
//
// CMFCApplication
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CMFCApplication::CMFCApplication(void)
	: CSimpleThread(L"MFCApplication")
{
	//Set default value.
	focused = (CD3DXObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CMFCApplication
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CMFCApplication::~CMFCApplication(void)
{
	//Clear focused object.
	focused = (CD3DXObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearFocused
//
///////////////////////////////////////////////////////////////////////////////

void CMFCApplication::clearFocused()
{
	//Open lock.
	openLock();
	{
		//Set value.
		this->focused = (CD3DXObject *)_NULL;
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFocused
//
///////////////////////////////////////////////////////////////////////////////

CD3DXObject* CMFCApplication::getFocused()
{
	//Value.
	CD3DXObject* object;
	//Open lock.
	openLock();
	{
		//Set value.
		object = focused;
	}
	//Close lock.
	closeLock();
	//Return result.
	return object;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetFocused
//
///////////////////////////////////////////////////////////////////////////////

void CMFCApplication::setFocused(CD3DXObject* focused)
{
	//Open lock.
	openLock();
	{
		//Set value.
		this->focused = focused;
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// Process
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CMFCApplication::process()
{
	//Open lock.
	openLock();
	{
		//Check pause status.
		CXD3D::RenderEnvironment();
	}
	//Close lock.
	closeLock();
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// Unintialize
//
///////////////////////////////////////////////////////////////////////////////

void CMFCApplication::uninitialize()
{
	//Shutdown.
	CSimpleThread::shutdown();

	//Open lock.
	openLock();
	{
		//Clear focused.
		clearFocused();
		///////////////////////////////////////
		//
		//Cleanup environment.
		CXD3D::CleanupEnvironment();
		//Clear wnd.
		CXD3D::m_hWndRender = (HWND)_NULL;
		//
		///////////////////////////////////////
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::initialize(HWND hWnd)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(hWnd != _NULL);
#endif
	//Get safe handle.
	CXD3D::m_hWndRender = hWnd;
	//Enable depth buffer.
	CXD3D::Enumeration.AppUsesDepthBuffer = true;
	//Return result.
	V_RETURN(CXD3D::CreateD3D());
	//Startup thread.
	return CSimpleThread::startup() ? S_OK : E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
//
// InitDeviceObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::InitDeviceObjects()
{
	//Result.
	HRESULT hr;
	//Event.
	D3DXEvent d3dxEvent;

	//Check device.
	if(CXD3D::m_pd3dDevice == _NULL) return E_FAIL;
	//Clear event.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9CreateDevice;
	d3dxEvent.d3dxCreateDevice9.pd3dDevice = CXD3D::m_pd3dDevice;
	d3dxEvent.d3dxCreateDevice9.nWidth = CXD3D::m_rcClient.right - CXD3D::m_rcClient.left;
	d3dxEvent.d3dxCreateDevice9.nHeight = CXD3D::m_rcClient.bottom - CXD3D::m_rcClient.top;
	//Handle message.
	V_RETURN(CD3DXApplication::handleMessage(d3dxEvent));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// RestoreDeviceObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::RestoreDeviceObjects()
{
	//Result.
	HRESULT hr;
	//Event.
	D3DXEvent d3dxEvent;

	//Check device.
	if(CXD3D::m_pd3dDevice == _NULL) return E_FAIL;
	//Clear memory.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9ResetDevice;
	d3dxEvent.d3dxResetDevice9.pd3dDevice = CXD3D::m_pd3dDevice;
	d3dxEvent.d3dxCreateDevice9.nWidth = CXD3D::m_rcClient.right - CXD3D::m_rcClient.left;
	d3dxEvent.d3dxCreateDevice9.nHeight = CXD3D::m_rcClient.bottom - CXD3D::m_rcClient.top;
	//Handle message.
	V_RETURN(CD3DXApplication::handleMessage(d3dxEvent));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// FrameMove
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::FrameMove()
{
	//Result.
	HRESULT hr;
	//Event.
	D3DXEvent d3dxEvent;
	//Clear event.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnFrameMove;
	d3dxEvent.d3dxFrameMove.fTime = CXD3D::m_fTime;
	d3dxEvent.d3dxFrameMove.fElapsedTime = CXD3D::m_fElapsedTime;
	d3dxEvent.d3dxFrameMove.nMilliseconds = ::GetTickCount();
	//Handle message.
	V_RETURN(CD3DXApplication::handleMessage(d3dxEvent));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// Render
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::Render()
{
	//Result.
	HRESULT hr;
	//Event.
	D3DXEvent d3dxEvent;

	//Check device.
	if(CXD3D::m_pd3dDevice == _NULL) return E_FAIL;
	//Clear device.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9FrameRender;
	d3dxEvent.d3dxFrameRender9.pd3dDevice = CXD3D::m_pd3dDevice;
	d3dxEvent.d3dxFrameRender9.fTime = m_fTime;
	d3dxEvent.d3dxFrameRender9.fElapsedTime = m_fElapsedTime;
	d3dxEvent.d3dxFrameRender9.nMilliseconds = ::GetTickCount();
	//Handle message.
	V_RETURN(CD3DXApplication::handleMessage(d3dxEvent));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// InvalidateDeviceObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::InvalidateDeviceObjects()
{
	//Result
	HRESULT hr;
	//Event.
	D3DXEvent d3dxEvent;
	//Clear event.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9LostDevice;
	//Handle message.
	V_RETURN(CD3DXApplication::handleMessage(d3dxEvent));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// DeleteDeviceObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::DeleteDeviceObjects()
{
	//Result.
	HRESULT hr;
	//Event.
	D3DXEvent d3dxEvent;
	//Clear memory.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9DestroyDevice;
	//Handle message.
	V_RETURN(CD3DXApplication::handleMessage(d3dxEvent));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleKeyboardMessages
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::handleKeyboardMessage(UINT nChar,bool bKeyDown,bool bAltDown)
{
	//Result.
	HRESULT hr;
	//Event.
	D3DXEvent d3dxEvent;
	//Clear message.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnKeyboard;
	d3dxEvent.d3dxKeyboard.nChar = nChar;
	d3dxEvent.d3dxKeyboard.bKeyDown = bKeyDown;
	d3dxEvent.d3dxKeyboard.bAltDown = bAltDown;
	//Handle message.
	V_RETURN(CD3DXApplication::handleMessage(d3dxEvent));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleKeyboardMessages
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CMFCApplication::handleMouseMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	//Result.
	HRESULT hr;
	//Event.
	D3DXEvent d3dxEvent;
	//No further processing.
	bool bNoFurtherProcessing = false;//Be sure of it. Otherwise there would be an exception.
	//Clear memory.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxMsgProc;
	d3dxEvent.d3dxMsgProc.hWnd = CXD3D::m_hWndRender;
	d3dxEvent.d3dxMsgProc.uMsg = message;
	d3dxEvent.d3dxMsgProc.wParam = wParam;
	d3dxEvent.d3dxMsgProc.lParam = lParam;
	d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = &bNoFurtherProcessing;
	//Handle message.
	V_RETURN(CD3DXApplication::handleMessage(d3dxEvent));
	//Return true.
	return hr;
}
