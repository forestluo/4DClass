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

// VirtualLabView.cpp : implementation of the CVirtualLabView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVirtualLabView

IMPLEMENT_DYNCREATE(CVirtualLabView, CView)

BEGIN_MESSAGE_MAP(CVirtualLabView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVirtualLabView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	
	//Important functions.
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//Interactive functions.
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEHWHEEL()
	//Simulation
	ON_COMMAND(IDT_VIEW_UPDATER, &CVirtualLabView::OnViewUpdated)
	ON_COMMAND(ID_BUTTON_START, &CVirtualLabView::OnButtonStart)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_START, &CVirtualLabView::OnUpdateButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CVirtualLabView::OnButtonStop)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_STOP, &CVirtualLabView::OnUpdateButtonStop)
	//Surface
	ON_COMMAND(ID_BUTTON_CIRCLE, &CVirtualLabView::OnButtonCircle)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CIRCLE, &CVirtualLabView::OnUpdateButtonCircle)
	ON_COMMAND(ID_BUTTON_GRID_MESH, &CVirtualLabView::OnButtonGridMesh)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_GRID_MESH, &CVirtualLabView::OnUpdateButtonGridMesh)
	//Slice
	ON_COMMAND(ID_BUTTON_SLICE, &CVirtualLabView::OnButtonSlice)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SLICE, &CVirtualLabView::OnUpdateButtonSlice)
	ON_COMMAND(ID_BUTTON_SLICE_YVERTICAL, &CVirtualLabView::OnButtonSliceYvertical)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SLICE_YVERTICAL, &CVirtualLabView::OnUpdateButtonSliceYvertical)
	ON_COMMAND(ID_BUTTON_SLICE_ZVERTICAL, &CVirtualLabView::OnButtonSliceZvertical)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SLICE_ZVERTICAL, &CVirtualLabView::OnUpdateButtonSliceZvertical)
	ON_COMMAND(ID_BUTTON_SLICE_XVERTICAL, &CVirtualLabView::OnButtonSliceXvertical)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SLICE_XVERTICAL, &CVirtualLabView::OnUpdateButtonSliceXvertical)
	ON_COMMAND(ID_BUTTON_BALL_YVERTICAL, &CVirtualLabView::OnButtonBallYvertical)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_BALL_YVERTICAL, &CVirtualLabView::OnUpdateButtonBallYvertical)
	ON_COMMAND(ID_BUTTON_CUBOID_YVERTICAL, &CVirtualLabView::OnButtonCuboidYvertical)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CUBOID_YVERTICAL, &CVirtualLabView::OnUpdateButtonCuboidYvertical)
	//Polygon
	ON_COMMAND(ID_BUTTON_SPHERE, &CVirtualLabView::OnButtonSphere)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SPHERE, &CVirtualLabView::OnUpdateButtonSphere)
	ON_COMMAND(ID_BUTTON_CUBE, &CVirtualLabView::OnButtonCube)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CUBE, &CVirtualLabView::OnUpdateButtonCube)
	ON_COMMAND(ID_BUTTON_CUBOID, &CVirtualLabView::OnButtonCuboid)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CUBOID, &CVirtualLabView::OnUpdateButtonCuboid)
	ON_COMMAND(ID_BUTTON_POLYGON, &CVirtualLabView::OnButtonPolygon)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_POLYGON, &CVirtualLabView::OnUpdateButtonPolygon)
	//Cone
	ON_COMMAND(ID_BUTTON_CONE0, &CVirtualLabView::OnButtonCone0)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONE0, &CVirtualLabView::OnUpdateButtonCone0)
	ON_COMMAND(ID_BUTTON_CONE3, &CVirtualLabView::OnButtonCone3)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONE3, &CVirtualLabView::OnUpdateButtonCone3)
	ON_COMMAND(ID_BUTTON_CONE4, &CVirtualLabView::OnButtonCone4)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONE4, &CVirtualLabView::OnUpdateButtonCone4)
	ON_COMMAND(ID_BUTTON_CONE6, &CVirtualLabView::OnButtonCone6)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONE6, &CVirtualLabView::OnUpdateButtonCone6)
	//Cylinder
	ON_COMMAND(ID_BUTTON_CYLINDER0, &CVirtualLabView::OnButtonCylinder0)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CYLINDER0, &CVirtualLabView::OnUpdateButtonCylinder0)
	ON_COMMAND(ID_BUTTON_CYLINDER3, &CVirtualLabView::OnButtonCylinder3)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CYLINDER3, &CVirtualLabView::OnUpdateButtonCylinder3)
	ON_COMMAND(ID_BUTTON_CYLINDER5, &CVirtualLabView::OnButtonCylinder5)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CYLINDER5, &CVirtualLabView::OnUpdateButtonCylinder5)
	ON_COMMAND(ID_BUTTON_CYLINDER6, &CVirtualLabView::OnButtonCylinder6)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CYLINDER6, &CVirtualLabView::OnUpdateButtonCylinder6)
	//Frustum
	ON_COMMAND(ID_BUTTON_FRUSTUM0, &CVirtualLabView::OnButtonFrustum0)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FRUSTUM0, &CVirtualLabView::OnUpdateButtonFrustum0)
	ON_COMMAND(ID_BUTTON_FRUSTUM3, &CVirtualLabView::OnButtonFrustum3)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FRUSTUM3, &CVirtualLabView::OnUpdateButtonFrustum3)
	ON_COMMAND(ID_BUTTON_FRUSTUM4, &CVirtualLabView::OnButtonFrustum4)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FRUSTUM4, &CVirtualLabView::OnUpdateButtonFrustum4)
	ON_COMMAND(ID_BUTTON_FRUSTUM6, &CVirtualLabView::OnButtonFrustum6)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FRUSTUM6, &CVirtualLabView::OnUpdateButtonFrustum6)
	//Other primitive
	ON_COMMAND(ID_BUTTON_HEMISPHERE, &CVirtualLabView::OnButtonHemisphere)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_HEMISPHERE, &CVirtualLabView::OnUpdateButtonHemisphere)
	ON_COMMAND(ID_BUTTON_CAPSULE, &CVirtualLabView::OnButtonCapsule)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CAPSULE, &CVirtualLabView::OnUpdateButtonCapsule)
	ON_COMMAND(ID_BUTTON_CHAMFER_CYLINDER, &CVirtualLabView::OnButtonChamferCylinder)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CHAMFER_CYLINDER, &CVirtualLabView::OnUpdateButtonChamferCylinder)
	//Compound
	ON_COMMAND(ID_BUTTON_COMPOUND_AXIS, &CVirtualLabView::OnButtonCompoundAxis)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_COMPOUND_AXIS, &CVirtualLabView::OnUpdateButtonCompoundAxis)
	ON_COMMAND(ID_BUTTON_COMPOUND_CROSS, &CVirtualLabView::OnButtonCompoundCross)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_COMPOUND_CROSS, &CVirtualLabView::OnUpdateButtonCompoundCross)
	//Joint
	ON_COMMAND(ID_BUTTON_JOINT_UPVECTOR, &CVirtualLabView::OnButtonJointUpvector)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_UPVECTOR, &CVirtualLabView::OnUpdateButtonJointUpvector)
	ON_COMMAND(ID_BUTTON_JOINT_CORKSCREW1, &CVirtualLabView::OnButtonJointCorkscrew1)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_CORKSCREW1, &CVirtualLabView::OnUpdateButtonJointCorkscrew1)
	ON_COMMAND(ID_BUTTON_JOINT_CORKSCREW2, &CVirtualLabView::OnButtonJointCorkscrew2)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_CORKSCREW2, &CVirtualLabView::OnUpdateButtonJointCorkscrew2)
	ON_COMMAND(ID_BUTTON_JOINT_BALL1, &CVirtualLabView::OnButtonJointBall1)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_BALL1, &CVirtualLabView::OnUpdateButtonJointBall1)
	ON_COMMAND(ID_BUTTON_JOINT_BALL2, &CVirtualLabView::OnButtonJointBall2)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_BALL2, &CVirtualLabView::OnUpdateButtonJointBall2)
	ON_COMMAND(ID_BUTTON_JOINT_HINGE1, &CVirtualLabView::OnButtonJointHinge1)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_HINGE1, &CVirtualLabView::OnUpdateButtonJointHinge1)
	ON_COMMAND(ID_BUTTON_JOINT_HINGE2, &CVirtualLabView::OnButtonJointHinge2)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_HINGE2, &CVirtualLabView::OnUpdateButtonJointHinge2)
	ON_COMMAND(ID_BUTTON_JOINT_SLIDER1, &CVirtualLabView::OnButtonJointSlider1)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_SLIDER1, &CVirtualLabView::OnUpdateButtonJointSlider1)
	ON_COMMAND(ID_BUTTON_JOINT_SLIDER2, &CVirtualLabView::OnButtonJointSlider2)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_SLIDER2, &CVirtualLabView::OnUpdateButtonJointSlider2)
	ON_COMMAND(ID_BUTTON_JOINT_UNIVERSAL1, &CVirtualLabView::OnButtonJointUniversal1)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_UNIVERSAL1, &CVirtualLabView::OnUpdateButtonJointUniversal1)
	ON_COMMAND(ID_BUTTON_JOINT_UNIVERSAL2, &CVirtualLabView::OnButtonJointUniversal2)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_UNIVERSAL2, &CVirtualLabView::OnUpdateButtonJointUniversal2)
	ON_COMMAND(ID_BUTTON_JOINT_BALL3, &CVirtualLabView::OnButtonJointBall3)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_BALL3, &CVirtualLabView::OnUpdateButtonJointBall3)
	ON_COMMAND(ID_BUTTON_JOINT_HINGE3, &CVirtualLabView::OnButtonJointHinge3)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_HINGE3, &CVirtualLabView::OnUpdateButtonJointHinge3)
	ON_COMMAND(ID_BUTTON_JOINT_SLIDER3, &CVirtualLabView::OnButtonJointSlider3)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_SLIDER3, &CVirtualLabView::OnUpdateButtonJointSlider3)
	ON_COMMAND(ID_BUTTON_JOINT_6DOF, &CVirtualLabView::OnButtonJoint6dof)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_JOINT_6DOF, &CVirtualLabView::OnUpdateButtonJoint6dof)
	ON_COMMAND(ID_BUTTON_COMPOUND_BOX, &CVirtualLabView::OnButtonCompoundBox)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_COMPOUND_BOX, &CVirtualLabView::OnUpdateButtonCompoundBox)
	//PSEye
	ON_COMMAND(ID_BUTTON_PSEYE_OPEN, &CVirtualLabView::OnButtonPseyeOpen)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PSEYE_OPEN, &CVirtualLabView::OnUpdateButtonPseyeOpen)
	ON_COMMAND(ID_BUTTON_PSEYE_CLOSE, &CVirtualLabView::OnButtonPseyeClose)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PSEYE_CLOSE, &CVirtualLabView::OnUpdateButtonPseyeClose)
	//Filter
	ON_COMMAND(ID_BUTTON_HAAR_DETECTOR, &CVirtualLabView::OnButtonHaarDetector)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_HAAR_DETECTOR, &CVirtualLabView::OnUpdateButtonHaarDetector)
	ON_COMMAND(ID_BUTTON_DEPTH_FILTER, &CVirtualLabView::OnButtonDepthFilter)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DEPTH_FILTER, &CVirtualLabView::OnUpdateButtonDepthFilter)
	ON_COMMAND(ID_BUTTON_FILTER_CLOSE, &CVirtualLabView::OnButtonFilterClose)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FILTER_CLOSE, &CVirtualLabView::OnUpdateButtonFilterClose)
	//Dynamic Texture
	ON_COMMAND(ID_BUTTON_IMAGE_TEXTURE, &CVirtualLabView::OnButtonImageTexture)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_IMAGE_TEXTURE, &CVirtualLabView::OnUpdateButtonImageTexture)
	ON_COMMAND(ID_BUTTON_TEXTURE_CLOSE, &CVirtualLabView::OnButtonTextureClose)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TEXTURE_CLOSE, &CVirtualLabView::OnUpdateButtonTextureClose)
	//Kinect
	ON_COMMAND(ID_BUTTON_KINECT_OPEN, &CVirtualLabView::OnButtonKinectOpen)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_KINECT_OPEN, &CVirtualLabView::OnUpdateButtonKinectOpen)
	ON_COMMAND(ID_BUTTON_KINECT_CLOSE, &CVirtualLabView::OnButtonKinectClose)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_KINECT_CLOSE, &CVirtualLabView::OnUpdateButtonKinectClose)
	//Dynamics
	ON_COMMAND(ID_BUTTON_GROUND_MESH, &CVirtualLabView::OnButtonGroundMesh)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_GROUND_MESH, &CVirtualLabView::OnUpdateButtonGroundMesh)
	ON_COMMAND(ID_BUTTON_CONTROLLED_BALL, &CVirtualLabView::OnButtonControlledBall)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONTROLLED_BALL, &CVirtualLabView::OnUpdateButtonControlledBall)
	ON_COMMAND(ID_BUTTON_CONTROLLED_ITEM, &CVirtualLabView::OnButtonControlledItem)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONTROLLED_ITEM, &CVirtualLabView::OnUpdateButtonControlledItem)
	ON_COMMAND(ID_BUTTON_KINEMATIC_ITEM, &CVirtualLabView::OnButtonKinematicItem)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_KINEMATIC_ITEM, &CVirtualLabView::OnUpdateButtonKinematicItem)
	//ViewPort
	ON_COMMAND(ID_BUTTON_VIEW_XZ, &CVirtualLabView::OnButtonViewXz)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_VIEW_XZ, &CVirtualLabView::OnUpdateButtonViewXz)
	ON_COMMAND(ID_BUTTON_VIEW_XY, &CVirtualLabView::OnButtonViewXy)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_VIEW_XY, &CVirtualLabView::OnUpdateButtonViewXy)
	ON_COMMAND(ID_BUTTON_VIEW_YZ, &CVirtualLabView::OnButtonViewYz)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_VIEW_YZ, &CVirtualLabView::OnUpdateButtonViewYz)
	END_MESSAGE_MAP()

