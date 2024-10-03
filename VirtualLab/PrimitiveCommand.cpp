#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#include "SphereDialog.h"
#include "CapsuleDialog.h"
#include "ChamferCylinderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CVirtualLabView::OnButtonHemisphere()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CSphereDialog dialog(true,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}

void CVirtualLabView::OnUpdateButtonHemisphere(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonCapsule()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCapsuleDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonCapsule(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonChamferCylinder()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CChamferCylinderDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonChamferCylinder(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}
