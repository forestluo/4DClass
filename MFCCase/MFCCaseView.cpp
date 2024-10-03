// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MFCCaseView.cpp : implementation of the CMFCCaseView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCCase.h"
#endif

#include "MFCCaseDoc.h"
#include "MFCCaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCCaseView

IMPLEMENT_DYNCREATE(CMFCCaseView, CView)

BEGIN_MESSAGE_MAP(CMFCCaseView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCCaseView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CMFCCaseView::OnButtonStart)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_START, &CMFCCaseView::OnUpdateButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CMFCCaseView::OnButtonStop)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_STOP, &CMFCCaseView::OnUpdateButtonStop)
END_MESSAGE_MAP()

// CMFCCaseView construction/destruction

CMFCCaseView::CMFCCaseView()
{
	// TODO: add construction code here

}

CMFCCaseView::~CMFCCaseView()
{
}

BOOL CMFCCaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCCaseView drawing

void CMFCCaseView::OnDraw(CDC* /*pDC*/)
{
	CMFCCaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCCaseView printing


void CMFCCaseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCCaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCCaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCCaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCCaseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CMFCCaseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCCaseView diagnostics

#ifdef _DEBUG
void CMFCCaseView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCCaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCCaseDoc* CMFCCaseView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCCaseDoc)));
	return (CMFCCaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCCaseView message handlers


void CMFCCaseView::OnDestroy()
{
	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check result.
	if(pDoc->application != NULL)
	{
		//Uninitialize.
		pDoc->application->uninitialize();
	}
	//Destroy.
	__super::OnDestroy();
}

void CMFCCaseView::OnInitialUpdate()
{
	//On initial update.
	__super::OnInitialUpdate();

	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check result.
	if(pDoc->application != NULL)
	{
		//Check simulator.
		if(pDoc->application->CPhysicsApplication::isRunning())
		{
			//Stop simulation.
			pDoc->application->CPhysicsApplication::shutdown();
		}
		//Check initialized.
		if(pDoc->application->CXD3D::IsActive())
		{
			//Clear focused.
			pDoc->application->clearFocused();
			//Clear foreground.
			pDoc->application->clearForeground();
		}
		else
		{
			//Initialize D3DX.
			if(FAILED(pDoc->application->initialize(GetSafeHwnd()))) PostQuitMessage(1);
		}
	}
}

BOOL CMFCCaseView::OnEraseBkgnd(CDC* pDC)
{
	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Return directly.
	return pDoc->application != NULL ? TRUE : __super::OnEraseBkgnd(pDC);
}

void CMFCCaseView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Handle size changed.
	if(pDoc->application != NULL)
	{
		//Open lock.
		pDoc->application->openLock();
		{
			//Handle message.
			pDoc->application->HandlePossibleSizeChange();
		}
		//Close lock.
		pDoc->application->closeLock();
	}
}

LRESULT CMFCCaseView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	//Get document.
	CMFCCaseDoc* pDoc =(CMFCCaseDoc*)m_pDocument;
	// TODO: Add your specialized code here and/or call the base class
	if(pDoc != NULL && pDoc->application != NULL && pDoc->application->CXD3D::IsActive())
	{
		//Handle mouse messages.
		if(pDoc->application->handleMouseMessage(message,wParam,lParam)) return FALSE;
	}
	//Return result.
	return __super::WindowProc(message, wParam, lParam);
}

void CMFCCaseView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check application.
	if(pDoc->application != NULL)
	{
		//Handle keyboard message.
		pDoc->application->handleKeyboardMessage(nChar,true,(nFlags >> 13) & 0x01);
	}

	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMFCCaseView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check application.
	if(pDoc->application != NULL)
	{
		//Handle keyboard message.
		pDoc->application->handleKeyboardMessage(nChar,false,(nFlags >> 13) & 0x01);
	}

	__super::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CMFCCaseView::OnButtonStart()
{
	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	pDoc->application->CD3DXApplication::startup();
}


void CMFCCaseView::OnUpdateButtonStart(CCmdUI *pCmdUI)
{
	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CMFCCaseView::OnButtonStop()
{
	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	pDoc->application->CD3DXApplication::shutdown();
}


void CMFCCaseView::OnUpdateButtonStop(CCmdUI *pCmdUI)
{
	CMFCCaseDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && pDoc->application->CPhysicsApplication::isRunning());
}