// CVirtualLabView construction/destruction

CVirtualLabView::CVirtualLabView()
{
	//Set default value.
	g_pMainFrame = NULL;
}

CVirtualLabView::~CVirtualLabView()
{
	//Clear value.
	g_pMainFrame = NULL;
}

BOOL CVirtualLabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVirtualLabView drawing

void CVirtualLabView::OnDraw(CDC* /*pDC*/)
{
	CVirtualLabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CVirtualLabView printing


void CVirtualLabView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CVirtualLabView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVirtualLabView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVirtualLabView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVirtualLabView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CVirtualLabView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVirtualLabView diagnostics

#ifdef _DEBUG
void CVirtualLabView::AssertValid() const
{
	CView::AssertValid();
}

void CVirtualLabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVirtualLabDoc* CVirtualLabView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVirtualLabDoc)));
	return (CVirtualLabDoc*)m_pDocument;
}
#endif //_DEBUG


// CVirtualLabView message handlers

void CVirtualLabView::OnDestroy()
{
	CVirtualLabDoc* pDoc = GetDocument();
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

void CVirtualLabView::OnInitialUpdate()
{
	//On initial update.
	__super::OnInitialUpdate();

	CVirtualLabDoc* pDoc = GetDocument();
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

			//Update scene view.
			if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();

			//Switch to default.
			CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
			assert(pDoc != NULL);
#endif
			//Check result.
			if(pDoc->application != NULL && pDoc->application->getViewPort() != NULL)
			{
				//Update view port.
				if(g_pMainFrame != NULL)
				{
					//Show properties.
					g_pMainFrame->ShowProperties(pDoc->application->getViewPort());
				}
			}
		}
		else
		{
			//Initialize D3DX.
			if(FAILED(pDoc->application->initialize(GetSafeHwnd()))) PostQuitMessage(1);
		}
	}
	//Enable properties.
	if(g_pMainFrame != NULL) g_pMainFrame->EnableProperties(TRUE);
}

