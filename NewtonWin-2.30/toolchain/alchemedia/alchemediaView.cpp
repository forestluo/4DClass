/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaView.cpp
// Purpose:     
// Author:      Julio Jerez
// Modified by: 
// Created:     22/05/2010 08:02:08
// RCS-ID:      
// Copyright:   Copyright (c) <2010> <Newton Game Dynamics>
// License:     
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely
/////////////////////////////////////////////////////////////////////////////

// alchemediaView.cpp : implementation of the alchemediaView class
//

#include "alchemediaStdafx.h"
#include "alchemedia.h"
#include "alchemediaDoc.h"
#include "alchemediaView.h"
#include "alchemediaScene.h"
#include "alchemediaMainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



IMPLEMENT_DYNCREATE(alchemediaView, CView)

BEGIN_MESSAGE_MAP(alchemediaView, CView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEWERMENU_MAXIMIZE, &alchemediaView::OnViewermenuMaximize)
	ON_COMMAND(ID_VIEWERMENU_SELECT, &alchemediaView::OnViewermenuSelect)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// alchemediaView construction/destruction

alchemediaView::alchemediaView()
	:m_renderContext(NULL)
	,m_mainFrame(NULL)
	,m_myCameraIndex (0)
{
	// TODO: add construction code here
//	m_renderMode = m_hiddenline;
//	m_renderMode = m_wireframe;
	m_renderMode = m_gouraud;
	m_viewMode = alchemediaCamera::m_perspective;
	
}

alchemediaView::~alchemediaView()
{
	if (m_renderContext) {
		wglDeleteContext (m_renderContext);
	}

//	if (m_deviceContext) {
//		delete m_deviceContext;
//	}
}

BOOL alchemediaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}


// alchemediaView message handlers

int alchemediaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	// add the toolbar control
	int DEFAULT_TOOLBAR_STYLE = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC;
	m_toolBar.Create(this, DEFAULT_TOOLBAR_STYLE, IDR_VIEWER_TOOLBAR);


	SIZE size;
	size.cx = 24;
	size.cy = 24;
//	m_toolBar.SetLargeIcons(TRUE);
	m_toolBar.SetSizes(size, size);
	m_toolBar.LoadToolBar(IDR_VIEWER_TOOLBAR, 0, 0, TRUE);
//	m_toolBar.LoadBitmap(IDR_VIEWER_TOOLBAR, 0, 0, TRUE);
	
	m_toolBar.SetPaneStyle(m_toolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_toolBar.SetPaneStyle(m_toolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_toolBar.SetOwner(this);


	for (int i = 0; i < m_toolBar.GetCount(); i ++) {
		UINT nID;
		UINT nStyle;
		int iImage;
		m_toolBar.GetButtonInfo(i, nID, nStyle, iImage);
		m_toolBar.GetButtonInfo(i, nID, nStyle, iImage);
//		switch (nID) 
//		{
//			case ID_VIEWERMENU_CAMERA:
//			case ID_VIEWERMENU_ZOOM:
//			case ID_VIEWERMENU_PAN:
//			case ID_VIEWERMENU_SELECT:
//			case ID_VIEWERMENU_TRANSLATE:
//			case ID_VIEWERMENU_ROTATE:
//			case ID_VIEWERMENU_SCALE:
//			{
//				m_toolBar.SetButtonStyle (i, TBBS_CHECKBOX);
//			}
//		}
	}
//	SelectToolBarBottom (ID_VIEWERMENU_SELECT);



	// All commands will be routed via this control , not via the parent frame:
	m_toolBar.SetRouteCommandsViaFrame(FALSE);

	m_toolBar.m_viewPort = this;

	CDC* const cdc = GetDC(); /* get the device context for a particular window */
	if (!SelectPixelFormat()) {
		return -1;
	}

	HDC hdc = cdc->GetSafeHdc();

	m_renderContext = wglCreateContext(hdc);
	_ASSERTE (m_renderContext);
	wglMakeCurrent(hdc, m_renderContext);

	GetClientRect(&m_oldRect);

	PIXELFORMATDESCRIPTOR pfd;
	int n = ::GetPixelFormat(hdc);
	::DescribePixelFormat(hdc, n, sizeof(pfd), &pfd);

	InitGraphicsSystem();
	return 0;
}



bool alchemediaView::SelectPixelFormat(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |			// support OpenGL
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	int pixelformat;

	CDC* const cdc = GetDC(); /* get the device context for a particular window */
	HDC hdc = cdc->GetSafeHdc();
	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == 0 ) {
		MessageBox("ChoosePixelFormat failed");
		return false;
	}

	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE) {
		MessageBox("SetPixelFormat failed");
		return false;
	}
	return true;
}

