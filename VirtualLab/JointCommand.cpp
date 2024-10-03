#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#include "ClassicBallJointDialog.h"
#include "ClassicHingeJointDialog.h"
#include "ClassicSliderJointDialog.h"
#include "ClassicUpVectorJointDialog.h"
#include "ClassicCorkscrewJointDialog.h"
#include "ClassicUniversalJointDialog.h"

#include "Custom6DOFJointDialog.h"
#include "CustomBallJointDialog.h"
#include "CustomHingeJointDialog.h"
#include "CustomSliderJointDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CVirtualLabView::OnButtonJointUpvector()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicUpVectorJointDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}

void CVirtualLabView::OnUpdateButtonJointUpvector(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}

void CVirtualLabView::OnButtonJointCorkscrew1()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicCorkscrewJointDialog dialog(true,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}

void CVirtualLabView::OnUpdateButtonJointCorkscrew1(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}

void CVirtualLabView::OnButtonJointCorkscrew2()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicCorkscrewJointDialog dialog(false,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}

void CVirtualLabView::OnUpdateButtonJointCorkscrew2(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}

void CVirtualLabView::OnButtonJointBall1()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicBallJointDialog dialog(true,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}

void CVirtualLabView::OnUpdateButtonJointBall1(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}

void CVirtualLabView::OnButtonJointBall2()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicBallJointDialog dialog(false,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointBall2(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJointHinge1()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicHingeJointDialog dialog(true,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointHinge1(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJointHinge2()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicHingeJointDialog dialog(false,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointHinge2(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJointSlider1()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicSliderJointDialog dialog(true,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointSlider1(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJointSlider2()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicSliderJointDialog dialog(false,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointSlider2(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}



void CVirtualLabView::OnButtonJointUniversal1()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicUniversalJointDialog dialog(true,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointUniversal1(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJointUniversal2()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CClassicUniversalJointDialog dialog(false,pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointUniversal2(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJointBall3()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCustomBallJointDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointBall3(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJointHinge3()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCustomHingeJointDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointHinge3(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJointSlider3()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCustomSliderJointDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJointSlider3(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}


void CVirtualLabView::OnButtonJoint6dof()
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command handler code here
	CCustom6DOFJointDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update scene view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateSceneView();
	}
}


void CVirtualLabView::OnUpdateButtonJoint6dof(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL && !pDoc->application->CPhysicsApplication::isRunning());
}
