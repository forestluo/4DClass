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
#include "MainFrm.h"
#include "SceneView.h"
#include "Resource.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
///////////////////////////////////////////////////////////////////////////////

#define ITEM_LIGHT											L"光线"
#define ITEM_VIEWPORT										L"视口"
#define ITEM_BACKGROUND										L"背景"
#define ITEM_FOREGROUND										L"前景"
#define ITEM_ENVIRONMENT									L"环境"

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())


///////////////////////////////////////////////////////////////////////////////
//
// CClassViewMenuButton
//
///////////////////////////////////////////////////////////////////////////////

class CSceneViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CSceneView;

	DECLARE_SERIAL(CSceneViewMenuButton)

public:
	CSceneViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CSceneViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSceneView::CSceneView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CSceneView::~CSceneView()
{
}

BEGIN_MESSAGE_MAP(CSceneView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceneView message handlers

int CSceneView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndSceneView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create Class View\n");
		return -1;      // fail to create
	}

	// Load images:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CSceneViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CSceneViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CSceneViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillSceneView();

	return 0;
}

void CSceneView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CSceneView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndSceneView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CSceneView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndSceneView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CSceneView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CSceneView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CSceneViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CSceneViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CSceneView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CSceneView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("Add member function..."));
}

void CSceneView::OnClassAddMemberVariable()
{
	// TODO: Add your command handler code here
}

void CSceneView::OnClassDefinition()
{
	// TODO: Add your command handler code here
}

void CSceneView::OnClassProperties()
{
	// TODO: Add your command handler code here
}

void CSceneView::OnNewFolder()
{
	AfxMessageBox(_T("New Folder..."));
}

void CSceneView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndSceneView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CSceneView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndSceneView.SetFocus();
}

void CSceneView::OnChangeVisualStyle()
{
	m_SceneViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_SceneViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_SceneViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndSceneView.SetImageList(&m_SceneViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* Locked */);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnNotify
//
///////////////////////////////////////////////////////////////////////////////

BOOL CSceneView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	NMHDR* pNMHDR = (NMHDR*)lParam;
#ifdef _DEBUG
	assert(pNMHDR != NULL && MAINFRAME != NULL);
#endif
	//Get document.
	CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();

	//Check result.
	if(pNMHDR->code == TVN_SELCHANGED && pDoc != NULL)
	{
		//Get selected item.
		HTREEITEM hItem = m_wndSceneView.GetSelectedItem();
		//Check result.
		if(hItem != NULL)
		{
			//Get text.
			CString name = m_wndSceneView.GetItemText(hItem);
			//Check name.
			if(name == ITEM_LIGHT)
			{
				//Show properties of light.
			}
			else if(name == ITEM_VIEWPORT)
			{
				//Show properties of view port.
				MAINFRAME->ShowProperties(pDoc->application->getViewPort());
			}
			else if(name == ITEM_ENVIRONMENT)
			{
				//Show properties of environment.
			}
			else
			{
				//Pick object by name.
				CWorldObject* pObject = pDoc->application->pickObject(CNormalString(name.GetBuffer()));
				//Check result.
				if(pObject != NULL && pObject->isRenderableObject())
				{
					//Show properties.
					MAINFRAME->ShowProperties((CD3DXRenderableObject *)pObject->getRenderable());
				}
			}
		}
	}
	//Return result.
	return CDockablePane::OnNotify(wParam, lParam, pResult);
}

///////////////////////////////////////////////////////////////////////////////
//
// UpdateSceneView
//
///////////////////////////////////////////////////////////////////////////////

void CSceneView::UpdateSceneView()
{
	//Delete all items.
	m_wndSceneView.DeleteAllItems();
	//Fill scene view.
	FillSceneView();
}

///////////////////////////////////////////////////////////////////////////////
//
// FillSceneView
//
///////////////////////////////////////////////////////////////////////////////

void CSceneView::FillSceneView()
{
	//Fill environment.
	FillEnvironment();
	//Fill foreground.
	FillForeground();
}

///////////////////////////////////////////////////////////////////////////////
//
// FillEnvironment
//
///////////////////////////////////////////////////////////////////////////////