BOOL CVirtualLabView::OnEraseBkgnd(CDC* pDC)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Return directly.
	return pDoc->application != NULL ? TRUE : __super::OnEraseBkgnd(pDC);
}

void CVirtualLabView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	CVirtualLabDoc* pDoc = GetDocument();
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

LRESULT CVirtualLabView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	//Get document.
	CVirtualLabDoc* pDoc =(CVirtualLabDoc*)m_pDocument;
	// TODO: Add your specialized code here and/or call the base class
	if(pDoc != NULL && pDoc->application != NULL && pDoc->application->CXD3D::IsActive())
	{
		//Handle mouse messages.
		if(pDoc->application->handleMouseMessage(message,wParam,lParam)) return FALSE;
	}
	//Return result.
	return __super::WindowProc(message, wParam, lParam);
}

void CVirtualLabView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CVirtualLabDoc* pDoc = GetDocument();
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

void CVirtualLabView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CVirtualLabDoc* pDoc = GetDocument();
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


void CVirtualLabView::OnButtonStart()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	pDoc->application->CD3DXApplication::startup();
	//Enable properties.
	if(g_pMainFrame != NULL) g_pMainFrame->EnableProperties(FALSE);
}


void CVirtualLabView::OnUpdateButtonStart(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonStop()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	pDoc->application->CD3DXApplication::shutdown();
	//Enable properties.
	if(g_pMainFrame != NULL) g_pMainFrame->EnableProperties(TRUE);
}

