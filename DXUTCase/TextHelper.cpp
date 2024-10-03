///////////////////////////////////////////////////////////////////////////////
//
// TextHelper.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "TextHelper.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "DXUTApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CTextHelper::base(L"CTextHelper",L"CD3DXObject");

///////////////////////////////////////////////////////////////////////////////
//
// CTextHelper
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CTextHelper::CTextHelper(void)
{
	//Set default value.
	g_bShowHelp = true;

	//Set default value.
	g_pFont = NULL;
	g_pSprite = NULL;
	g_pTxtHelper = NULL;

	g_strHelp = L"按ESC退出";
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CTextHelper
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CTextHelper::~CTextHelper(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Render
//
// Render the help and statistics text.
// This function uses the ID3DXFont interface for efficient text rendering.
//
///////////////////////////////////////////////////////////////////////////////

void CTextHelper::Render()
{
    // The helper object simply helps keep track of text position, and color
    // and then it calls pFont->DrawText( m_pSprite, strMsg, -1, &rc, DT_NOCLIP, m_clr );
    // If NULL is passed in as the sprite object, then it will work however the 
    // pFont->DrawText() will not be batched together.  Batching calls will improves performance.
    const D3DSURFACE_DESC* pd3dsdBackBuffer = DXUTGetD3D9BackBufferSurfaceDesc();

    // Output statistics
    g_pTxtHelper->Begin();
    g_pTxtHelper->SetInsertionPos( 5, 5 );
    g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
    g_pTxtHelper->DrawTextLine( DXUTGetFrameStats( DXUTIsVsyncEnabled() ) );
    g_pTxtHelper->DrawTextLine( DXUTGetDeviceStats() );

	// Check indication
	if(g_strIndication.length() > 0)
	{
	    g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
		g_pTxtHelper->DrawTextLine( g_strIndication.getCString() );
	}

    // List properties that have been applied.
    // Since IConfigDatabase only lives within CConfigManager::Initialize,
    // we check all properties and print them one by one.  This is ok since
    // this code is usually only used for informational purposes only.
    g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 0.0f, 1.0f, 0.0f, 1.0f ) );
    int iY = pd3dsdBackBuffer->Height - 24;
	if( DXUT_APPLICATION->GetForceShader() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        switch( DXUT_APPLICATION->GetForceShader() )
        {
            case 9999:
                g_pTxtHelper->DrawTextLine( L"ForceShader=0 (Shader is disabled)" ); break;
            case 9998:
                g_pTxtHelper->DrawTextLine( L"ForceShader=A2 (Forcing ps_2_a target)" ); break;
            case 9997:
                g_pTxtHelper->DrawTextLine( L"ForceShader=B2 (Forcing ps_2_b target)" ); break;
            default:
                g_pTxtHelper->DrawFormattedTextLine( L"ForceShader=%d (Forcing ps_%d_%d target)", DXUT_APPLICATION->GetForceShader(),
                                                 DXUT_APPLICATION->GetForceShader() / 10, DXUT_APPLICATION->GetForceShader() % 10 );
        }
        iY -= 16;
    }
	if( DXUT_APPLICATION->IsInvalidSoundDriver() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"无效的声卡驱动(声卡驱动与当前应用不兼容)" );
        iY -= 16;
    }
	if( DXUT_APPLICATION->IsInvalidDriver() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"无效的显卡驱动(显卡驱动与当前应用不兼容)" );
        iY -= 16;
    }
    if( DXUT_APPLICATION->IsOldSoundDriver() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"过时的声卡驱动(声卡驱动低于所要求的版本)" );
        iY -= 16;
    }
    if( DXUT_APPLICATION->IsOldDriver() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"过时的显卡驱动(显卡驱动低于所要求的版本)" );
        iY -= 16;
    }
    if( DXUT_APPLICATION->IsUnsupportedCard() )  // Should never see this. Included here anyways.
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"显卡无法支持(显示卡能力低于当前的要求)" );
        iY -= 16;
    }
    if( DXUT_APPLICATION->IsPrototypeCard() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"显卡类型未知(无法确认显示卡的类型)" );
        iY -= 16;
    }
    if( DXUT_APPLICATION->IsSpecularDisabled() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"禁止镜面高光(镜面高光已关闭)" );
        iY -= 16;
    }
    if( DXUT_APPLICATION->IsFixedFunctionEnabled() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"使用修正功能(渲染时强制使用修正功能)" );
        iY -= 16;
    }
    if( DXUT_APPLICATION->IsAnisotropicFilterEnabled() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawTextLine( L"启用各向异性过滤(纹理的各项异性过滤已开启)" );
        iY -= 16;
    }
    if( DXUT_APPLICATION->GetMaximumResolution() )
    {
        g_pTxtHelper->SetInsertionPos( 10, iY );
        g_pTxtHelper->DrawFormattedTextLine( L"最大分辨率=%d(最大分辨率的宽度限制为%d)",
                                         DXUT_APPLICATION->GetMaximumResolution(), DXUT_APPLICATION->GetMaximumResolution() );
        iY -= 16;
    }

    g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    g_pTxtHelper->SetInsertionPos( 5, iY - 4 );
    g_pTxtHelper->DrawTextLine( L"配置选项:" );

    iY -= 24;
    g_pTxtHelper->SetInsertionPos( 5, iY );
    g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 0.0f, 0.0f, 1.0f ) );
    if( DXUT_APPLICATION->IsSafeMode() )
        g_pTxtHelper->DrawTextLine( L"安全模式\n" );

    // Draw help
    if( g_bShowHelp )
    {
        g_pTxtHelper->SetInsertionPos( pd3dsdBackBuffer->Width - 150, pd3dsdBackBuffer->Height - 15 * 6 );
        g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 0.75f, 0.0f, 1.0f ) );
        g_pTxtHelper->DrawTextLine( L"按F1隐藏帮助" );

		// Check help
		if( g_strHelp.length() > 0)
		{
			g_pTxtHelper->SetInsertionPos( pd3dsdBackBuffer->Width - 130, pd3dsdBackBuffer->Height - 15 * 5 );
			g_pTxtHelper->DrawTextLine( g_strHelp.getCString() );
			/*
			g_pTxtHelper->DrawTextLine( L"移动位置: W,S,A,D\n"
									L"旋转视角: 鼠标右键\n"
									L"退出: 按ESC" );*/
		}
    }
    else
    {
        g_pTxtHelper->SetInsertionPos( pd3dsdBackBuffer->Width - 150, pd3dsdBackBuffer->Height - 15 * 2 );
        g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
        g_pTxtHelper->DrawTextLine( L"按F1显示帮助" );
    }
    g_pTxtHelper->End();
}

