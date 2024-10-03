///////////////////////////////////////////////////////////////////////////////
//
// D3DXEvent.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_EVENT_H_
#define _D3DX_EVENT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXUtility.h"

///////////////////////////////////////////////////////////////////////////////
//
// EventID
//
///////////////////////////////////////////////////////////////////////////////

typedef enum enD3DXEventID
{
	//Handle key presses.
	d3dxMsgProc						= 0x00000100,
	//Message process.
	d3dxOnKeyboard					= 0x00000200,

	//Handle updates to the scene.
	d3dxOnFrameMove					= 0x00000800,

	//Render the scene using the D3D9 device.
	d3dxOnD3D9FrameRender			= 0x00000901,
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	d3dxOnD3D9DestroyDevice			= 0x00000902,
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	d3dxOnD3D9CreateDevice			= 0x00000903,
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	d3dxOnD3D9LostDevice			= 0x00000904,
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	d3dxOnD3D9ResetDevice			= 0x00000905,

} D3DXEventID;

///////////////////////////////////////////////////////////////////////////////
//
// MsgProc Event
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXMsgProcEvent
{
	HWND hWnd;
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
	bool* pbNoFurtherProcessing;

	///////////////////////////////////////
	//
	// Event Functions
	//
	///////////////////////////////////////
	bool IsMouseEvent() const;
	bool IsMousePickEvent() const;
	bool IsMouseReleaseEvent() const;
	bool IsMouseMoveObjectEvent() const;

} D3DXMsgProcEvent;

///////////////////////////////////////////////////////////////////////////////
//
// Keyboard Event
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXKeyboardEvent
{
	UINT nChar;
	bool bKeyDown;
	bool bAltDown;

} D3DXKeyboardEvent;

///////////////////////////////////////////////////////////////////////////////
//
// OnFrameMove Event
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXOnFrameMoveEvent
{
	double fTime;
	float fElapsedTime;
	int nMilliseconds;

} D3DXOnFrameMoveEvent;

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9FrameRender Event
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXOnD3D9FrameRenderEvent
{
	IDirect3DDevice9* pd3dDevice;
	double fTime;
	float fElapsedTime;
	int nMilliseconds;

} D3DXOnD3D9FrameRenderEvent;

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9DestroyDevice Event
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXOnD3D9DestroyDeviceEvent
{

} D3DXOnD3D9DestroyDeviceEvent;

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9CreateDevice Event
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXOnD3D9CreateDeviceEvent
{
	IDirect3DDevice9* pd3dDevice;

	UINT nWidth; //Width of back buffer.
	UINT nHeight; //Height of back buffer.
	//Details of back buffer.
	const D3DSURFACE_DESC* pBackBufferSurfaceDesc;

} D3DXOnD3D9CreateDeviceEvent;

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9LostDevice Event
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXOnD3D9LostDeviceEvent
{

} D3DXOnD3D9LostDeviceEvent;

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9ResetDevice Event
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXOnD3D9ResetDeviceEvent
{
	IDirect3DDevice9* pd3dDevice;

	UINT nWidth; //Width of back buffer.
	UINT nHeight; //Height of back buffer.
	//Details of back buffer.
	const D3DSURFACE_DESC* pBackBufferSurfaceDesc;

} D3DXOnD3D9ResetDeviceEvent;

///////////////////////////////////////////////////////////////////////////////
//
// D3DXEvent
//
///////////////////////////////////////////////////////////////////////////////

typedef struct tagD3DXEvent
{
	//Event ID
	D3DXEventID d3dxEventID;
	//Events
	union
	{
		D3DXMsgProcEvent				d3dxMsgProc;
		D3DXKeyboardEvent				d3dxKeyboard;
		
		D3DXOnFrameMoveEvent			d3dxFrameMove;

		D3DXOnD3D9FrameRenderEvent		d3dxFrameRender9;
		D3DXOnD3D9DestroyDeviceEvent	d3dxDestroyDevice9;
		D3DXOnD3D9CreateDeviceEvent		d3dxCreateDevice9;
		D3DXOnD3D9LostDeviceEvent		d3dxLostDevice9;
		D3DXOnD3D9ResetDeviceEvent		d3dxResetDevice9;
	};
	//User Context
	void* pUserContext;

} D3DXEvent;

#define GetBackBufferSurfaceWidth(p) ((p).pBackBufferSurfaceDesc != NULL ? (p).pBackBufferSurfaceDesc->Width : (p).nWidth)
#define GetBackBufferSurfaceHeight(p) ((p).pBackBufferSurfaceDesc != NULL ? (p).pBackBufferSurfaceDesc->Height : (p).nHeight)

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_EVENT_H_