// Initializes the Graphics System
void alchemediaView::InitGraphicsSystem(void)
{
	glShadeModel (GL_SMOOTH);

	// Culling. 
	glCullFace (GL_BACK);
	glFrontFace (GL_CCW);
	glEnable (GL_CULL_FACE);

	// z buffer test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

	// Set the clear color. 
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// Change to the projection matrix and set our viewing volume.
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity( );

	// set on ambient directional light
	GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 0.0 };
	GLfloat lightAmbientColor[] = { 0.7f, 0.7f, 0.7f, 0.0 };
	GLfloat lightPosition[] = { 500.0f, 200.0f, 500.0f, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}



/*
void alchemediaView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void alchemediaView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}
*/

// alchemediaView diagnostics

#ifdef _DEBUG
void alchemediaView::AssertValid() const
{
	CView::AssertValid();
}

void alchemediaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

alchemediaDoc* alchemediaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(alchemediaDoc)));
	return (alchemediaDoc*)m_pDocument;
}
#endif //_DEBUG


BOOL alchemediaView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void alchemediaView::SetDefaultLight(void)
{
	dMatrix matrix;	
	glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0][0]);
	matrix = matrix.Inverse();

	GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 0.0 };
	GLfloat lightAmbientColor[] = { 1.0f, 1.0f, 1.0f, 0.0 };
	GLfloat lightDiffuseColor[] = { 1.0f, 1.0f, 1.0f, 0.0 };
	matrix.m_posit.m_w = 0.0f;

	glLightfv(GL_LIGHT0, GL_POSITION, &matrix.m_posit[0]);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, &matrix.m_front[0]);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


// alchemediaView drawing

