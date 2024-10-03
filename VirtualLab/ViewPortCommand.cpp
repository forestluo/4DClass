#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "VirtualLabDoc.h"
#include "VirtualLabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CVirtualLabView::OnButtonViewXz()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check result.
	if(pDoc->application != NULL) pDoc->application->yAxisView();
}


void CVirtualLabView::OnUpdateButtonViewXz(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL);
}


void CVirtualLabView::OnButtonViewXy()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check result.
	if(pDoc->application != NULL) pDoc->application->zAxisView();
}


void CVirtualLabView::OnUpdateButtonViewXy(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL);
}



void CVirtualLabView::OnButtonViewYz()
{
	// TODO: Add your command handler code here
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Check result.
	if(pDoc->application != NULL) pDoc->application->xAxisView();
}


void CVirtualLabView::OnUpdateButtonViewYz(CCmdUI *pCmdUI)
{
	CVirtualLabDoc* pDoc = GetDocument();
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(pDoc->application != NULL);
}
