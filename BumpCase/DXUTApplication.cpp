///////////////////////////////////////////////////////////////////////////////
//
// DXUTApplication.cpp
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

#include "DXUTgui.h"
#include "SDKsound.h"

#include "BumpScene.h"
#include "ModelViewPort.h"

////////////////////////////////////////////////////////////////////////////////
//
// XNA
//
////////////////////////////////////////////////////////////////////////////////

#include "D3DX10Math.h"
#include <xnamath.h>

///////////////////////////////////////////////////////////////////////////////
//
// UI control IDs
//
///////////////////////////////////////////////////////////////////////////////

#define IDC_STATIC                                          -1

#define IDC_TOGGLEFULLSCREEN                                1
#define IDC_TOGGLEREF                                       2
#define IDC_CHANGEDEVICE                                    3

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

static CDXUTApplication dxutApplication;

///////////////////////////////////////////////////////////////////////////////
//
// GetApplication
//
///////////////////////////////////////////////////////////////////////////////

CDXUTApplication* CDXUTApplication::getApplication()
{
	//Return result.
	return &dxutApplication;
}

///////////////////////////////////////////////////////////////////////////////
//
// CDXUTApplication
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CDXUTApplication::CDXUTApplication(void)
{
	//Set default value.
	g_pCM = NULL;
	g_pCMList = NULL;

	//Set view port.
	CViewPortApplication::setViewPort(new CModelViewPort());
	//Set background.
	CSceneApplication::setBackground(new CBackgroundScene());

	//用于检测所有基础几合体的碰撞模拟问题。
	CSceneApplication::setForeground(new CBumpScene());
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CDXUTApplication
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CDXUTApplication::~CDXUTApplication(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// GetForceShader
//
///////////////////////////////////////////////////////////////////////////////

int CDXUTApplication::GetForceShader(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_ForceShader;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsInvalidSoundDriver
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsInvalidSoundDriver(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_InvalidSoundDriver ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsInvalidDriver
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsInvalidDriver(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_InvalidDriver ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsOldSoundDriver
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsOldSoundDriver(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_OldSoundDriver ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsOldDriver
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsOldDriver(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_OldDriver ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsUnsupportedCard
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsUnsupportedCard(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_UnsupportedCard ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsPrototypeCard
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsPrototypeCard(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_PrototypeCard ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsDisableSpecular
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsSpecularDisabled(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_DisableSpecular ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsFixedFunctionEnabled
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsFixedFunctionEnabled(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_UseFixedFunction ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsAnisotropicFilterEnabled
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsAnisotropicFilterEnabled(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_UseAnisotropicFilter ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMaximuResolution
//
///////////////////////////////////////////////////////////////////////////////

DWORD CDXUTApplication::GetMaximumResolution(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_MaximumResolution;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsSafeMode
//
///////////////////////////////////////////////////////////////////////////////

bool CDXUTApplication::IsSafeMode(void)
{
#ifdef _DEBUG
	assert(g_pCM != NULL);
#endif
	//Return result.
	return g_pCM->cf_SafeMode ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//
// ToggleShowHelp
//
///////////////////////////////////////////////////////////////////////////////

void CDXUTApplication::ToggleShowHelp(void)
{
	//Toggle show help.
	g_TxtHelper.ToggleShowHelp();
}

///////////////////////////////////////////////////////////////////////////////
//
// ChangeDevice
//
///////////////////////////////////////////////////////////////////////////////

void CDXUTApplication::ChangeDevice(void)
{
	//Change device.
	g_SettingsDlg.SetActive(!g_SettingsDlg.IsActive());
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CDXUTApplication::handleMessage(const D3DXEvent& d3dxEvent)
{
	//New event.
	D3DXEvent newEvent;
	//Copy event.
	memcpy(&newEvent,&d3dxEvent,sizeof(D3DXEvent));
	//Set view port.
	newEvent.pUserContext = (void *)this;

	//Open lock.
	openLock();
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Handle key presses.
	case d3dxMsgProc:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing != NULL);
#endif
		//Pass messages to dialog resource manager calls so GUI state is updated correctly.
		if(g_DialogResourceManager.MsgProc(d3dxEvent.d3dxMsgProc.hWnd,
											d3dxEvent.d3dxMsgProc.uMsg,
											d3dxEvent.d3dxMsgProc.wParam,
											d3dxEvent.d3dxMsgProc.lParam))
		{
			//Set flag.
			*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
		}
		else if(g_SettingsDlg.IsActive())
		{
			//Process message.
			g_SettingsDlg.MsgProc(d3dxEvent.d3dxMsgProc.hWnd,
									d3dxEvent.d3dxMsgProc.uMsg,
									d3dxEvent.d3dxMsgProc.wParam,
									d3dxEvent.d3dxMsgProc.lParam);
		}
		else if(g_HUD.MsgProc(d3dxEvent.d3dxMsgProc.hWnd,
								d3dxEvent.d3dxMsgProc.uMsg,
								d3dxEvent.d3dxMsgProc.wParam,
								d3dxEvent.d3dxMsgProc.lParam))
		{
			//Set flag.
			*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
		}
		else if(g_SampleUI.MsgProc(d3dxEvent.d3dxMsgProc.hWnd,
									d3dxEvent.d3dxMsgProc.uMsg,
									d3dxEvent.d3dxMsgProc.wParam,
									d3dxEvent.d3dxMsgProc.lParam))
		{
			//Set flag.
			*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
		}
		else
		{
			//Check mouse event.
			if(d3dxEvent.d3dxMsgProc.IsMouseEvent())
			{
				CNormalString value;
				//Append.
				value.append(L"鼠标状态：");
				if(newEvent.d3dxMsgProc.uMsg == WM_MOUSEMOVE) value.append(L"正在移动");
				else if(newEvent.d3dxMsgProc.uMsg == WM_LBUTTONDOWN) value.append(L"左键按下");
				else if(newEvent.d3dxMsgProc.uMsg == WM_MBUTTONDOWN) value.append(L"中键按下");
				else if(newEvent.d3dxMsgProc.uMsg == WM_RBUTTONDOWN) value.append(L"右键按下");
				else if(newEvent.d3dxMsgProc.uMsg == WM_LBUTTONDBLCLK) value.append(L"左键双击");
				else if(newEvent.d3dxMsgProc.uMsg == WM_MBUTTONDBLCLK) value.append(L"中键双击");
				else if(newEvent.d3dxMsgProc.uMsg == WM_RBUTTONDBLCLK) value.append(L"右键双击");
				else if(newEvent.d3dxMsgProc.uMsg == WM_LBUTTONUP) value.append(L"左键抬起");
				else if(newEvent.d3dxMsgProc.uMsg == WM_MBUTTONUP) value.append(L"中键抬起");
				else if(newEvent.d3dxMsgProc.uMsg == WM_RBUTTONUP) value.append(L"右键抬起");
				else if(newEvent.d3dxMsgProc.uMsg == WM_MOUSEWHEEL) value.append(L"滚轮滑动");
				//value.append()
				value.append(L"(")->append(( short )LOWORD( newEvent.d3dxMsgProc.lParam ))->append(L",")->append(( short )HIWORD( newEvent.d3dxMsgProc.lParam ))->append(L")");
				g_TxtHelper.SetIndicationText(value);
			}

			//Check message.
			if(d3dxEvent.d3dxMsgProc.IsMousePickEvent()) handlePickEvent(newEvent);
			else if(d3dxEvent.d3dxMsgProc.IsMouseMoveObjectEvent()) handleMoveEvent(newEvent);
			else if(d3dxEvent.d3dxMsgProc.IsMouseReleaseEvent())
			{
				//Clear body controller.
				if(CPhysicsApplication::isRunning())
				{
					//Get foreground.
					CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
					assert(foreground != _NULL);
#endif
					//Get picked object.
					CWorldObject* worldObject = foreground->getPickedObject();
					//Check result.
					if(worldObject != _NULL && worldObject->isPhysicsObject())
					{
						//Clear controller.
						CPhysicsApplication::clearController((CPhysicsObject *)worldObject->getPhysics());
					}
				}
			}
			
			//Handle message process.
			if(CViewPortApplication::handleMessage(newEvent))
			{
				//Set flag.
				*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
			}
			//Handle message process.
			else if(CSceneApplication::handleMessage(newEvent))
			{
				//Set flag.
				*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
			}
		}
		break;
	//Message process.
	case d3dxOnKeyboard:
		//Check keydown.
		if(d3dxEvent.d3dxKeyboard.bKeyDown)
		{
			//Check value.
			if(d3dxEvent.d3dxKeyboard.nChar == VK_F1)
			{
				//Show help.
				g_TxtHelper.ToggleShowHelp();
			}
			else
			{
				//Get foreground.
				CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
				assert(foreground != _NULL);
#endif
				//Handle message.
				foreground->handleMessage(newEvent);
			}
		}
		break;
	//Handle updates to the scene.
	case d3dxOnFrameMove:
		//Do simulation.
		CPhysicsApplication::doSimulation();
		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		break;
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxFrameRender9.pd3dDevice != NULL);
#endif
		//Initialize render state.
		initializeRenderState(d3dxEvent.d3dxCreateDevice9.pd3dDevice);
		//If the settings dialog is being shown, then render it instead of rendering the app's scene.
		if(g_SettingsDlg.IsActive())
		{
			//Call frame render.
			g_SettingsDlg.OnRender(d3dxEvent.d3dxFrameRender9.fElapsedTime);
		}
		else
		{
			//Clear backckground.
			clearBackground(d3dxEvent.d3dxFrameRender9.pd3dDevice);
			//Render the scene.
			if(SUCCEEDED(d3dxEvent.d3dxFrameRender9.pd3dDevice->BeginScene()))
			{
				//Get view port.
				CViewPort* viewPort = getViewPort();
#ifdef _DEBUG
				assert(viewPort != _NULL);
#endif
				//Next timestamp.
				viewPort->nextFrameStamp();

				//Get background.
				CBackgroundScene* background = getBackground();
#ifdef _DEBUG
				assert(background != _NULL);
#endif
				//Set view port.
				background->setViewPort(viewPort);
				//Handle message.
				background->handleMessage(newEvent);

				//Get foreground.
				CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
				assert(foreground != _NULL);
#endif
				//Set view port.
				foreground->setViewPort(viewPort);
				//Handle message.
				foreground->handleMessage(newEvent);

				//These events are to help PIX identify what the code is doing.
				//Begin performance event.
				DXUT_BeginPerfEvent(DXUT_PERFEVENTCOLOR,L"HUD");
				//Render
				g_TxtHelper.handleMessage(newEvent);
				//Render dialog.
				g_HUD.OnRender(d3dxEvent.d3dxFrameRender9.fElapsedTime);
				//Render dialog.
				g_SampleUI.OnRender(d3dxEvent.d3dxFrameRender9.fElapsedTime);
				//End performance event.
				DXUT_EndPerfEvent();

				//End scence.
				d3dxEvent.d3dxFrameRender9.pd3dDevice->EndScene();
			}
		}
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Handle message.
		g_DialogResourceManager.OnD3D9DestroyDevice();
		g_SettingsDlg.OnD3D9DestroyDevice();
		g_TxtHelper.handleMessage(newEvent);

		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		InitializeConfig(d3dxEvent.d3dxCreateDevice9.pd3dDevice);
	    g_DialogResourceManager.OnD3D9CreateDevice(d3dxEvent.d3dxCreateDevice9.pd3dDevice);
		g_SettingsDlg.OnD3D9CreateDevice(d3dxEvent.d3dxCreateDevice9.pd3dDevice);
		g_TxtHelper.handleMessage(newEvent);

		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Handle message.
		g_DialogResourceManager.OnD3D9LostDevice();
		g_SettingsDlg.OnD3D9LostDevice();
		g_TxtHelper.handleMessage(newEvent);

		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Set resource manager.
		g_DialogResourceManager.OnD3D9ResetDevice();
		//Set settings dialog.
		g_SettingsDlg.OnD3D9ResetDevice();

		//Set dialogs.
		//Set location.
		g_HUD.SetLocation(GetBackBufferSurfaceWidth(d3dxEvent.d3dxResetDevice9) - 170,0);
		//Set size.
		g_HUD.SetSize(170,170);

		//Set controls.
		//Set location.
		g_SampleUI.SetLocation(GetBackBufferSurfaceWidth(d3dxEvent.d3dxResetDevice9) - 170,
							   GetBackBufferSurfaceHeight(d3dxEvent.d3dxResetDevice9) - 350);
		//Set size.
		g_SampleUI.SetSize(170,300);

		//Handle message.
		g_TxtHelper.handleMessage(newEvent);

		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		break;
	}
	//Close lock.
	closeLock();
	//Return result.
	return CD3DXObject::handleMessage(newEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnGUIEvent
//
// Handles the GUI events.
//
///////////////////////////////////////////////////////////////////////////////

void CALLBACK OnGUIEvent(UINT nEvent,int nControlID,CDXUTControl* pControl,void* pUserContext)
{
	//Check control id.
    switch(nControlID)
    {
    case IDC_TOGGLEREF:
		//Toggle REF.
        DXUTToggleREF();
		break;
    case IDC_TOGGLEFULLSCREEN:
		//Toggle full screen.
        DXUTToggleFullScreen();
		break;
    case IDC_CHANGEDEVICE:
		//Set active.
		DXUT_APPLICATION->ChangeDevice();
		break;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeApplication
//
// Render the scene using the D3D9 device.
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CDXUTApplication::InitializeApplication(void)
{
	//Initialize dialog resource.
    g_SettingsDlg.Init(&g_DialogResourceManager);
	//Initialize dialog resource.
    g_HUD.Init(&g_DialogResourceManager);
	//Initialize dialog resource.
    g_SampleUI.Init(&g_DialogResourceManager);

	//Set callback of dialog.
    g_HUD.SetCallback(OnGUIEvent);
	
	int iY = 10;
	//Add button.
    g_HUD.AddButton(IDC_TOGGLEFULLSCREEN,L"全屏显示切换",35,iY,125,22);
    g_HUD.AddButton(IDC_TOGGLEREF,L"软件模拟(F3)",35,iY += 24,125,22,VK_F3);
    g_HUD.AddButton(IDC_CHANGEDEVICE,L"调整参数(F2)",35,iY += 24,125,22,VK_F2);

	//Set callback of dialog.
    g_SampleUI.SetCallback(OnGUIEvent);
	//Return OK.
	return S_OK;
}

//--------------------------------------------------------------------------------------
// CheckForSafeMode searches launch state files written by previous instances of the
// application. It is called during program launch and program shutdown. During
// initialization, it enables the safe mode flag if a previous instance did not shut
// down properly. When shutting down, it deletes those orphaned launch state files so
// that the next launch can go normally without entering safe mode.
//--------------------------------------------------------------------------------------
void CheckForSafeMode( WCHAR* wszLaunchFile, bool& bSafeMode, bool bInitialize )
{
    HRESULT hr;

    if( !bInitialize )
    {
        // If shutting down, remove the launch state file that this current instance wrote.
        ::DeleteFile( wszLaunchFile );
    }

    // Check for initialization flag from previous launch.
    // We use SHGetFolderPath with CSIDL_LOCAL_APPDATA to write to
    // a subdirectory of Documents and Settings\<username>\Local Settings\Application Data.
    // It is the best practice to write user-specific data under the user profile directory
    // because not every user on the system will always have write access to the application
    // executable directory.
    WCHAR wszPath[MAX_PATH];
    ::GetModuleFileName( NULL, wszPath, MAX_PATH );
    hr = ::SHGetFolderPath( NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, wszPath );
    if( SUCCEEDED( hr ) )
    {
        // Create the directory for this application. We don't care
        // if the directory already exists as long as it exists after
        // this point.
        wcscat_s( wszPath, MAX_PATH, L"\\ConfigSystem" );
        ::CreateDirectory( wszPath, NULL );

        // Search for launch*.sta. For each file found, we extract the process ID
        // from the file name and search for the process. If we cannot find the
        // process with the same ID, then that instance of app did not shut down
        // properly, and we should enable safe mode.
        WCHAR wszSearch[MAX_PATH];
        wcscpy_s( wszSearch, MAX_PATH, wszPath );
        wcscat_s( wszSearch, MAX_PATH, L"\\launch*.sta" );
        WIN32_FIND_DATAW fd;
        HANDLE hFind = ::FindFirstFile( wszSearch, &fd );
        while( INVALID_HANDLE_VALUE != hFind )
        {
            // Extract the process ID from the file name.
            WCHAR wszPid[MAX_PATH];
            wcscpy_s( wszPid, MAX_PATH, fd.cFileName + 6 );
            WCHAR* pDot = wcsstr( wszPid, L".sta" );
            if( pDot )
            {
                *pDot = L'\0';

                // wszPid now holds the PID in string form.
                DWORD dwPid = _wtol( wszPid );
                HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE, dwPid );
                DWORD dwExitCode = 0;
                if( hProcess )
                    GetExitCodeProcess( hProcess, &dwExitCode );
                if( !hProcess || STILL_ACTIVE != dwExitCode )
                {
                    // Launch state file exists but the process does not.
                    // Now check the state file again in the rare case
                    // that the process shuts down right after we check
                    // the existence of the file but before the call
                    // to OpenProcess().

                    wcscpy_s( wszSearch, MAX_PATH, wszPath );
                    wcscat_s( wszSearch, MAX_PATH, L"\\" );
                    wcscat_s( wszSearch, MAX_PATH, fd.cFileName );
                    if( ::GetFileAttributes( wszSearch ) != INVALID_FILE_ATTRIBUTES )
                    {
                        // File still exists. Process was not shut down properly.
                        if( bInitialize )
                        {
                            // When initializing, enable safe mode.
                            bSafeMode = true;
                            break;
                        }
                        else
                        {
                            // When shutting down, delete each orphaned launch state file.
                            ::DeleteFile( wszSearch );
                        }
                    }
                }
                else
                    CloseHandle( hProcess );
            }

            // Find the next file
            if( !::FindNextFile( hFind, &fd ) )
                break;
        }

        ::FindClose( hFind );

        if( bInitialize )
        {
            // When initializing, create Launch%PID%.sta in the ConfigSystem's app data folder.
            // This serves as a way to "register" this instance of the app.
            swprintf_s( wszLaunchFile, MAX_PATH, L"%s\\launch%u.sta", wszPath, GetCurrentProcessId() );
            HANDLE hFile = ::CreateFile( wszLaunchFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
                                         NULL );
            if( hFile != INVALID_HANDLE_VALUE )
                ::CloseHandle( hFile );
        }
    }
}

//--------------------------------------------------------------------------------------
//Initialize config
//--------------------------------------------------------------------------------------
HRESULT CDXUTApplication::InitializeConfig(IDirect3DDevice9* pd3dDevice)
{
    HRESULT hr;

    // Verify requirement and prompt the user if any requirement is not met.
    hr = g_pCM->VerifyRequirements();
    if( FAILED( hr ) )
    {
        DXUTShutdown( 0 );
        return S_OK;
    }

    // Obtain the CConfigManager object for the 3D device created.
    // Point g_pCM to the CConfigManager object.
    D3DCAPS9 Caps;
    pd3dDevice->GetDeviceCaps( &Caps );
    g_pCM = g_pCMList + Caps.AdapterOrdinal;

    // Check for unsupported display device.
    if( g_pCM->cf_UnsupportedCard )
    {
        ::MessageBox( NULL, L"显示设备不支持该应用。"
                      L"程序将退出。", L"系统提示", MB_OK | MB_ICONERROR );
        return E_FAIL;
    }

    // Check for invalid display driver
    if( g_pCM->cf_InvalidDriver )
    {
        ::MessageBox( NULL, L"显示驱动和现有应用不兼容。"
                      L"程序将退出。", L"系统提示", MB_OK | MB_ICONERROR );
        return E_FAIL;
    }

    // Check for old display driver
    if( g_pCM->cf_OldDriver )
    {
        ::MessageBox( NULL, L"显示驱动已经过时。建议您安装最新的驱动。"
                      L"请安装最新驱动。", L"系统提示", MB_OK | MB_ICONWARNING );
    }

    // Check for known prototype card
    if( g_pCM->cf_PrototypeCard )
    {
        ::MessageBox( NULL, L"检测到无法确定类型的显示卡。"
					  L"建议您使用有支持能力的显示卡来运行程序。", L"系统提示", MB_OK | MB_ICONWARNING );
    }

    // Check for invalid sound driver
    if( g_pCM->cf_InvalidSoundDriver )
    {
        ::MessageBox( NULL, L"声音驱动和现有应用不兼容。"
                      L"程序将退出。", L"系统提示", MB_OK | MB_ICONERROR );
        return E_FAIL;
    }

    // Check for old sound driver
    if( g_pCM->cf_OldSoundDriver )
    {
        ::MessageBox( NULL, L"声音驱动已过时。"
					  L"建议您安装最新的声音设备驱动。", L"系统提示", MB_OK | MB_ICONWARNING );
    }

    // Go through the list of resolution and remove those that are excluded for this card.
    CD3D9EnumAdapterInfo* pAdapterInfo = DXUTGetD3D9Enumeration()->GetAdapterInfo( Caps.AdapterOrdinal );
    for( int idm = pAdapterInfo->displayModeList.GetSize() - 1; idm >= 0; --idm )
    {
        D3DDISPLAYMODE DisplayMode = pAdapterInfo->displayModeList.GetAt( idm );

        if( DisplayMode.Width > g_pCM->cf_MaximumResolution )
            pAdapterInfo->displayModeList.Remove( idm );
    }

	//Return result.
	return S_OK;
}

//--------------------------------------------------------------------------------------
// Initialize window
//--------------------------------------------------------------------------------------
HRESULT CDXUTApplication::InitializeWindow( void )
{
	HRESULT hr = S_FALSE;
	bool bSafeMode = false;
    WCHAR wszLaunchFile[MAX_PATH] = L"";

    // Initialize config information for all available 3D devices after DXUTInit is called
    // because we would like to do this as soon as we have a D3D object.
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    assert( pD3D != NULL );

    // Allocate the CM array to hold all devices on the system.
    g_pCMList = new CConfigManager[pD3D->GetAdapterCount()];
    if( !g_pCMList )
    {
        // If we cannot allocate memory for the CM array.  The system must
        // be in a critical state.  Do not proceed in this case.
        ::MessageBox( NULL, L"系统没有足够的内存来运行应用。", L"系统提示", MB_OK );
    }
    else
    {
        // Obtain sound information (device GUID)
        GUID guidDeviceId;
        GetDeviceID( &DSDEVID_DefaultPlayback, &guidDeviceId );

        WCHAR str[MAX_PATH];
        hr = DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"config.txt" );

        if( FAILED( hr ) )
        {
            MessageBox( NULL, L"未能找到配置文件。所有的属性和配置都将设置为缺省值。",
						L"配置文件丢失！", MB_OK | MB_ICONEXCLAMATION );
        }

        // Initialize CM objects, one for each 3D device
        for( DWORD dev = 0; dev < pD3D->GetAdapterCount(); ++dev )
        {
            D3DADAPTER_IDENTIFIER9 id;
            D3DCAPS9 Caps;
            pD3D->GetAdapterIdentifier( dev, 0, &id );
            pD3D->GetDeviceCaps( dev, D3DDEVTYPE_HAL, &Caps );
            g_pCMList[dev].Initialize( str, id, Caps, guidDeviceId );
            // Propagate safe mode flag
            g_pCMList[dev].cf_SafeMode = bSafeMode;
        }

        // Make g_pCM point to the first element in g_pCMList by default.
        // OnCreateDevice will make it point to the correct element later.
        g_pCM = g_pCMList;

        // Handle window creation
        DXUTCreateWindow( L"仿真实验室——碰撞演示" );

        // Initialize sound after we have the window
		initializeSounds();

        hr = DXUTCreateDevice( true, 640, 480 );
        if( SUCCEEDED( hr ) )
        {
            // Pass control to DXUT for handling the message pump and 
            // dispatching render calls. DXUT will call your FrameMove 
            // and FrameRender callback when there is idle time between handling window messages.
            DXUTMainLoop();
        }
        delete[] g_pCMList;
    }

	return hr;
}
