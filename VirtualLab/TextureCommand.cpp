#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#include "HAARFilter.h"
#include "PSEyeDevice.h"
#include "KinectDevice.h"

#include "HAARFilterDialog.h"
#include "DepthFilterDialog.h"
#include "InputTextureDialog.h"

#include "D3DXInputTexture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CVirtualLabView::OnButtonPseyeOpen()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Open devices.
	pDoc->openPSEyeDevices();
	//Update resource view.
	if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
}

void CVirtualLabView::OnUpdateButtonPseyeOpen(CCmdUI *pCmdUI)
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
					!pDoc->application->CPhysicsApplication::isRunning() && 
					CPSEyeDevice::getCameraCount() > 0 && pDoc->getPSEyeDeviceCount() <= 0);
}

void CVirtualLabView::OnButtonPseyeClose()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL && pDoc->application != NULL);
#endif
	//Get current selection.
	CD3DXObject* focused = pDoc->application->getFocused();
	//Check result.
	if(IS_PSEYEDEVICE_BASE(focused))
	{
		//Remove it from focused.
		pDoc->application->clearFocused();
		//Check result.
		if(pDoc->application->getViewPort() != NULL)
		{
			//Update the default value.
			g_pMainFrame->ShowProperties(pDoc->application->getViewPort());
		}
	}
	//Close devices.
	pDoc->closePSEyeDevices();
	//Update resource view.
	if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
}

void CVirtualLabView::OnUpdateButtonPseyeClose(CCmdUI *pCmdUI)
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
					!pDoc->application->CPhysicsApplication::isRunning() &&
					pDoc->getPSEyeDeviceCount() > 0);
}


void CVirtualLabView::OnButtonHaarDetector()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Dialog.
	CHAARFilterDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update resource view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
	}
}


void CVirtualLabView::OnUpdateButtonHaarDetector(CCmdUI *pCmdUI)
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
					!pDoc->application->CPhysicsApplication::isRunning() && 
					pDoc->getDeviceCount() > 0);
}



void CVirtualLabView::OnButtonFilterClose()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL && pDoc->application != NULL);
#endif
	//Get current selection.
	CD3DXObject* focused = pDoc->application->getFocused();
	//Check result.
	if(IS_FILTER_BASE(focused))
	{
		//Remove it from focused.
		pDoc->application->clearFocused();
		//Check result.
		if(pDoc->application->getViewPort() != NULL)
		{
			//Update the default value.
			g_pMainFrame->ShowProperties(pDoc->application->getViewPort());
		}
	}
	//Close filters.
	pDoc->closeFilters();
	//Update resource view.
	if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
}


void CVirtualLabView::OnUpdateButtonFilterClose(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() && pDoc->getFilterCount() > 0);
}


void CVirtualLabView::OnButtonImageTexture()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Dialog.
	CInputTextureDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update resource view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
	}
}


void CVirtualLabView::OnUpdateButtonImageTexture(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() && pDoc->getDeviceCount() > 0);
}


void CVirtualLabView::OnButtonTextureClose()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL && pDoc->application != NULL);
#endif
	//Get current selection.
	CD3DXObject* focused = pDoc->application->getFocused();
	//Check result.
	if(IS_INPUTTEXTURE_BASE(focused))
	{
		//Remove it from focused.
		pDoc->application->clearFocused();
		//Check result.
		if(pDoc->application->getViewPort() != NULL)
		{
			//Update the default value.
			g_pMainFrame->ShowProperties(pDoc->application->getViewPort());
		}
	}
	//Close textures.
	pDoc->closeInputTextures();
	//Update resource view.
	if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
}


void CVirtualLabView::OnUpdateButtonTextureClose(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() && pDoc->getInputTextureCount() > 0);
}


void CVirtualLabView::OnButtonKinectOpen()
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Open devices.
	pDoc->openKinectDevices();
	//Update resource view.
	if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
}


void CVirtualLabView::OnUpdateButtonKinectOpen(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() &&
		CKinectDevice::getKinectCount() > 0 && pDoc->getKinectDeviceCount() <= 0);
}


void CVirtualLabView::OnButtonKinectClose()
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL && pDoc->application != NULL);
#endif
	//Get current selection.
	CD3DXObject* focused = pDoc->application->getFocused();
	//Check result.
	if(IS_KINECTDEVICE_BASE(focused))
	{
		//Remove it from focused.
		pDoc->application->clearFocused();
		//Check result.
		if(pDoc->application->getViewPort() != NULL)
		{
			//Update the default value.
			g_pMainFrame->ShowProperties(pDoc->application->getViewPort());
		}
	}
	//Close devices.
	pDoc->closeKinectDevices();
	//Update resource view.
	if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
}


void CVirtualLabView::OnUpdateButtonKinectClose(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() && pDoc->getKinectDeviceCount() > 0);
}


void CVirtualLabView::OnButtonDepthFilter()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Dialog.
	CDepthFilterDialog dialog(pDoc);
	//Do modal.
	if(dialog.DoModal() == IDOK)
	{
		//Update resource view.
		if(g_pMainFrame != NULL) g_pMainFrame->UpdateResourceView();
	}
}


void CVirtualLabView::OnUpdateButtonDepthFilter(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL &&
		!pDoc->application->CPhysicsApplication::isRunning() && pDoc->getKinectDeviceCount() > 0);
}
