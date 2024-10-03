#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#include "SliceDialog.h"
#include "ArrayDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CVirtualLabView::OnButtonSlice()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CSliceDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonSlice(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonSliceXvertical()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CArrayDialog dialog(CPrimitiveAttribute::floor0Primitive,CArrayManager::xVerticalArray,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonSliceXvertical(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonSliceYvertical()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CArrayDialog dialog(CPrimitiveAttribute::floor0Primitive,CArrayManager::yVerticalArray,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonSliceYvertical(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonSliceZvertical()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CArrayDialog dialog(CPrimitiveAttribute::floor0Primitive,CArrayManager::zVerticalArray,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonSliceZvertical(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonBallYvertical()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CArrayDialog dialog(CPrimitiveAttribute::sphere0Primitive,CArrayManager::yVerticalArray,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonBallYvertical(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonCuboidYvertical()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CArrayDialog dialog(CPrimitiveAttribute::cuboid0Primitive,CArrayManager::yVerticalArray,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonCuboidYvertical(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}