void CSceneView::FillEnvironment()
{
	//Create environment item.
	HTREEITEM hRootItem = m_wndSceneView.InsertItem(ITEM_ENVIRONMENT,0,0);
#ifdef _DEBUG
	assert(hRootItem != NULL);
#endif
	//Add tree item.
	m_wndSceneView.SetItemState(hRootItem,TVIS_BOLD,TVIS_BOLD);

	//Fill light.
	FillLight(hRootItem);
	//Fill view port.
	FillViewport(hRootItem);
	//Fill background.
	FillBackground(hRootItem);

	//Expand items.
	m_wndSceneView.Expand(hRootItem,TVE_EXPAND);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillLight
//
///////////////////////////////////////////////////////////////////////////////

void CSceneView::FillLight(HTREEITEM hRootItem)
{
#ifdef _DEBUG
	assert(hRootItem != NULL);
#endif
	//Create light.
	HTREEITEM hLightItem = m_wndSceneView.InsertItem(ITEM_LIGHT,1,1,hRootItem);
#ifdef _DEBUG
	assert(hLightItem != NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// FillViewport
//
///////////////////////////////////////////////////////////////////////////////

void CSceneView::FillViewport(HTREEITEM hRootItem)
{
#ifdef _DEBUG
	assert(hRootItem != NULL);
#endif
	//Create view port.
	HTREEITEM hViewPortItem = m_wndSceneView.InsertItem(ITEM_VIEWPORT,1,1,hRootItem);
#ifdef _DEBUG
	assert(hViewPortItem != NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// FillBackground
//
///////////////////////////////////////////////////////////////////////////////

void CSceneView::FillBackground(HTREEITEM hRootItem)
{
#ifdef _DEBUG
	assert(hRootItem != NULL);
#endif
	//Create background.
	HTREEITEM hBackgroundItem = m_wndSceneView.InsertItem(ITEM_BACKGROUND,1,1,hRootItem);
#ifdef _DEBUG
	assert(hBackgroundItem != NULL);
#endif

	//Check result.
	if(MAINFRAME != NULL)
	{
		//Get document.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check background.
		if(pDoc != NULL && pDoc->application != NULL && pDoc->application->getBackground() != NULL)
		{
			//Enumeration.
			CListNodeEnumeration iterator;
			//Get enumeration.
			pDoc->application->getBackground()->getEnumeration(iterator);
			//Do while.
			while(iterator.hasMoreElements())
			{
				//Get object.
				CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
				assert(object != NULL);
#endif
				//Insert items.
				m_wndSceneView.InsertItem(object->getAlias().getCString(),1,1,hBackgroundItem);
			}
		}
	}

	//Expand items.
	m_wndSceneView.Expand(hBackgroundItem,TVE_EXPAND);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillForegroundScene
//
///////////////////////////////////////////////////////////////////////////////

void CSceneView::FillForeground()
{
	//Create object item.
	HTREEITEM hForegroundItem = m_wndSceneView.InsertItem(ITEM_FOREGROUND,0,0);
	//Set item state.
	m_wndSceneView.SetItemState(hForegroundItem,TVIS_BOLD,TVIS_BOLD);

	//Check mainframe.
	if(MAINFRAME != NULL)
	{
		//Get document.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL && pDoc->application->getForeground() != NULL)
		{
			//Enumeration.
			CListNodeEnumeration iterator;
			//Get enumeration.
			pDoc->application->getForeground()->getEnumeration(iterator);
			//Do while.
			while(iterator.hasMoreElements())
			{
				//Get object.
				CWorldObject* childObject = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
				assert(childObject != NULL);
#endif
				//Insert items.
				HTREEITEM hChildItem = m_wndSceneView.InsertItem(childObject->getAlias().getCString(),1,1,hForegroundItem);
				//Check base
				if(childObject->getCount() > 0) FillForeground(childObject,hChildItem);
			}
		}
	}

	//Expand items.
	m_wndSceneView.Expand(hForegroundItem,TVE_EXPAND);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillForeground
//
///////////////////////////////////////////////////////////////////////////////

void CSceneView::FillForeground(CWorldObject* object,HTREEITEM hRootItem)
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(object != NULL && hRootItem != NULL);
#endif

	//Get enumeration.
	object->getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* childObject = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(childObject != NULL);
#endif
		//Insert item.
		HTREEITEM hChildItem = m_wndSceneView.InsertItem(childObject->getAlias().getCString(),1,1,hRootItem);
#ifdef _DEBUG
		assert(hChildItem != NULL);
#endif
		//Check base.
		if(childObject->getCount() > 0) FillForeground(object,hChildItem);
	}

	//Expand items.
	m_wndSceneView.Expand(hRootItem,TVE_EXPAND);
}
