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
#include "mainfrm.h"
#include "ResourceView.h"
#include "Resource.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"

#include "D3DXDevice.h"
#include "D3DXFilter.h"
#include "D3DXTexture.h"
#include "D3DXFileMesh.h"
#include "ResourceManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
//
//Definitions
//
/////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

/////////////////////////////////////////////////////////////////////////////
// CResourceView

CResourceView::CResourceView()
{
}

CResourceView::~CResourceView()
{
}

BEGIN_MESSAGE_MAP(CResourceView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CResourceView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndResourceView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Failed to create file view\n");
		return -1;      // fail to create
	}

	// Load view images:
	m_ResourceViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndResourceView.SetImageList(&m_ResourceViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillResourceView();
	AdjustLayout();

	return 0;
}

void CResourceView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CResourceView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndResourceView;
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
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CResourceView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndResourceView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CResourceView::OnProperties()
{
	//Check mainframe.
	if(MAINFRAME != NULL)
	{
		//Get active doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL)
		{
			//Get current selected item.
			HTREEITEM hItem = m_wndResourceView.GetSelectedItem();
			//Check result.
			if(hItem != NULL)
			{
				//Get name.
				CString name = m_wndResourceView.GetItemText(hItem);
				//Get resource.
				CD3DXResource* pResource = pDoc->application->getResource(CNormalString(name.GetBuffer()));
				//Check result.
				if(pResource != NULL) MAINFRAME->ShowProperties(pResource);
			}
		}
	}
}

void CResourceView::OnFileOpen()
{
	// TODO: Add your command handler code here
}

void CResourceView::OnFileOpenWith()
{
	// TODO: Add your command handler code here
}

void CResourceView::OnDummyCompile()
{
	// TODO: Add your command handler code here
}

void CResourceView::OnEditCut()
{
	// TODO: Add your command handler code here
}

void CResourceView::OnEditCopy()
{
	// TODO: Add your command handler code here
}

void CResourceView::OnEditClear()
{
	// TODO: Add your command handler code here
}

void CResourceView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndResourceView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CResourceView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndResourceView.SetFocus();
}

void CResourceView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	m_ResourceViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

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

	m_ResourceViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ResourceViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndResourceView.SetImageList(&m_ResourceViewImages, TVSIL_NORMAL);
}

///////////////////////////////////////////////////////////////////////////////
//
// UpdateResourceView
//
///////////////////////////////////////////////////////////////////////////////

void CResourceView::UpdateResourceView()
{
	//Delete all items.
	m_wndResourceView.DeleteAllItems();
	//Fill resource view.
	FillResourceView();
}

///////////////////////////////////////////////////////////////////////////////
//
// FillResourceView
//
///////////////////////////////////////////////////////////////////////////////

void CResourceView::FillResourceView()
{
	//Fill devices.
	FillDevices();
	//Fill filters.
	FillFilters();
	//
	//Fill effect files.
	FillEffectFiles();
	//Fill texture files.
	FillTextureFiles();
	//Fill renderable files.
	FillRenderableFiles();
}

///////////////////////////////////////////////////////////////////////////////
//
// FillDevices
//
///////////////////////////////////////////////////////////////////////////////