void CVirtualLabView::OnUpdateButtonStop(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && pDoc->application->CPhysicsApplication::isRunning());
}

void CVirtualLabView::OnViewUpdated()
{
	//Check main frame.
	if(g_pMainFrame == NULL)
	{
		//Get main frame.
		g_pMainFrame = (CMainFrame *)GetTopLevelFrame();
		//Check result.
		if(g_pMainFrame != NULL)
		{
			//Update scene view.
			g_pMainFrame->UpdateSceneView();
			//Update resource view.
			g_pMainFrame->UpdateResourceView();

			CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
			assert(pDoc != NULL);
#endif
			//Check result.
			if(pDoc->application != NULL && pDoc->application->getViewPort() != NULL)
			{
				//Show properties.
				g_pMainFrame->ShowProperties(pDoc->application->getViewPort());
			}
		}
	}
}

void CVirtualLabView::OnMouseMove(UINT nFlags, CPoint point)
{
	__super::OnMouseMove(nFlags, point);

	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check application.
	if(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning())
	{
		//Check main frame.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdatePropertyView();
	}
}

void CVirtualLabView::OnLButtonDown(UINT nFlags, CPoint point)
{
	__super::OnLButtonDown(nFlags, point);

	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check application.
	if(pDoc->application != NULL && pDoc->application->getForeground() != NULL)
	{
		//Get picked object.
		CWorldObject* pObject = pDoc->application->getForeground()->getPickedObject();
		//Check result.
		if(pObject != NULL && pObject->isRenderableObject())
		{
			//Get renderable object.
			_OBJECT renderableObject = pObject->getRenderable();
#ifdef _DEBUG
			assert(renderableObject != NULL);
#endif
			//Show properties of renderable object.
			if(g_pMainFrame != NULL) g_pMainFrame->ShowProperties((CD3DXRenderableObject*)renderableObject);
		}
	}
}

void CVirtualLabView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	// TODO: Add your message handler code here and/or call default
	__super::OnMouseHWheel(nFlags, zDelta, pt);

	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check application.
	if(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning())
	{
		//Check main frame.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdatePropertyView();
	}
}
