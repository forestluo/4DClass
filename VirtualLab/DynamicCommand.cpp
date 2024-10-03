#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#include "GroundMeshDialog.h"
#include "ControlBallDialog.h"
#include "ControlItemDialog.h"
#include "KinematicItemDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CVirtualLabView::OnButtonGroundMesh()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Dialog.
	CGroundMeshDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update resource view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonGroundMesh(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() &&	pDoc->getKinectDeviceCount() > 0);
}


void CVirtualLabView::OnButtonControlledBall()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Dialog.
	CControlBallDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update resource view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonControlledBall(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() &&	pDoc->getKinectDeviceCount() > 0);
}



void CVirtualLabView::OnButtonControlledItem()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Dialog.
	CControlItemDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update resource view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonControlledItem(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() &&	pDoc->getKinectDeviceCount() > 0);
}



void CVirtualLabView::OnButtonKinematicItem()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Dialog.
	CKinematicItemDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update resource view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonKinematicItem(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() &&	pDoc->getKinectDeviceCount() > 0);
}
