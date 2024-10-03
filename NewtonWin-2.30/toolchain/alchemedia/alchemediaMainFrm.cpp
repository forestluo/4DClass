/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaMainFrame.cpp
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
#include "alchemedia.h"
#include "alchemediaDoc.h"
#include "alchemediaView.h"
#include "alchemediaScene.h"
#include "alchemediaMainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// alchemediaMainFrame

#define ID_MAX_IMPORT_PLUGINS 100
typedef dPluginRecord** (CALLBACK* GetPluginArray)();



IMPLEMENT_DYNCREATE(alchemediaMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(alchemediaMainFrame, CFrameWndEx)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &alchemediaMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &alchemediaMainFrame::OnToolbarCreateNew)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND_RANGE(ID_IMPORT_DLLS, ID_IMPORT_DLLS + ID_MAX_IMPORT_PLUGINS, &alchemediaMainFrame::OnImport)
	ON_COMMAND_RANGE(ID_EXPORT_DLLS, ID_EXPORT_DLLS + ID_MAX_IMPORT_PLUGINS, &alchemediaMainFrame::OnExport)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// alchemediaMainFrame construction/destruction

alchemediaMainFrame::alchemediaMainFrame()
	:m_importPluginCount(0)
	,m_exportPluginsCount(0)
	,m_importPlugins(NULL)
	,m_exportPlugins(NULL)
{
	// TODO: add member initialization code here
}

alchemediaMainFrame::~alchemediaMainFrame()
{
}

int alchemediaMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));

	if (!m_mainMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_mainMenuBar.SetPaneStyle(m_mainMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
//	m_mainMenuBar.SetMenuSizes(CSize(30,30), CSize(24,24));
//	m_mainMenuBar.SetMenuSizes(CSize(22,22), CSize(16,16));
//	m_mainMenuBar.SetPaneStyle(m_mainMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);


//	CMFCToolBarInfo tbInfo;
//	tbInfo.m_uiColdResID = 0;
//	tbInfo.m_uiDisabledResID = 0;
//	tbInfo.m_uiHotResID	= 0;
//	tbInfo.m_uiLargeColdResID	= 0;
//	tbInfo.m_uiLargeDisabledResID = 0;
//	tbInfo.m_uiLargeHotResID = 0;
//	tbInfo.m_uiMenuResID = IDR_MAINFRAME;

	if (!m_mainToolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
//		!m_mainToolbar.LoadToolBarEx(IDR_MAINFRAME_ICONS, tbInfo))
		!m_mainToolbar.LoadToolBar(IDR_MAINFRAME_ICONS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
//	m_mainToolbar.SetLockedSizes(CSize(30,30), CSize(24,24));

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_mainToolbar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_mainToolbar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_mainMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_mainToolbar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_mainMenuBar);
	DockPane(&m_mainToolbar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Load menu item image (not placed on any standard toolbars):
	//CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, 0);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	m_explorer.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_explorer);
	CDockablePane* pTabbedBar = NULL;
	m_wndClassView.AttachToTabWnd(&m_explorer, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

m_viewPort0->m_toolBar.SetLargeIcons(TRUE);
SIZE size;
size.cx = 24;
size.cy = 24;
//	m_toolBar.SetLargeIcons(TRUE);
m_viewPort0->m_toolBar.SetSizes(size, size);
m_viewPort0->m_toolBar.LoadToolBar(IDR_VIEWER_TOOLBAR, 0, 0, TRUE);
//	m_toolBar.LoadBitmap(IDR_VIEWER_TOOLBAR, 0, 0, TRUE);



	// share all display List among view ports
	wglShareLists(m_viewPort0->m_renderContext, m_viewPort1->m_renderContext);
	wglShareLists(m_viewPort0->m_renderContext, m_viewPort2->m_renderContext);
	wglShareLists(m_viewPort0->m_renderContext, m_viewPort3->m_renderContext);



	// Enable toolbar and docking window menu replacement
//	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);
	// enable quick (Alt+drag) toolbar customization
//	CMFCToolBar::EnableQuickCustomization();
//	if (CMFCToolBar::GetUserImages() == NULL)
//	{
//		// load user-defined toolbar images
//		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
//		{
//			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
//			CMFCToolBar::SetUserImages(&m_UserImages);
//		}
//	}

	// load all available plug ins
	RegisterAllPlugins();


	return 0;
}

BOOL alchemediaMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{

	// create splitter window
	if (!m_viewportSplitter.CreateStatic(this, 2, 2))
		return FALSE;

	if (!m_viewportSplitter.CreateView(0, 0, RUNTIME_CLASS(alchemediaView), CSize(100, 100), pContext) ||
		!m_viewportSplitter.CreateView(0, 1, RUNTIME_CLASS(alchemediaView), CSize(100, 100), pContext) ||
		!m_viewportSplitter.CreateView(1, 0, RUNTIME_CLASS(alchemediaView), CSize(100, 100), pContext) ||
		!m_viewportSplitter.CreateView(1, 1, RUNTIME_CLASS(alchemediaView), CSize(100, 100), pContext))
	{
		m_viewportSplitter.DestroyWindow();
		return FALSE;
	}

	// get the view port windows
	m_viewPort0 = (alchemediaView*) m_viewportSplitter.GetPane(0, 0);
	m_viewPort1 = (alchemediaView*) m_viewportSplitter.GetPane(0, 1);
	m_viewPort2 = (alchemediaView*) m_viewportSplitter.GetPane(1, 0);
	m_viewPort3 = (alchemediaView*) m_viewportSplitter.GetPane(1, 1);


	m_viewPort0->m_mainFrame = this;
	m_viewPort1->m_mainFrame = this;
	m_viewPort2->m_mainFrame = this;
	m_viewPort3->m_mainFrame = this;

	m_viewPort0->m_myCameraIndex = 0;
	m_viewPort1->m_myCameraIndex = 1;
	m_viewPort2->m_myCameraIndex = 2;
	m_viewPort3->m_myCameraIndex = 3;

	m_document = m_viewPort0->GetDocument();
	m_document->m_mainFrame = this;
	m_document->m_explorer = &m_explorer;
	return TRUE;
}

alchemediaSplitterViewports& alchemediaMainFrame::GetSplitter()
{
	return m_viewportSplitter;
}

BOOL alchemediaMainFrame::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	// unload all dll plugins
	while (m_allPlugins.GetFirst()) {
		FreeLibrary(m_allPlugins.GetFirst()->GetInfo());
		m_allPlugins.Remove(m_allPlugins.GetFirst());
	}

	// delete the world 
	if (m_importPlugins) {
		delete[] m_importPlugins;
	}
	if (m_exportPlugins) {
		delete[] m_exportPlugins;
	}

	return CFrameWndEx::DestroyWindow();
}


BOOL alchemediaMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL alchemediaMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Create class view
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Class View window\n");
		return FALSE; // failed to create
	}

	// Create file view
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_explorer.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create File View window\n");
		return FALSE; // failed to create
	}

	// Create output window
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Output window\n");
		return FALSE; // failed to create
	}

	// Create properties window
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons();
	return TRUE;
}

void alchemediaMainFrame::SetDockingWindowIcons()
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_explorer.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// alchemediaMainFrame diagnostics

#ifdef _DEBUG
void alchemediaMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void alchemediaMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// alchemediaMainFrame message handlers

void alchemediaMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT alchemediaMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

BOOL alchemediaMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


// make sure view port are centered on initialization
void alchemediaMainFrame::CenterViewPorts(void)
{
	CDockingManager* manager = GetDockingManager();
	manager->AdjustDockingLayout();

	m_viewportSplitter.CenterViewPorts();
}

