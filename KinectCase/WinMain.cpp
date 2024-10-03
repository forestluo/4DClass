///////////////////////////////////////////////////////////////////////////////
//
// WinMain.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "DXUTApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DX10Math.h"
#include <xnamath.h>

#include "KinectDevice.h"

///////////////////////////////////////////////////////////////////////////////
//
// Declaration
//
///////////////////////////////////////////////////////////////////////////////

void CheckForSafeMode( WCHAR* wszLaunchFile,bool& bSafeMode,bool bInitialize);

///////////////////////////////////////////////////////////////////////////////
//
// MsgProc
//
// Handle messages to the application.
//
///////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK MsgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam,
					     bool* pbNoFurtherProcessing,void* pUserContext)
{
	//Event.
	D3DXEvent d3dxEvent;
	
#ifdef _DEBUG
	assert(pbNoFurtherProcessing != NULL);
#endif
	
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxMsgProc;
	d3dxEvent.d3dxMsgProc.hWnd = hWnd;
	d3dxEvent.d3dxMsgProc.uMsg = uMsg;
	d3dxEvent.d3dxMsgProc.wParam = wParam;
	d3dxEvent.d3dxMsgProc.lParam = lParam;
	d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = pbNoFurtherProcessing;
	d3dxEvent.pUserContext = pUserContext;
	//Return result.
	return DXUT_APPLICATION->handleMessage(d3dxEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnKeyboard
//
// Handle key presses.
//
///////////////////////////////////////////////////////////////////////////////

void CALLBACK OnKeyboard(UINT nChar,bool bKeyDown,bool bAltDown,void* pUserContext)
{
	//Event.
	D3DXEvent d3dxEvent;

	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnKeyboard;
	d3dxEvent.d3dxKeyboard.nChar = nChar;
	d3dxEvent.d3dxKeyboard.bKeyDown = bKeyDown;
	d3dxEvent.d3dxKeyboard.bAltDown = bAltDown;
	d3dxEvent.pUserContext = pUserContext;
	//Handle message.
	DXUT_APPLICATION->handleMessage(d3dxEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9DestroyDevice
//
// Release D3D9 resources created in the OnD3D9CreateDevice callback. 
//
///////////////////////////////////////////////////////////////////////////////

void CALLBACK OnD3D9DestroyDevice(void* pUserContext)
{
	//Event.
	D3DXEvent d3dxEvent;

	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9DestroyDevice;
	d3dxEvent.pUserContext = pUserContext;
	//Handle message.
	DXUT_APPLICATION->handleMessage(d3dxEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9CreateDevice
//
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size.
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CALLBACK OnD3D9CreateDevice(IDirect3DDevice9* pd3dDevice,
	                                const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext)
{
	//Event.
	D3DXEvent d3dxEvent;

#ifdef _DEBUG
	assert(pd3dDevice != NULL);
	assert(pBackBufferSurfaceDesc != NULL);
#endif

	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9CreateDevice;
	d3dxEvent.d3dxCreateDevice9.pd3dDevice = pd3dDevice;
	d3dxEvent.d3dxCreateDevice9.pBackBufferSurfaceDesc = pBackBufferSurfaceDesc;
	d3dxEvent.pUserContext = pUserContext;
	//Handle message.
	return DXUT_APPLICATION->handleMessage(d3dxEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9LostDevice
//
// Release D3D9 resources created in the OnD3D9ResetDevice callback.
//
///////////////////////////////////////////////////////////////////////////////

void CALLBACK OnD3D9LostDevice(void* pUserContext)
{
	//Event.
	D3DXEvent d3dxEvent;

	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9LostDevice;
	d3dxEvent.pUserContext = pUserContext;
	//Handle message.
	DXUT_APPLICATION->handleMessage(d3dxEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9ResetDevice
//
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size.
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CALLBACK OnD3D9ResetDevice(IDirect3DDevice9* pd3dDevice,
                                   const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
								   void* pUserContext)
{
	//Event.
	D3DXEvent d3dxEvent;

#ifdef _DEBUG
	assert(pd3dDevice != NULL);
	assert(pBackBufferSurfaceDesc != NULL);
#endif

	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9ResetDevice;
	d3dxEvent.d3dxResetDevice9.pd3dDevice = pd3dDevice;
	d3dxEvent.d3dxResetDevice9.pBackBufferSurfaceDesc = pBackBufferSurfaceDesc;
	d3dxEvent.pUserContext = pUserContext;
	//Handle message.
	return DXUT_APPLICATION->handleMessage(d3dxEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnFrameMove
//
// Handle updates to the scene.
// This is called regardless of which D3D API is used.
//
///////////////////////////////////////////////////////////////////////////////

void CALLBACK OnFrameMove(double fTime,float fElapsedTime,void* pUserContext)
{
	//Event.
	D3DXEvent d3dxEvent;

	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnFrameMove;
	d3dxEvent.d3dxFrameMove.fTime = fTime;
	d3dxEvent.d3dxFrameMove.fElapsedTime = fElapsedTime;
	d3dxEvent.d3dxFrameMove.nMilliseconds = ::GetTickCount();
	d3dxEvent.pUserContext = pUserContext;
	//Handle message.
	DXUT_APPLICATION->handleMessage(d3dxEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnD3D9FrameRender
//
// Render the scene using the D3D9 device.
//
///////////////////////////////////////////////////////////////////////////////

void CALLBACK OnD3D9FrameRender(IDirect3DDevice9* pd3dDevice,double fTime,float fElapsedTime,void* pUserContext)
{
	//Event.
	D3DXEvent d3dxEvent;

#ifdef _DEBUG
	assert(pd3dDevice != NULL);
#endif

	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9FrameRender;
	d3dxEvent.d3dxFrameRender9.pd3dDevice = pd3dDevice;
	d3dxEvent.d3dxFrameRender9.fTime = fTime;
	d3dxEvent.d3dxFrameRender9.fElapsedTime = fElapsedTime;
	d3dxEvent.d3dxFrameRender9.nMilliseconds = ::GetTickCount();
	d3dxEvent.pUserContext = pUserContext;
	//Handle message.
	DXUT_APPLICATION->handleMessage(d3dxEvent);
}

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat,
                                      D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    // Skip backbuffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    // No fallback defined by this app, so reject any device that 
    // doesn't support at least ps2.0
    if( pCaps->PixelShaderVersion < D3DPS_VERSION( 2, 0 ) )
        return false;

    return true;
}

//--------------------------------------------------------------------------------------
// Called right before creating a D3D9 or D3D10 device, allowing the app to modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    assert( DXUT_D3D9_DEVICE == pDeviceSettings->ver );

    HRESULT hr;
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    D3DCAPS9 caps;

    V( pD3D->GetDeviceCaps( pDeviceSettings->d3d9.AdapterOrdinal,
                            pDeviceSettings->d3d9.DeviceType,
                            &caps ) );

    // If device doesn't support HW T&L or doesn't support 1.1 vertex shaders in HW 
    // then switch to SWVP.
    if( ( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) == 0 ||
        caps.VertexShaderVersion < D3DVS_VERSION( 1, 1 ) )
    {
        pDeviceSettings->d3d9.BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }

    // Debugging vertex shaders requires either REF or software vertex processing 
    // and debugging pixel shaders requires REF.  
#ifdef DEBUG_VS
    if( pDeviceSettings->d3d9.DeviceType != D3DDEVTYPE_REF )
    {
        pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
        pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_PUREDEVICE;
        pDeviceSettings->d3d9.BehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }
#endif
#ifdef DEBUG_PS
    pDeviceSettings->d3d9.DeviceType = D3DDEVTYPE_REF;
#endif
    // For the first device created if its a REF device, optionally display a warning dialog box
    static bool s_bFirstTime = true;
    if( s_bFirstTime )
    {
        s_bFirstTime = false;
        if( pDeviceSettings->d3d9.DeviceType == D3DDEVTYPE_REF )
            DXUTDisplaySwitchingToREFWarning( pDeviceSettings->ver );
    }

    return true;
}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	HRESULT hr;
	bool bSafeMode = false;
    WCHAR wszLaunchFile[MAX_PATH] = L"";

	//Check kinect.
	if( CKinectDevice::getKinectCount() <= 0)
	{
		MessageBox( NULL, TEXT("这个应用需要Kinect设备做支持。"),
			TEXT("仿真实验室"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

    // XNAMath uses SSE/SSE2 instructions on Windows. We should verify the CPU supports these instructions
    // as early in the program as possible
    if ( !XMVerifyCPUSupport() )
    {
        MessageBox( NULL, TEXT("这个应用需要处理器支持SSE2指令。"),
                    TEXT("仿真实验室"), MB_OK | MB_ICONEXCLAMATION);
        return -1;
    }

    // DXUT will create and use the best device (either D3D9 or D3D10) 
    // that is available on the system depending on which D3D callbacks are set below

    // Set DXUT callbacks
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackKeyboard( OnKeyboard );
    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );

    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    
	DXUTSetCursorSettings( true, true );

	//Initialize application.
	if(FAILED(DXUT_APPLICATION->InitializeApplication()))
	{
        MessageBox( NULL, TEXT("应用初始化失败。\n\n程序将要退出。"),
                    TEXT("仿真实验室"), MB_OK | MB_ICONEXCLAMATION);
        return -1;
	}

    // Check if safe mode is desired.
    CheckForSafeMode( wszLaunchFile, bSafeMode, true );

    // When initializing, prompt the user to enter safe mode.
    if( bSafeMode )
    {
        if( IDNO == ::MessageBox( NULL, L"应用在上次启动中初始化失败。推荐您在安全模式下运行该程序。\n\n是否运行安全模式？",
                                  L"系统提示", MB_YESNO | MB_ICONQUESTION ) )
            bSafeMode = false;
    }

    DXUTInit( true, true, NULL ); // Parse the command line, show msgboxes on error, no extra command line params
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys

	// Initialize window
	hr = DXUT_APPLICATION->InitializeWindow();
	// Check result
    if( SUCCEEDED( hr ) )
    {
        // Program completed.  Do safe mode clean up.
        CheckForSafeMode( wszLaunchFile, bSafeMode, false );
    }

	//Return exit code.
    return DXUTGetExitCode();
}