///////////////////////////////////////////////////////////////////////////////
//
// ToggleShowHelp
//
///////////////////////////////////////////////////////////////////////////////

void CTextHelper::ToggleShowHelp(void)
{
	//Toggle the value.
	g_bShowHelp = !g_bShowHelp;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetHelpText
//
///////////////////////////////////////////////////////////////////////////////

void CTextHelper::SetHelpText(const CNormalString& strHelp)
{
#ifdef _DEBUG
	assert(strHelp.length() > 0);
#endif
	//Set value.
	g_strHelp = strHelp;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetIndicationText
//
///////////////////////////////////////////////////////////////////////////////

void CTextHelper::SetIndicationText(const CNormalString& strIndication)
{
#ifdef _DEBUG
	assert(strIndication.length() > 0);
#endif
	//Set value.
	g_strIndication = strIndication;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CTextHelper::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
		Render();
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Release font.
		SAFE_RELEASE(g_pFont);
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Return result.
		return D3DXCreateFont(d3dxEvent.d3dxCreateDevice9.pd3dDevice,
							  15,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,
							  OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,L"Arial",&g_pFont);
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Call process.
		if(g_pFont != NULL) g_pFont->OnLostDevice();
		//Release sprite.
		SAFE_RELEASE(g_pSprite);
		//Release text helper.
		SAFE_DELETE(g_pTxtHelper);
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Call process.
		if(g_pFont != NULL) V_RETURN(g_pFont->OnResetDevice());
		//Create sprite.
		V_RETURN(D3DXCreateSprite(d3dxEvent.d3dxCreateDevice9.pd3dDevice,&g_pSprite));
		//Create text helper.
		g_pTxtHelper = new CDXUTTextHelper(g_pFont,g_pSprite,NULL,NULL,15);
		//Return result.
		return hr;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