void alchemediaMainFrame::RegisterAllPlugins(void)
{
	char appPath [_MAX_PATH + 1];
	char plugInPath [_MAX_PATH + 256];
	char rootPathInPath [_MAX_PATH + 256];

	// allocate space for the list of different kind of plug ins
	if (m_exportPlugins) {
		delete[] m_exportPlugins;
	}
	m_exportPlugins = new dExportPlugin* [ID_MAX_IMPORT_PLUGINS];

	if (m_importPlugins) {
		delete[] m_importPlugins;
	}
	m_importPlugins = new dImportPlugin* [ID_MAX_IMPORT_PLUGINS];

	::GetModuleFileName(NULL, appPath, _MAX_PATH);

	sprintf (plugInPath, "%s", appPath);
	char* ptr = strrchr (plugInPath, '/');
	if (!ptr) {
		ptr = strrchr (plugInPath, '\\');
	}
	*ptr = 0;
	strcat (ptr, "/plugins");
	sprintf (rootPathInPath, "%s/*.dll", plugInPath);


	_finddata_t data;

	intptr_t handle = _findfirst (rootPathInPath, &data);
	if (handle != -1) {
		do {
			sprintf (rootPathInPath, "%s/%s", plugInPath, data.name);

			HMODULE module = LoadLibrary(rootPathInPath);
			//HMODULE module = AfxLoadLibrary (rootPathInPath);
			//int error = GetLastError();

			if (module) {
				// get the interface function pointer to the Plug in classes
				GetPluginArray GetPluginsTable = (GetPluginArray) GetProcAddress (module, "GetPluginArray"); 
				if (GetPluginsTable) {
					m_allPlugins.Append(module);
				} else {
					FreeLibrary(module);
				}
			}
		} while (_findnext (handle, &data) == 0);
		_findclose (handle);
	}
}

void alchemediaMainFrame::RecalcLayout(BOOL bNotify)
{
	// TODO: Add your specialized code here and/or call the base class
	CFrameWndEx::RecalcLayout(bNotify);

	CenterViewPorts();
}

void alchemediaMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CFrameWndEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: Add your message handler code here
	CMenu* importMenu = NULL;
	CMenu* exportMenu = NULL;
	int count = pPopupMenu->GetMenuItemCount();
	for (int j = 0; j < count; j ++) {
		char name[256];
		pPopupMenu->GetMenuString(j, name, sizeof (name), MF_BYPOSITION);
		if (!stricmp (name, "import..")) {
			CMenu* subMenu = pPopupMenu->GetSubMenu(j);
			if (subMenu->GetMenuItemID(0) == ID_IMPORT_MARKER) {
				subMenu->DeleteMenu(0, MF_BYPOSITION);
				importMenu = subMenu;
			}
		}
		if (!stricmp (name, "export..")) {
			CMenu* subMenu = pPopupMenu->GetSubMenu(j);
			if (subMenu->GetMenuItemID(0) == ID_EXPORT_MARKER) {
				subMenu->DeleteMenu(0, MF_BYPOSITION);
				exportMenu = subMenu;
			}
		}
	}

	if (importMenu && exportMenu) {
		int id_importIndex = ID_IMPORT_DLLS;
		int id_exportIndex = ID_EXPORT_DLLS;

		for (alchemdiaPluginDlls::dListNode* dllNode = m_allPlugins.GetFirst(); dllNode; dllNode = dllNode->GetNext()) {
			HMODULE module = dllNode->GetInfo();
			GetPluginArray GetPluginsTable = (GetPluginArray) GetProcAddress (module, "GetPluginArray"); 
			dPluginRecord** table = GetPluginsTable();

			for (int i = 0; table[i]; i ++) {
				dPluginRecord* plugin = table[i];
				switch (plugin->GetType())
				{
					case dPluginRecord::m_ImportPlugin:
					{
						dImportPlugin* importPlugin = (dImportPlugin*) plugin;
						m_importPlugins[id_importIndex - ID_IMPORT_DLLS] = importPlugin;
						_ASSERTE ((id_importIndex - ID_IMPORT_DLLS) < ID_MAX_IMPORT_PLUGINS);
						const char* menuName = importPlugin->GetMenuName ();
						//const char* description = importPlugin->GetFileDescription ();
						importMenu->AppendMenu(MF_STRING | MF_ENABLED, id_importIndex, menuName);
						importMenu->EnableMenuItem(id_importIndex, MF_BYCOMMAND | MF_ENABLED);    
						id_importIndex ++;
						break;
					}

					case dPluginRecord::m_ExportPlugin:
					{
						dExportPlugin* exportPlugin = (dExportPlugin*) plugin;
						m_exportPlugins[id_exportIndex - ID_EXPORT_DLLS] = exportPlugin;
						_ASSERTE ((id_exportIndex - ID_EXPORT_DLLS) < ID_MAX_IMPORT_PLUGINS);

						const char* menuName = exportPlugin->GetMenuName ();
						//const char* description = exportlugin->GetFileDescription ();

						exportMenu->AppendMenu(MF_STRING | MF_ENABLED, id_exportIndex, menuName);
						exportMenu->EnableMenuItem(id_exportIndex, MF_BYCOMMAND | MF_ENABLED);    
						id_exportIndex ++;
						break;
					}
				}
			}
		}
	}
}


