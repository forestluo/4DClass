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

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "4DProperties.h"

#include "VirtualLab.h"
#include "VirtualLabDoc.h"

#include "D3DXFileMesh.h"
#include "D3DXPrimitive.h"

#include "D3DXScene.h"
#include "D3DXRenderableObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
///////////////////////////////////////////////////////////////////////////////

#define MFC_COMBO_BOX_ID									1

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	//Current selected property page.
	nSelectedPropertyPage = -1;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	//Change property page.
	ON_CBN_SELENDOK(MFC_COMBO_BOX_ID,OnSelendokCombo)
	//On property value changed.
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create combo:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, MFC_COMBO_BOX_ID))
	{
		TRACE0("Failed to create Properties Combo \n");
		return -1;      // fail to create
	}

	m_wndObjectCombo.AddString(_T("Application"));
	m_wndObjectCombo.AddString(_T("Properties Window"));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

///////////////////////////////////////////////////////////////////////////////
//
// EnableProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::EnableProperties(BOOL bEnable)
{
	//Enable properties.
	m_wndPropList.EnableWindow(bEnable);
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearHandles
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ClearHandles()
{
	//Check properties. 
	for(int i = 0;i < sizeof(g_pPropHandles) / sizeof(CMFCPropertyGridProperty*);i ++) g_pPropHandles[i] = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// OnSelchangeCombo
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::OnSelendokCombo()
{
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL)
		{
			//Get object.
			CD3DXObject* object = pDoc->application->getFocused();
			//Check current.
			if(object != NULL)
			{
				//Get select text.
				int nSelected = m_wndObjectCombo.GetCurSel();
				//Check object.
				if(IS_FILEMESH_BASE(object))
				{
					//Change property page.
					ChangePropertyPage((CD3DXFileMesh *)object,nSelected);
				}
				else if(IS_PRIMITIVE_BASE(object))
				{
					//Change property page.
					ChangePropertyPage((CD3DXPrimitive *)object,nSelected);
				}
				else if(IS_RENDERABLEOBJECT_BASE(object))
				{
					//Change property page.
					ChangePropertyPage((CD3DXRenderableObject *)object,nSelected);
				}
				//Set selected.
				nSelectedPropertyPage = nSelected;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// OnPropertyChanged
//
///////////////////////////////////////////////////////////////////////////////

LRESULT CPropertiesWnd::OnPropertyChanged( WPARAM wParam, LPARAM lParam )
{
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL)
		{
			//Get object.
			CD3DXObject* object = pDoc->application->getFocused();
			//Check current object.
			if(object != NULL)
			{
				//Get property.
				CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty *)lParam;
#ifdef _DEBUG
				assert(pProp != NULL);
#endif
				//Check type.
				if(IS_SCENE_BASE(object))
				{

				}
				else if(IS_VIEWPORT_BASE(object))
				{
					//On property changed.
					OnPropertyChanged((CViewPort *)object,pProp);
				}
				else if(IS_DEVICE_BASE(object))
				{
					//On property changed.
					OnPropertyChanged((CD3DXDevice *)object,pProp);
				}
				else if(IS_FILTER_BASE(object))
				{
					//On property changed.
					OnPropertyChanged((CD3DXFilter *)object,pProp);
				}
				else if(IS_RENDERABLEOBJECT_BASE(object))
				{
					//Check selection.
					if(nSelectedPropertyPage == PROPERTY_GENERAL_SELECTION)
					{
						//On property changed.
						OnPropertyChanged((CD3DXRenderableObject *)object,pProp);
					}
					else if(nSelectedPropertyPage == PROPERTY_RENDER_SELECTION)
					{
						//On property changed.
						OnRenderPropertyChanged((CD3DXRenderableObject *)object,pProp);
					}
					else if(nSelectedPropertyPage == PROPERTY_JOINT_SELECTION)
					{
						//Check type.
						if(((CD3DXRenderableObject *)object)->isJointObject()
							&& ((CD3DXRenderableObject *)object)->isPhysicsObject())
						{
							//Get physics object.
							CPhysicsObject* physicsObject = (CPhysicsObject *)((CD3DXRenderableObject *)object)->getPhysics();
#ifdef _DEBUG
							assert(physicsObject != NULL);
#endif
							//On property changed.
							OnJointPropertyChanged((CPhysicsJointObject*)physicsObject,pProp);
						}
					}
				}
			}
		}
	}
	//Return result.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// UpdateProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::UpdateProperties()
{
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL)
		{
			//Get object.
			CD3DXObject* object = pDoc->application->getFocused();
			//Check result.
			if(object != NULL)
			{
				//Check type.
				if(IS_SCENE_BASE(object))
				{
					//Do nothing.
				}
				else if(IS_VIEWPORT_BASE(object))
				{
					//Change properties.
					ChangeProperties((CViewPort *)object);
				}
				else if(IS_RENDERABLEOBJECT_BASE(object))
				{
					//Check selection.
					if(nSelectedPropertyPage == PROPERTY_GENERAL_SELECTION)
					{
						//Change properties.
						ChangeProperties((CD3DXRenderableObject *)object);
					}
					else if(nSelectedPropertyPage == PROPERTY_PHYSICS_SELECTION)
					{
						//Get physics object.
						_OBJECT physicsObject = ((CD3DXRenderableObject *)object)->getPhysics();
#ifdef _DEBUG
						assert(physicsObject != NULL);
#endif
						//Change properties.
						ChangePhysicsProperties((CPhysicsObject *)physicsObject);
					}
					else if(nSelectedPropertyPage == PROPERTY_PHYSICS_FORCE_SELECTION)
					{
						//Get physics object.
						_OBJECT physicsObject = ((CD3DXRenderableObject *)object)->getPhysics();
#ifdef _DEBUG
						assert(physicsObject != NULL);
#endif
						//Change properties.
						ChangePhysicsForceProperties((CPhysicsObject *)physicsObject);
					}
					else if(nSelectedPropertyPage == PROPERTY_JOINT_SELECTION)
					{
						//Get physics object.
						_OBJECT physicsObject = ((CD3DXRenderableObject *)object)->getPhysics();
#ifdef _DEBUG
						assert(physicsObject != NULL);
#endif
						if(((CD3DXRenderableObject *)object)->isJointObject())
						{
							//Change properties.
							ChangeJointProperties((CPhysicsJointObject *)physicsObject);
						}
					}
					else if(nSelectedPropertyPage == PROPERTY_JOINT_FORCE_SELECTION)
					{
						//Get physics object.
						_OBJECT physicsObject = ((CD3DXRenderableObject *)object)->getPhysics();
#ifdef _DEBUG
						assert(physicsObject != NULL);
#endif
						if(((CD3DXRenderableObject *)object)->isJointObject())
						{
							//Change properties.
							ChangeJointForceProperties((CPhysicsJointObject *)physicsObject);
						}
					}
				}
			}
		}
	}
}