void CResourceView::FillDevices()
{
	//Insert item.
	HTREEITEM hTreeRoot = m_wndResourceView.InsertItem(L"输入设备",0,0);
	//Set item state.
	m_wndResourceView.SetItemState(hTreeRoot,TVIS_BOLD,TVIS_BOLD);

	//Check mainframe.
	if(MAINFRAME != NULL)
	{
		//Get active doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL && pDoc->application->getResourceManager() != NULL)
		{
			//Lock.
			pDoc->application->openLock();
			{
				//Enumeration.
				CListNodeEnumeration iterator;
				//Get enumeration.
				pDoc->application->getResourceManager()->getEnumeration(CResourceManager::deviceManager,iterator);
				//Do while.
				while(iterator.hasMoreElements())
				{
					//Get resource.
					CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
					assert(resource != _NULL);
#endif
					//Check type.
					if(IS_DEVICE_BASE(resource) && !resource->isReserved())
					{
						//Insert item.
						m_wndResourceView.InsertItem(resource->getName().getCString(),1,1,hTreeRoot);
					}
				}
			}
			//Close lock.
			pDoc->application->closeLock();
		}
	}
	//Expand it.
	m_wndResourceView.Expand(hTreeRoot,TVE_EXPAND);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillFilters
//
///////////////////////////////////////////////////////////////////////////////

void CResourceView::FillFilters()
{
	//Insert item.
	HTREEITEM hTreeRoot = m_wndResourceView.InsertItem(L"过滤设备",0,0);
	//Set item state.
	m_wndResourceView.SetItemState(hTreeRoot,TVIS_BOLD,TVIS_BOLD);

	//Check mainframe.
	if(MAINFRAME != NULL)
	{
		//Get active doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL && pDoc->application->getResourceManager() != NULL)
		{
			//Open lock.
			pDoc->application->openLock();
			{
				//Enumeration.
				CListNodeEnumeration iterator;
				//Get enumeration.
				pDoc->application->getResourceManager()->getEnumeration(CResourceManager::filterManager,iterator);
				//Do while.
				while(iterator.hasMoreElements())
				{
					//Get resource.
					CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
					assert(resource != _NULL);
#endif
					//Check type.
					if(IS_FILTER_BASE(resource) && !resource->isReserved())
					{
						//Insert item.
						m_wndResourceView.InsertItem(resource->getName().getCString(),1,1,hTreeRoot);
					}
				}
			}
			//Close lock.
			pDoc->application->closeLock();
		}
	}
	//Expand it.
	m_wndResourceView.Expand(hTreeRoot,TVE_EXPAND);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillEffectFiles
//
///////////////////////////////////////////////////////////////////////////////

void CResourceView::FillEffectFiles()
{
	//Insert item.
	HTREEITEM hTreeRoot = m_wndResourceView.InsertItem(L"特效文件",0,0);
	//Set item state.
	m_wndResourceView.SetItemState(hTreeRoot,TVIS_BOLD,TVIS_BOLD);

	//Check mainframe.
	if(MAINFRAME != NULL)
	{
		//Get active doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL && pDoc->application->getResourceManager() != NULL)
		{
			//Open lock.
			pDoc->application->openLock();
			{
				//Enumeration.
				CListNodeEnumeration iterator;
				//Get enumeration.
				pDoc->application->getResourceManager()->getEnumeration(CResourceManager::effectManager,iterator);
				//Do while.
				while(iterator.hasMoreElements())
				{
					//Get resource.
					CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
					assert(resource != NULL);
#endif
					//Check type.
					if(IS_EFFECT_BASE(resource) && !resource->isReserved())
					{
						//Insert item.
						m_wndResourceView.InsertItem(resource->getName().getCString(),1,1,hTreeRoot);
					}
				}
			}
			//Close lock.
			pDoc->application->closeLock();
		}
	}

	//Expand it.
	m_wndResourceView.Expand(hTreeRoot,TVE_EXPAND);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillTextureFiles
//
///////////////////////////////////////////////////////////////////////////////

void CResourceView::FillTextureFiles()
{
	//Insert item.
	HTREEITEM hTreeRoot = m_wndResourceView.InsertItem(L"贴图文件",0,0);
	//Set item state.
	m_wndResourceView.SetItemState(hTreeRoot,TVIS_BOLD,TVIS_BOLD);

	//Check mainframe.
	if(MAINFRAME != NULL)
	{
		//Get active doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL && pDoc->application->getResourceManager() != NULL)
		{
			//Open lock.
			pDoc->application->openLock();
			{
				//Enumeration.
				CListNodeEnumeration iterator;
				//Get enumeration.
				pDoc->application->getResourceManager()->getEnumeration(CResourceManager::textureManager,iterator);
				//Do while.
				while(iterator.hasMoreElements())
				{
					//Get resource.
					CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
					assert(resource != _NULL);
#endif
					//Check type.
					if(IS_TEXTURE_BASE(resource) && !resource->isReserved())
					{
						//Insert item.
						m_wndResourceView.InsertItem(resource->getName().getCString(),1,1,hTreeRoot);
					}
				}
			}
			//Close lock.
			pDoc->application->closeLock();
		}
	}
	//Expand it.
	m_wndResourceView.Expand(hTreeRoot,TVE_EXPAND);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillRenderableFiles
//
///////////////////////////////////////////////////////////////////////////////

void CResourceView::FillRenderableFiles()
{
	//Insert item.
	HTREEITEM hTreeRoot = m_wndResourceView.InsertItem(L"绘制模板",0,0);
	//Set item state.
	m_wndResourceView.SetItemState(hTreeRoot,TVIS_BOLD,TVIS_BOLD);

	//Insert item.
	HTREEITEM hTreeInternalRoot = m_wndResourceView.InsertItem(L"内部模板",0,0,hTreeRoot);
	//Insert item.
	HTREEITEM hTreeExternalRoot = m_wndResourceView.InsertItem(L"外部模板",0,0,hTreeRoot);

	//Check mainframe.
	if(MAINFRAME != NULL)
	{
		//Get active doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL && pDoc->application->getResourceManager() != NULL)
		{
			//Open lock.
			pDoc->application->openLock();
			{
				//Enumeration.
				CListNodeEnumeration iterator;
				//Get enumeration.
				pDoc->application->getResourceManager()->getEnumeration(CResourceManager::primitiveManager,iterator);
				//Do while.
				while(iterator.hasMoreElements())
				{
					//Get resource.
					CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
					assert(resource != _NULL);
#endif
					//Check type.
					if(IS_PRIMITIVE_BASE(resource) && !resource->isReserved())
					{
						//Insert item.
						m_wndResourceView.InsertItem(resource->getName().getCString(),2,2,hTreeInternalRoot);
					}
				}
				//Get enumeration.
				pDoc->application->getResourceManager()->getEnumeration(CResourceManager::meshManager,iterator);
				//Do while.
				while(iterator.hasMoreElements())
				{
					//Get resource.
					CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
					assert(resource != NULL);
#endif
					//Check type.
					if(IS_FILEMESH_BASE(resource) && !resource->isReserved())
					{
						//Insert item.
						m_wndResourceView.InsertItem(resource->getName().getCString(),2,2,hTreeExternalRoot);
					}
				}
			}
			//Close lock.
			pDoc->application->closeLock();
		}
	}

	//Expand it.
	m_wndResourceView.Expand(hTreeRoot,TVE_EXPAND);
	//Expand it.
	m_wndResourceView.Expand(hTreeInternalRoot,TVE_EXPAND);
	//Expand it.
	m_wndResourceView.Expand(hTreeExternalRoot,TVE_EXPAND);
}