void alchemediaMainFrame::OnExport(UINT nID)
{
	int index = nID - ID_EXPORT_DLLS;
	dExportPlugin* exportPlugin = m_exportPlugins[index];

	char tmp[1024];
	const char* ext = exportPlugin->GetFileExtension ();
	const char* description = exportPlugin->GetFileDescription();
	tmp[0] = 0;
	memset (tmp, 0, sizeof (tmp));
	strcpy (tmp, description);
	sprintf (tmp + strlen(tmp) + 1, "*.%s", ext);

	char fileNamePath[1024];
	fileNamePath[0] = 0;
	OPENFILENAME fileNameInfo;
	memset (&fileNameInfo, 0, sizeof (fileNameInfo));
	fileNameInfo.lStructSize = sizeof (fileNameInfo);
	fileNameInfo.lpstrTitle = description;
	fileNameInfo.lpstrFilter = tmp;
	fileNameInfo.lpstrFile = fileNamePath;
	fileNameInfo.nMaxFile = sizeof (fileNamePath);
	if (GetSaveFileName(&fileNameInfo)) {
		exportPlugin->Export(fileNamePath, m_document->GetCurWorld());
//		Invalidate();
	}
}



void alchemediaMainFrame::OnImport(UINT nID)
{
	int index = nID - ID_IMPORT_DLLS;
	dImportPlugin* importPlugin = m_importPlugins[index];

	char tmp[1024];
	const char* ext = importPlugin->GetFileExtension ();
	const char* description = importPlugin->GetFileDescription();
	tmp[0] = 0;
	memset (tmp, 0, sizeof (tmp));
	strcpy (tmp, description);
	sprintf (tmp + strlen(tmp) + 1, "*.%s", ext);

	char fileNamePath[1024];
	fileNamePath[0] = 0;
	OPENFILENAME fileNameInfo;
	memset (&fileNameInfo, 0, sizeof (fileNameInfo));
	fileNameInfo.lStructSize = sizeof (fileNameInfo);
	fileNameInfo.lpstrTitle = description;
	fileNameInfo.lpstrFilter = tmp;
	fileNameInfo.lpstrFile = fileNamePath;
	fileNameInfo.nMaxFile = sizeof (fileNamePath);
	if (GetOpenFileName(&fileNameInfo)) {
		alchemediaScene* const world = m_document->NewWorldInstance();
		if (importPlugin->Import(fileNamePath, world)) {
			char texPath[256];
			dExtractPathFromFullName (fileNamePath, texPath);

			world->MergeDuplicateTextures();
			world->LoadTextures (texPath);
			world->UpdateAllOOBB ();
			world->RemoveUnusedVertex();
			m_document->m_explorer->PopulateScene(world);
			Invalidate();
		}
	}
}


void alchemediaMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CenterViewPorts();
}
