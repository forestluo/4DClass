#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#include "CompoundBoxDialog.h"
#include "CompoundAxisDialog.h"
#include "CompoundPlusDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CVirtualLabView::OnButtonCompoundAxis()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCompoundAxisDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonCompoundAxis(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}



void CVirtualLabView::OnButtonCompoundCross()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCompoundPlusDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonCompoundCross(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonCompoundBox()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCompoundBoxDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonCompoundBox(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}
