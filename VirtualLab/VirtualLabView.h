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

// VirtualLabView.h : interface of the CVirtualLabView class
//

#pragma once

#include "MainFrm.h"

class CVirtualLabView : public CView
{
protected: // create from serialization only
	CVirtualLabView();
	DECLARE_DYNCREATE(CVirtualLabView)

// Attributes
public:
	CVirtualLabDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CVirtualLabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	//Main frame.
	CMainFrame*						g_pMainFrame;

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	
	////////////////////////////////////////
	//
	//Major functions.
	//
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Interactive functions.
	//
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//
	////////////////////////////////////////

	DECLARE_MESSAGE_MAP()

public:

	////////////////////////////////////////
	//
	//Major overloaded functions.
	//
	virtual void OnInitialUpdate();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//
	////////////////////////////////////////
	
	////////////////////////////////////////
	//
	//Update for the first time.
	//
	afx_msg void OnViewUpdated();
	//
	////////////////////////////////////////

public:

	////////////////////////////////////////
	//
	//Control of simulation.
	//
	afx_msg void OnButtonStart();
	afx_msg void OnUpdateButtonStart(CCmdUI *pCmdUI);
	afx_msg void OnButtonStop();
	afx_msg void OnUpdateButtonStop(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

public:

	////////////////////////////////////////
	//
	//Control of surface.
	//
	afx_msg void OnButtonCircle();
	afx_msg void OnUpdateButtonCircle(CCmdUI *pCmdUI);
	afx_msg void OnButtonGridMesh();
	afx_msg void OnUpdateButtonGridMesh(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

public:

	////////////////////////////////////////
	//
	//Control of slice.
	//
	afx_msg void OnButtonSlice();
	afx_msg void OnUpdateButtonSlice(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonSliceXvertical();
	afx_msg void OnUpdateButtonSliceXvertical(CCmdUI *pCmdUI);
	afx_msg void OnButtonSliceYvertical();
	afx_msg void OnUpdateButtonSliceYvertical(CCmdUI *pCmdUI);
	afx_msg void OnButtonSliceZvertical();
	afx_msg void OnUpdateButtonSliceZvertical(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonBallYvertical();
	afx_msg void OnUpdateButtonBallYvertical(CCmdUI *pCmdUI);
	afx_msg void OnButtonCuboidYvertical();
	afx_msg void OnUpdateButtonCuboidYvertical(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Control of polygon.
	//
	afx_msg void OnButtonSphere();
	afx_msg void OnUpdateButtonSphere(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonCube();
	afx_msg void OnUpdateButtonCube(CCmdUI *pCmdUI);
	afx_msg void OnButtonCuboid();
	afx_msg void OnUpdateButtonCuboid(CCmdUI *pCmdUI);
	afx_msg void OnButtonPolygon();
	afx_msg void OnUpdateButtonPolygon(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Control of cone.
	//
	afx_msg void OnButtonCone0();
	afx_msg void OnUpdateButtonCone0(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonCone3();
	afx_msg void OnUpdateButtonCone3(CCmdUI *pCmdUI);
	afx_msg void OnButtonCone4();
	afx_msg void OnUpdateButtonCone4(CCmdUI *pCmdUI);
	afx_msg void OnButtonCone6();
	afx_msg void OnUpdateButtonCone6(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Control of cylinder.
	//
	afx_msg void OnButtonCylinder0();
	afx_msg void OnUpdateButtonCylinder0(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonCylinder3();
	afx_msg void OnUpdateButtonCylinder3(CCmdUI *pCmdUI);
	afx_msg void OnButtonCylinder5();
	afx_msg void OnUpdateButtonCylinder5(CCmdUI *pCmdUI);
	afx_msg void OnButtonCylinder6();
	afx_msg void OnUpdateButtonCylinder6(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Control of frustum.
	//
	afx_msg void OnButtonFrustum0();
	afx_msg void OnUpdateButtonFrustum0(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonFrustum3();
	afx_msg void OnUpdateButtonFrustum3(CCmdUI *pCmdUI);
	afx_msg void OnButtonFrustum4();
	afx_msg void OnUpdateButtonFrustum4(CCmdUI *pCmdUI);
	afx_msg void OnButtonFrustum6();
	afx_msg void OnUpdateButtonFrustum6(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Control of other primitive.
	//
	afx_msg void OnButtonHemisphere();
	afx_msg void OnUpdateButtonHemisphere(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonCapsule();
	afx_msg void OnUpdateButtonCapsule(CCmdUI *pCmdUI);
	afx_msg void OnButtonChamferCylinder();
	afx_msg void OnUpdateButtonChamferCylinder(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Control of compound.
	//
	afx_msg void OnButtonCompoundAxis();
	afx_msg void OnUpdateButtonCompoundAxis(CCmdUI *pCmdUI);
	afx_msg void OnButtonCompoundCross();
	afx_msg void OnUpdateButtonCompoundCross(CCmdUI *pCmdUI);
	afx_msg void OnButtonCompoundBox();
	afx_msg void OnUpdateButtonCompoundBox(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

public:

	////////////////////////////////////////
	//
	//Control of joint.
	//
	afx_msg void OnButtonJointUpvector();
	afx_msg void OnUpdateButtonJointUpvector(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonJointCorkscrew1();
	afx_msg void OnUpdateButtonJointCorkscrew1(CCmdUI *pCmdUI);
	afx_msg void OnButtonJointCorkscrew2();
	afx_msg void OnUpdateButtonJointCorkscrew2(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonJointBall1();
	afx_msg void OnUpdateButtonJointBall1(CCmdUI *pCmdUI);
	afx_msg void OnButtonJointBall2();
	afx_msg void OnUpdateButtonJointBall2(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonJointHinge1();
	afx_msg void OnUpdateButtonJointHinge1(CCmdUI *pCmdUI);
	afx_msg void OnButtonJointHinge2();
	afx_msg void OnUpdateButtonJointHinge2(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonJointSlider1();
	afx_msg void OnUpdateButtonJointSlider1(CCmdUI *pCmdUI);
	afx_msg void OnButtonJointSlider2();
	afx_msg void OnUpdateButtonJointSlider2(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonJointUniversal1();
	afx_msg void OnUpdateButtonJointUniversal1(CCmdUI *pCmdUI);
	afx_msg void OnButtonJointUniversal2();
	afx_msg void OnUpdateButtonJointUniversal2(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonJointBall3();
	afx_msg void OnUpdateButtonJointBall3(CCmdUI *pCmdUI);
	afx_msg void OnButtonJointHinge3();
	afx_msg void OnUpdateButtonJointHinge3(CCmdUI *pCmdUI);
	afx_msg void OnButtonJointSlider3();
	afx_msg void OnUpdateButtonJointSlider3(CCmdUI *pCmdUI);
	afx_msg void OnButtonJoint6dof();
	afx_msg void OnUpdateButtonJoint6dof(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

public:

	////////////////////////////////////////
	//
	//Control of Input.
	//
	afx_msg void OnButtonPseyeOpen();
	afx_msg void OnUpdateButtonPseyeOpen(CCmdUI *pCmdUI);
	afx_msg void OnButtonPseyeClose();
	afx_msg void OnUpdateButtonPseyeClose(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonHaarDetector();
	afx_msg void OnUpdateButtonHaarDetector(CCmdUI *pCmdUI);
	afx_msg void OnButtonFilterClose();
	afx_msg void OnUpdateButtonFilterClose(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonImageTexture();
	afx_msg void OnUpdateButtonImageTexture(CCmdUI *pCmdUI);
	afx_msg void OnButtonTextureClose();
	afx_msg void OnUpdateButtonTextureClose(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonKinectOpen();
	afx_msg void OnUpdateButtonKinectOpen(CCmdUI *pCmdUI);
	afx_msg void OnButtonKinectClose();
	afx_msg void OnUpdateButtonKinectClose(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonDepthFilter();
	afx_msg void OnUpdateButtonDepthFilter(CCmdUI *pCmdUI);
	//
	afx_msg void OnButtonGroundMesh();
	afx_msg void OnUpdateButtonGroundMesh(CCmdUI *pCmdUI);
	afx_msg void OnButtonControlledBall();
	afx_msg void OnUpdateButtonControlledBall(CCmdUI *pCmdUI);
	afx_msg void OnButtonControlledItem();
	afx_msg void OnUpdateButtonControlledItem(CCmdUI *pCmdUI);
	afx_msg void OnButtonKinematicItem();
	afx_msg void OnUpdateButtonKinematicItem(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////

public:

	////////////////////////////////////////
	//
	// Control of view port.
	//
	afx_msg void OnButtonViewXz();
	afx_msg void OnUpdateButtonViewXz(CCmdUI *pCmdUI);
	afx_msg void OnButtonViewXy();
	afx_msg void OnUpdateButtonViewXy(CCmdUI *pCmdUI);
	afx_msg void OnButtonViewYz();
	afx_msg void OnUpdateButtonViewYz(CCmdUI *pCmdUI);
	//
	////////////////////////////////////////
};

#ifndef _DEBUG  // debug version in VirtualLabView.cpp
inline CVirtualLabDoc* CVirtualLabView::GetDocument() const
   { return reinterpret_cast<CVirtualLabDoc*>(m_pDocument); }
#endif

