// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#pragma once

#include "ViewPort.h"
#include "PhysicsObject.h"
#include "PhysicsJointObject.h"
#include "D3DXDevice.h"
#include "D3DXFilter.h"
#include "D3DXTexture.h"
#include "D3DXResource.h"
#include "D3DXFileMesh.h"
#include "D3DXLinestrip.h"
#include "D3DXPrimitive.h"
#include "D3DXRenderable.h"
#include "D3DXRenderableObject.h"

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// Construction
public:
	CPropertiesWnd();

	void AdjustLayout();
	///////////////////////////////////////
	//
	//Enable properties.
	void EnableProperties(BOOL bEnable);
	//
	//Update properties.
	void UpdateProperties();
	//
	//Show properties.
	void ShowProperties(CViewPort* pViewPort);
	//Show properties.
	void ShowProperties(CD3DXResource* pResource);
	//Show properties.
	void ShowProperties(CD3DXRenderableObject* pRenderableObject);
	//
	///////////////////////////////////////

// Attributes
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

	//Clear handles.
	void ClearHandles();
	///////////////////////////////////////
	//
	//Current selection.
	int nSelectedPropertyPage;
	//Properties for current.
	CMFCPropertyGridProperty* g_pPropHandles[64];
	//
	///////////////////////////////////////

// Implementation
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	//Change property page.
	afx_msg void OnSelendokCombo();
	//On property value changed.
	afx_msg LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

protected:

	///////////////////////////////////////
	//
	// Viewport.
	//
	//Fill properties.
	void FillProperties(CViewPort* pViewPort);
	//Change properties.
	void ChangeProperties(CViewPort* pViewPort);
	//On property value changed.
	void OnPropertyChanged(CViewPort* pViewPort,CMFCPropertyGridProperty *pProp);
	//
	///////////////////////////////////////

protected:

	///////////////////////////////////////
	//
	// Resource.
	//
	//Fill box properties.
	void FillBoxProperties(CD3DXRenderable* pRenderable);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Device.
	//
	//Show properties.
	void ShowProperties(CD3DXDevice* pDevice);
	//Fill properties.
	void FillProperties(CD3DXDevice* pDevice);
	//Fill properties.
	void FillPSEyeProperties(CD3DXDevice* pDevice);
	//On property value changed.
	void OnPropertyChanged(CD3DXDevice* pDevice,CMFCPropertyGridProperty *pProp);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Filter.
	//
	//Show properties.
	void ShowProperties(CD3DXFilter* pFilter);
	//Fill properties.
	void FillProperties(CD3DXFilter* pFilter);
	//Fill properties.
	void FillHAARProperties(CD3DXFilter* pFilter);
	//On property value changed.
	void OnPropertyChanged(CD3DXFilter* pFilter,CMFCPropertyGridProperty *pProp);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Effect.
	//
	//Show properties.
	void ShowProperties(CD3DXEffect* pEffect);
	//Fill properties.
	void FillProperties(CD3DXEffect* pEffect);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Texture.
	//
	//Show properties.
	void ShowProperties(CD3DXTexture* pTexture);
	//Fill properties.
	void FillProperties(CD3DXTexture* pTexture);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// File mesh.
	//
	//Show properties.
	void ShowProperties(CD3DXFileMesh* pFileMesh);
	//Fill properties.
	void FillProperties(CD3DXFileMesh* pFileMesh);
	//Change property page.
	void ChangePropertyPage(CD3DXFileMesh* pFileMesh,int nSelected);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Linestrip.
	//
	//Show properties.
	void ShowProperties(CD3DXLinestrip* pLinestrip);
	//Fill properties.
	void FillProperties(CD3DXLinestrip* pLinestrip);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Primitive.
	//
	//Show properties.
	void ShowProperties(CD3DXPrimitive* pPrimitive);
	//Fill properties.
	void FillProperties(CD3DXPrimitive* pPrimitive);
	//Change property page.
	void ChangePropertyPage(CD3DXPrimitive* pPrimitive,int nSelected);
	//
	///////////////////////////////////////

protected:

	///////////////////////////////////////
	//
	// Renderable object.
	//
	//Fill properties.
	void FillProperties(CD3DXRenderableObject* pRenderableObject);
	//Fill properties.
	void FillBoxProperties(CD3DXRenderableObject* pRenderableObject);
	//Fill properties.
	void FillRenderProperties(CD3DXRenderableObject* pRenderableObject);
	//
	//Change properties.
	void ChangeProperties(CD3DXRenderableObject* pRenderableObject);
	//Change property page.
	void ChangePropertyPage(CD3DXRenderableObject* pRenderableObject,int nSelected);
	//
	//On property value changed.
	void OnPropertyChanged(CD3DXRenderableObject* pRenderableObject,CMFCPropertyGridProperty *pProp);
	//On property value changed.
	void OnRenderPropertyChanged(CD3DXRenderableObject* pRenderableObject,CMFCPropertyGridProperty *pProp);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Physics object.
	//
	//Fill properties.
	void FillPhysicsProperties(CPhysicsObject* pPhysicsObject);
	//Fill properties.
	void FillPhysicsForceProperties(CPhysicsObject* pPhysicsObject);
	//
	//Change properties.
	void ChangePhysicsProperties(CPhysicsObject* pPhysicsObject);
	//Change properties.
	void ChangePhysicsForceProperties(CPhysicsObject* pPhysicsObject);
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	// Physics object.
	//
	//Fill properties.
	void FillJointProperties(CPhysicsJointObject* pJointObject);
	//Fill properties.
	void FillJointForceProperties(CPhysicsJointObject* pJointObject);
	//
	//Change properties.
	void ChangeJointProperties(CPhysicsJointObject* pJointObject);
	//Change properties.
	void ChangeJointForceProperties(CPhysicsJointObject* pJointObject);
	//
	//On property value changed.
	void OnJointPropertyChanged(CPhysicsJointObject* pJointObject,CMFCPropertyGridProperty *pProp);
	//
	///////////////////////////////////////
};