void alchemediaView::OnDraw(CDC* dc)
{
	alchemediaDoc* doc = GetDocument();
	ASSERT_VALID(doc);
	if (!(doc && doc->GetCurWorld()))
		return;


	BOOL state = wglMakeCurrent(dc->GetSafeHdc(), m_renderContext);
	_ASSERTE (state);

	glClearColor (0.5f, 0.5f, 0.5f, 1.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	naPersitanceWorld& world = m_mainFrame->GetWorld(); 
	alchemediaScene* scene = doc->GetCurWorld();

	alchemediaScene::dTreeNode* camNode = scene->FindCameraNode(m_myCameraIndex);
	alchemediaCamera* camera = (alchemediaCamera*) scene->GetInfoFromNode (camNode);


	RECT rect;
	GetClientRect(&rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
//	if (m_viewMode != camera->GetViewMode()) {
//		camera->SetViewMode(m_viewMode);
//	}


//camera->SetPointOfInterest (dVector (0, 15, 0));

	// set the camera project 
	camera->SetProjectionMode(width, height);


//camera->SetPointOfInterest(dVector (0.0f, 2.5f, -10.0f, 0.0f));
camera->SetCameraOrigin(dVector (0.0f, 2.5f, 0.0f, 0.0f));
camera->SetCameraYaw (90.0f * 3.1416f /180.0f);
//camera->SetPointOfInterest(dVector (12.0f, 15.0f, -0.0f, 0.0f));
//camera->SetCameraYaw (180.0f * 3.1416f /180.0f);

camera->SetCameraRoll(0.0f);




	// set the camera view matrix.
	camera->SetCameraMatrix();

	// draw the deconstruction grid
	camera->DrawConstructionGrid();

	// set the default light 
	SetDefaultLight ();

	dVector color (1.0f, 1.0f, 0.0f, 0.0f);

	switch (m_renderMode) 
	{
		case m_wireframe:
		{
			camera->DrawWireFrame(scene, camNode, color);
			break;
		}

		case m_hiddenline:
		{
			camera->DrawSolidWireFrame(scene, camNode, color);
			camera->DrawWireFrame(scene, camNode, color);
			break;
		}

		case m_gouraud:
		{
			camera->DrawGouraudShaded(scene, camNode, color);
camera->DrawWireFrame(scene, camNode, color);
			break;
		}

		case m_shaded:
		{
			_ASSERTE (0);
			camera->DrawShaded(scene, camNode, color);
			break;
		}
	}

/*
	// Render axis system and coordinate system of each selected body
	camera->DrawGizmo (scene, camNode, GetIdentityMatrix(), color, indexBuffer, sizeof (indexBuffer), dNodeInfo::m_selection, 40.0f);

	switch (m_navigationMode)
	{
	case ID_VIEWERMENU_SELECT:
		DrawNavigationGizmos (dNodeInfo::m_selection, color, indexBuffer, sizeof (indexBuffer));
		break;
	case ID_VIEWERMENU_TRANSLATE:
		DrawNavigationGizmos (dNodeInfo::m_translation, color, indexBuffer, sizeof (indexBuffer));
		break;

	case ID_VIEWERMENU_ROTATE:
		DrawNavigationGizmos (dNodeInfo::m_rotation, color, indexBuffer, sizeof (indexBuffer));
		break;

	case ID_VIEWERMENU_SCALE:
		DrawNavigationGizmos (dNodeInfo::m_scale, color, indexBuffer, sizeof (indexBuffer));
		break;

	case ID_VIEWERMENU_CAMERA:
	case ID_VIEWERMENU_ZOOM:
	case ID_VIEWERMENU_PAN:
		_ASSERTE (0);
		break;
	}


	//	if (m_curInfoHightlighted && (m_highLightedHandle != dNodeInfo::m_noHandle)) {
	if (m_currHighLightedNode) {
		//dNodeInfo* info = world->GetInfoFromNode(m_curInfoHightlighted);
		dSceneNodeInfo* info = (dSceneNodeInfo*) scene->GetInfoFromNode (m_currHighLightedNode);
		dMatrix alignmentMatrix (GetCoordinateMatrix(info));

		dNodeInfo::dGizmoMode gizmoMode = dNodeInfo::m_selection;
		if (m_navigationMode == m_translate) {
			gizmoMode = dNodeInfo::m_translation;
		} else if (m_navigationMode == m_rotate) {
			gizmoMode = dNodeInfo::m_rotation;
		} else if (m_navigationMode == m_scale) {
			gizmoMode = dNodeInfo::m_scale;
		}
		//dScene* world, const dMatrix& coordinaSystem, dGizmoMode mode, dGizmoHandle handle, const dVector& color, dFloat size) const
		info->DrawGizmoHandle(scene, alignmentMatrix, gizmoMode, m_gizmoHandle, dVector (1.0f, 1.0f, 0.0f, 0.0f), m_mainFrame->GetGizmoScale());
	}
*/
	glFinish();
//	SwapBuffers(m_deviceContextHandle);
	SwapBuffers(dc->GetSafeHdc());
}



void alchemediaView::OnSize(UINT nType, int cx, int cy)
{
	CSize size (m_toolBar.CalcSize(FALSE));
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	HDWP tmp;
	CRect rect;
	GetWindowRect(rect);
	rect.bottom = rect.top + size.cy;
	m_toolBar.MovePane(rect, TRUE, tmp);
}

void alchemediaView::OnViewermenuMaximize()
{
	// TODO: Add your command handler code here
	m_mainFrame->GetSplitter().ToggleViewPort(this);
}

void alchemediaView::OnViewermenuSelect()
{
	// TODO: Add your command handler code here
}

void alchemediaView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);

/*
	neMainFrame* mainFrame =(neMainFrame*)wxGetApp().GetTopWindow();
	neMultiWorld* multiWorld = mainFrame->GetWorld();
	neEditorWorld* world = multiWorld->GetCurWorld();
	//	nePersistenceSelection* selection = world->GetPersistenceSelection();
	neSceneExplorer* explorer = (neSceneExplorer*) mainFrame->GetCommandPanel()->FindWindow(_T("neSceneExplorer"));
	explorer->DeselectAll();
*/


	alchemediaDoc* doc = GetDocument();
	ASSERT_VALID(doc);
	if (!(doc && doc->GetCurWorld()))
		return;

	//	naPersitanceWorld& world = m_mainFrame->GetWorld(); 
	alchemediaScene* scene = doc->GetCurWorld();

	alchemediaScene::dTreeNode* const camNode = scene->FindCameraNode(m_myCameraIndex);
	alchemediaCamera* const camera = (alchemediaCamera*) scene->GetInfoFromNode (camNode);

	// set the camera view matrix.
	//camera->SetCameraMatrix();
	dVector p0 (camera->ScreenToWorld(dVector (dFloat(point.x), dFloat(point.y), 0.0f, 1.0f)));
	dVector p1 (camera->ScreenToWorld(dVector (dFloat(point.x), dFloat(point.y), 1.0f, 1.0f)));

	alchemediaScene::dTreeNode* const closestSceneNode = scene->RayCast(p0, p1);
	if (closestSceneNode) {
		_ASSERTE (0);
		//explorer->SelectNode (closestSceneNode);
	}
//	mainFrame->UpdateDisplay();
}
