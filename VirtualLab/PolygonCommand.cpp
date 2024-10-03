#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#include "CubeDialog.h"
#include "CuboidDialog.h"
#include "SphereDialog.h"
#include "PolygonDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CVirtualLabView::OnButtonSphere()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CSphereDialog dialog(false,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}

void CVirtualLabView::OnUpdateButtonSphere(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}

void CVirtualLabView::OnButtonCube()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCubeDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}

void CVirtualLabView::OnUpdateButtonCube(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}

void CVirtualLabView::OnButtonCuboid()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCuboidDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}

void CVirtualLabView::OnUpdateButtonCuboid(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonPolygon()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CPolygonDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonPolygon(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}
