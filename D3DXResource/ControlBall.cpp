///////////////////////////////////////////////////////////////////////////////
//
// 4DObject.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ControlBall.h"

///////////////////////////////////////////////////////////////////////////////
//
// CControlBall
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CControlBall::CControlBall(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CControlBall
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CControlBall::~CControlBall(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// OnBegin
//
/////////////////////////////////////////////////////////////////////////////////

void CControlBall::OnBegin(int nX,int nY,D3DXMATRIXA16* pmInvViewRotate)
{
#ifdef _DEBUG
	assert(pmInvViewRotate != NULL);
#endif
    m_bDrag = true;
    m_qDown = m_qNow;
    m_vDownPt = ScreenToVector( ( float )nX, ( float )nY );
    D3DXVECTOR4 v;
    D3DXVec3Transform( &v, &m_vDownPt, pmInvViewRotate );
    m_vDownPt = ( D3DXVECTOR3 )v;
}

///////////////////////////////////////////////////////////////////////////////
//
// OnMove
//
/////////////////////////////////////////////////////////////////////////////////

void CControlBall::OnMove(int nX,int nY,D3DXMATRIXA16* pmInvViewRotate)
{
#ifdef _DEBUG
	assert(pmInvViewRotate != NULL);
#endif

    if( m_bDrag )
    {
        m_vCurrentPt = ScreenToVector( ( float )nX, ( float )nY );
        D3DXVECTOR4 v;
        D3DXVec3Transform( &v, &m_vCurrentPt, pmInvViewRotate );
        m_vCurrentPt = ( D3DXVECTOR3 )v;
        m_qNow = m_qDown * QuatFromBallPoints( m_vDownPt, m_vCurrentPt );
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessages
//
/////////////////////////////////////////////////////////////////////////////////

LRESULT CControlBall::HandleMessages(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam,D3DXMATRIXA16* pmInvViewRotate)
{
#ifdef _DEBUG
	assert(pmInvViewRotate != NULL);
#endif

	// Current mouse position
    int iMouseX = ( short )LOWORD( lParam );
    int iMouseY = ( short )HIWORD( lParam );

    switch( uMsg )
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            SetCapture( hWnd );
            OnBegin( iMouseX, iMouseY, pmInvViewRotate );
            return TRUE;

        case WM_LBUTTONUP:
            ReleaseCapture();
            OnEnd();
            return TRUE;

        case WM_CAPTURECHANGED:
            if( ( HWND )lParam != hWnd )
            {
                ReleaseCapture();
                OnEnd();
            }
            return TRUE;

        case WM_MOUSEMOVE:
            if( MK_LBUTTON & wParam )
            {
                OnMove( iMouseX, iMouseY, pmInvViewRotate );
            }
            return TRUE;
    }

    return FALSE;
}
