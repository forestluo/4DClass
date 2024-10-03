/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaExplorerView.cpp
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


#include "alchemediaStdafx.h"
#include "Resource.h"
#include "alchemedia.h"
#include "alchemediaScene.h"
#include "alchemediaMainFrm.h"
#include "alchemediaExplorerView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



/////////////////////////////////////////////////////////////////////////////
// alchemediaExplorerView

alchemediaExplorerView::alchemediaExplorerView()
{
}

alchemediaExplorerView::~alchemediaExplorerView()
{
}

BEGIN_MESSAGE_MAP(alchemediaExplorerView, CDockablePane)
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

int alchemediaExplorerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_explorer.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Failed to create file view\n");
		return -1;      // fail to create
	}

	// Load view images:
//	m_iconList.Create(IDB_EXPLORER_VIEW_ICONS, 16, 0, RGB(255, 0, 255));
//	m_explorer.SetImageList(&m_iconList, TVSIL_NORMAL);

	m_toolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_toolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);
	m_toolBar.SetPaneStyle(m_toolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_toolBar.SetPaneStyle(m_toolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_toolBar.SetOwner(this);
	// All commands will be routed via this control , not via the parent frame:
	m_toolBar.SetRouteCommandsViaFrame(FALSE);

	// Fill in some static tree view data (dummy code, nothing magic here)
	AdjustLayout();

	return 0;
}

void alchemediaExplorerView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


void alchemediaExplorerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_explorer;
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

void alchemediaExplorerView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_toolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_toolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_explorer.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void alchemediaExplorerView::OnProperties()
{
	AfxMessageBox(_T("Properties...."));

}

void alchemediaExplorerView::OnFileOpen()
{
	// TODO: Add your command handler code here
}

void alchemediaExplorerView::OnFileOpenWith()
{
	// TODO: Add your command handler code here
}

void alchemediaExplorerView::OnDummyCompile()
{
	// TODO: Add your command handler code here
}

void alchemediaExplorerView::OnEditCut()
{
	// TODO: Add your command handler code here
}

void alchemediaExplorerView::OnEditCopy()
{
	// TODO: Add your command handler code here
}

void alchemediaExplorerView::OnEditClear()
{
	// TODO: Add your command handler code here
}

void alchemediaExplorerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_explorer.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void alchemediaExplorerView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_explorer.SetFocus();
}



void alchemediaExplorerView::PopulateScene(alchemediaScene* scene)
{
	m_explorer.DeleteAllItems();

	alchemediaScene::dTreeNode* rootNode = scene->GetRootNode();

//	dNodeInfo* info = scene->GetInfoFromNode (rootNode);
//	HTREEITEM root = m_explorer.InsertItem(_T(info->GetName()), 0, 0);

	int stack = 1;
	HTREEITEM  parent[D_GRAPH_MAX_STACK_DEPTH];
	alchemediaScene::dTreeNode* nodePool[D_GRAPH_MAX_STACK_DEPTH];

	parent[0] = NULL;
	nodePool[0] = rootNode;

/*
	for (int i = 0; i < 4; i ++) {
		parent[stack] = root;
		nodePool[stack] = scene->FindCameraNode(i);
		stack ++;
		_ASSERTE (stack < (sizeof (parent)/sizeof (parent[0])));
	}

	for (void* ptr =scene->GetFirstChild(rootNode); ptr; ptr =scene->GetNextChild(rootNode, ptr)) {
		naScene::dTreeNode* node =scene->GetNodeFromLink(ptr);
		dNodeInfo* info =scene->GetInfoFromNode(node);
		if (info->IsType(dSceneNodeInfo::GetRttiType())) {
			nodePool[stack] = node;
			parent[stack] = root;
			stack ++;
			_ASSERTE (stack < (sizeof (parent)/sizeof (parent[0])));
		}
	}
*/
	// scan all dSceneNodeInfo and add then to the tree
	while (stack) {
		stack --;
		alchemediaScene::dTreeNode* rootNode = nodePool[stack];

		HTREEITEM root = parent[stack];
		dNodeInfo* info = scene->GetInfoFromNode(rootNode);

		int iconIndex = 0;
//		if (info->IsType (dBoneNodeInfo::GetRttiType())) {
//			iconIndex = 6;
//		} else if (info->IsType(dCameraNodeInfo::GetRttiType())) {
//			iconIndex = 1;
//		} else if (info->IsType(dSceneNodeInfo::GetRttiType())) {
//			iconIndex = 2;
//		} else if (info->IsType(dGeometryNodeInfo::GetRttiType())) {
//			iconIndex = 3;
//		} else if (info->IsType (dMaterialNodeInfo::GetRttiType())) {
//			iconIndex = 4;
//		} else if (info->IsType (dTextureNodeInfo::GetRttiType())) {		
//			iconIndex = 5;
//		} else {
//			_ASSERTE (0);
//		}
		HTREEITEM item = m_explorer.InsertItem(_T(info->GetName()), iconIndex, iconIndex, root, TVI_FIRST);
		_ASSERTE (info->GetUniqueID() == rootNode->GetKey());
		m_explorer.SetItemData(item, info->GetUniqueID());

		if (info->IsType(dSceneNodeInfo::GetRttiType())) {
			m_explorer.Expand(root, TVE_EXPAND);
		}

		//m_map.Insert(item, rootNode);
		for (void* ptr = scene->GetFirstChild(rootNode); ptr; ptr =scene->GetNextChild(rootNode, ptr)) {

			alchemediaScene::dTreeNode* node =scene->GetNodeFromLink(ptr);
			dNodeInfo* info = scene->GetInfoFromNode(node);
			if (info->IsType(dGeometryNodeSkinModifierInfo::GetRttiType())) {
				iconIndex = 2;
				HTREEITEM root = m_explorer.InsertItem(_T(info->GetName()), iconIndex, iconIndex, item, TVI_FIRST);
				m_explorer.SetItemData(root, info->GetUniqueID());

				iconIndex = 6;
				for (void* boneLink = scene->GetFirstChild(node); boneLink; boneLink = scene->GetNextChild(node, boneLink)) {
					dScene::dTreeNode* boneNode = scene->GetNodeFromLink(boneLink);
					dSceneNodeInfo* boneInfo = (dSceneNodeInfo*) scene->GetInfoFromNode(boneNode);
					HTREEITEM item = m_explorer.InsertItem(_T(boneInfo->GetName()), iconIndex, iconIndex, root, TVI_LAST);
					m_explorer.SetItemData(item, boneInfo->GetUniqueID());
				}
			} else {
				nodePool[stack] = node;
				parent[stack] = item;
				stack ++;
			}
		}
	}

//	Expand(root);
}

