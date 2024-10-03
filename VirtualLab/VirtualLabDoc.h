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

// VirtualLabDoc.h : interface of the CVirtualLabDoc class
//


#pragma once

#include "MFCApplication.h"

class CVirtualLabDoc : public CDocument
{
protected: // create from serialization only
	CVirtualLabDoc();
	DECLARE_DYNCREATE(CVirtualLabDoc)

// Attributes
public:
	//Application.
	CMFCApplication* application;

public:

	////////////////////////////////////////
	//
	//General devices.
	//
	int getDeviceCount();
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//PSEye devices.
	//
	void openPSEyeDevices();
	void closePSEyeDevices();
	int getPSEyeDeviceCount();
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Kinect devices.
	//
	void openKinectDevices();
	void closeKinectDevices();
	int getKinectDeviceCount();
	void addDepthFilter(const CNormalString& name,const CNormalString& deviceName);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//HAAR filters.
	//
	void closeFilters();
	int getFilterCount();
	int getHAARFilterCount();
	void addHAARFilter(const CNormalString& name,const CNormalString& deviceName);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Dynamic texture.
	//
	void closeInputTextures();
	int getInputTextureCount();
	void addInputTexture(const CNormalString& name,const CNormalString& deviceName);
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	//Dynamic object.
	//
	void addControlledBall(const CNormalString& name,const CNormalString& deviceName);
	void addInputGroundMesh(const CNormalString& name,const CNormalString& deviceName);
	void addControlledItemArray(const CNormalString& name,const CNormalString& deviceName);
	void addKinematicItemArray(const CNormalString& name,const CNormalString& deviceName);
	//
	////////////////////////////////////////

public:
	////////////////////////////////////////
	//
	//Add options.
	//
	void addDeviceOptions(CComboBox* pCombo);
	void addKinectOptions(CComboBox* pCombo);
	void addFilterOptions(CComboBox* pCombo);
	void addParentOptions(CComboBox* pCombo);
	void addChildrenOptions(CComboBox* pCombo);
	//
	void addDeviceOptions(CMFCPropertyGridProperty* pProp);
	void addFilterOptions(CMFCPropertyGridProperty* pProp);
	void addTextureOptions(CMFCPropertyGridProperty* pProp);
	//
	void addEffectOptions(CMFCPropertyGridProperty* pProp);
	void addMeshOptions(CMFCPropertyGridProperty* pProp);
	void addPrimitiveOptions(CMFCPropertyGridProperty* pProp);
	//
	////////////////////////////////////////

// Operations
public:


// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CVirtualLabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
