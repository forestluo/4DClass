///////////////////////////////////////////////////////////////////////////////
//
// MFCApplication.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _MFC_APPLICATION_H_
#define _MFC_APPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "XD3D.h"
#include "SimpleThread.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

class CMFCApplication :
	public CD3DXApplication, 
	public CXD3D, public CSimpleThread
{
private:
	/**
	 * Focused object.
	 */
	CD3DXObject* focused;

public:
	CMFCApplication(void);
	virtual ~CMFCApplication(void);

protected:
	/**
	 * Process.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL process();

public:

	/**
	 * Uninitialize.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void uninitialize();

	/**
	 * D3D initializer.
	 *
	 * @param hWnd Handle of window.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT initialize(HWND hWnd);

public:

	/**
	 * Clear focused object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearFocused();

	/**
	 * Get focused object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Focused object.</p>
	 */
	CD3DXObject* getFocused();

	/**
	 * Set focused object.
	 *
	 * @param focused Focused object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFocused(CD3DXObject* focused);

private:
	///////////////////////////////////////
	//
	//D3D overrides.
	//All these functions equal to DXUT events.
	HRESULT InitDeviceObjects();		//Equal to "create device".
	HRESULT RestoreDeviceObjects();		//Equal to "reset device".
    HRESULT FrameMove();				//Equal to "frame move".
	HRESULT Render();					//Equal to "frame render".
	HRESULT InvalidateDeviceObjects();	//Equal to "lost device".
	HRESULT DeleteDeviceObjects();		//Equal to "destroy device".
	//
	///////////////////////////////////////

public:
	///////////////////////////////////////
	//
	//Handle keyboard message.
	HRESULT handleKeyboardMessage(UINT nChar,bool bKeyDown,bool bAltDown);
	//Handle mouse message.
	HRESULT handleMouseMessage(UINT message, WPARAM wParam, LPARAM lParam);
	//
	///////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////////////
#endif //_MFC_APPLICATION_H_
