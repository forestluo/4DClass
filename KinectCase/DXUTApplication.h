///////////////////////////////////////////////////////////////////////////////
//
// DXUTApplication.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _DXUT_APPLICATION_H_
#define _DXUT_APPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "TextHelper.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Config System
//
///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4995)
#include <stdio.h>
#include <shlobj.h>
#include "ConfigDatabase.h"
#include "ConfigManager.h"
#pragma warning(default: 4995)

///////////////////////////////////////////////////////////////////////////////
//
// DXUTApplication
//
///////////////////////////////////////////////////////////////////////////////

class CDXUTApplication : public CD3DXApplication
{
private:

	///////////////////////////////////////
	//
	// Text Helper
	//
	///////////////////////////////////////
	CTextHelper						g_TxtHelper;

	///////////////////////////////////////
	//
	// Dialogs
	//
	///////////////////////////////////////
	//Dialog for standard controls.
	CDXUTDialog						g_HUD;
	//Dialog for sample specific controls.
	CDXUTDialog						g_SampleUI;
	//Device settings dialog.
	CD3DSettingsDlg					g_SettingsDlg;
	//Manager for shared resources of dialogs.
	CDXUTDialogResourceManager		g_DialogResourceManager;

	///////////////////////////////////////
	//
	// Configs
	//
	///////////////////////////////////////
	//Active CM. Points to one of the elements in g_pCMList.
	CConfigManager*					g_pCM;           
	//Array of CConfigManager, one for each display device on system
	CConfigManager*					g_pCMList;

public:
	CDXUTApplication(void);
	virtual ~CDXUTApplication(void);

	///////////////////////////////////////
	//
	// Configs
	//
	// These functions can only be used under DXUT.
	//
	///////////////////////////////////////
	int GetForceShader(void);
	bool IsInvalidSoundDriver(void);
	bool IsInvalidDriver(void);
	bool IsOldSoundDriver(void);
	bool IsOldDriver(void);
	bool IsUnsupportedCard(void);
	bool IsPrototypeCard(void);
	bool IsSpecularDisabled(void);
	bool IsFixedFunctionEnabled(void);
	bool IsAnisotropicFilterEnabled(void);
	DWORD GetMaximumResolution(void);
	bool IsSafeMode(void);

	///////////////////////////////////////
	//
	// Basic Functions
	//
	// These functions can only be used under DXUT.
	//
	///////////////////////////////////////
	void ChangeDevice(void);
	void ToggleShowHelp(void);

	/**
	 * Get application.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Application.</p>
	 */
	static CDXUTApplication* getApplication();

protected:

	///////////////////////////////////////
	//
	// Initialize Functions
	//
	///////////////////////////////////////
	//Initialize application.
	virtual HRESULT InitializeApplication(void);
	//Initialize window.
	virtual HRESULT InitializeWindow(void);
	//Initialize config.
	virtual HRESULT InitializeConfig(IDirect3DDevice9* pd3dDevice);

	///////////////////////////////////////
	//
	// Kinect Devices
	//
	///////////////////////////////////////
	void openKinectDevices();
	void addDepthFilter(const CNormalString& name,const CNormalString& deviceName);
	void addInputTexture(const CNormalString& name,const CNormalString& deviceName);
	void closeInputTextures();
	void closeFilters();
	void closeKinectDevices();
	void addControlledItemArray(const CNormalString& name,const CNormalString& deviceName);

public:

	///////////////////////////////////////
	//
	// HandleMessage
	//
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Friend Functions
	//
	friend int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nCmdShow);
	//
	friend void CALLBACK OnKeyboard(UINT nChar,bool bKeyDown,bool bAltDown,void* pUserContext);
	friend LRESULT CALLBACK MsgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam,bool* pbNoFurtherProcessing,void* pUserContext);
	//
	friend void CALLBACK OnFrameMove(double fTime,float fElapsedTime,void* pUserContext);
	friend void CALLBACK OnD3D9FrameRender(IDirect3DDevice9* pd3dDevice,double fTime,float fElapsedTime,void* pUserContext);
	//
	friend void CALLBACK OnD3D9LostDevice(void* pUserContext);
	friend HRESULT CALLBACK OnD3D9ResetDevice(IDirect3DDevice9* pd3dDevice,const D3DSURFACE_DESC* pBackBufferSurfaceDesc,void* pUserContext);
	//
	friend void CALLBACK OnD3D9DestroyDevice(void* pUserContext);
	friend HRESULT CALLBACK OnD3D9CreateDevice(IDirect3DDevice9* pd3dDevice,const D3DSURFACE_DESC* pBackBufferSurfaceDesc,void* pUserContext);
	//
	friend bool CALLBACK IsD3D9DeviceAcceptable(D3DCAPS9* pCaps,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,bool bWindowed,void* pUserContext);
	friend bool CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings,void* pUserContext);
	//
	///////////////////////////////////////
};

//Application
#define DXUT_APPLICATION (CDXUTApplication::getApplication())

///////////////////////////////////////////////////////////////////////////////
#endif //_DXUT_APPLICATION_H_
