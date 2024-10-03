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

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "4DProperties.h"
#include "VirtualLabDoc.h"

#include "PSEyeDevice.h"
#include "KinectDevice.h"
#include "CLEyeMulticam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
///////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Device
const LPCTSTR DEVICE_PROPERTIES[] =
{
	PROPERTY_GENERAL
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXDevice* pDevice)
{
#ifdef _DEBUG
	assert(pDevice != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL) pDoc->application->setFocused(pDevice);
	}
	//Set selected property page.
	nSelectedPropertyPage = 0;
	//Set window text.
	SetWindowTextW(pDevice->getName().getCString());

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Remove all selections.
	m_wndObjectCombo.ResetContent();
	//Add properties.
	for(int i = 0;i < sizeof(DEVICE_PROPERTIES) / sizeof(LPCTSTR);i ++)
	{
		//Add string.
		m_wndObjectCombo.AddString(DEVICE_PROPERTIES[i]);
	}
	//Set current selection.
	m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);

	//Fill properties.
	FillProperties(pDevice);
	//Check instance.
	if(IS_PSEYEDEVICE_BASE(pDevice))
	{
		//Fill properties.
		FillPSEyeProperties(pDevice);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CD3DXDevice* pDevice)
{
#ifdef _DEBUG
	assert(pDevice != NULL);
#endif

	//Create major.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"��Ҫ����");

	//Create property.
	HANDLE_NAME = new CMFCPropertyGridProperty(L"����",
		pDevice->getName().getCString(), L"�����豸���ڲ����ơ�");
	HANDLE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

	//Check type.
	if(IS_PSEYEDEVICE_BASE(pDevice))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"PSEye����ͷ", L"�����豸���ڲ�����");
	}
	else if(IS_KINECTDEVICE_BASE(pDevice))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"Kinect����ͷ", L"�����豸���ڲ�����");
	}
	else
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"δ֪�豸����", L"�����豸���ڲ�����");
	}
	HANDLE_TYPE->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Create property.
	HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"���ô���",
		(_variant_t) pDevice->countReference(), L"������ͼ���ⲿ���õĴ�����");
	HANDLE_REFERENCED_COUNT->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillPSEyeProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillPSEyeProperties(CD3DXDevice* pDevice)
{
	//Get device.
	CPSEyeDevice* pPSEyeDevice = (CPSEyeDevice *)pDevice;
#ifdef _DEBUG
	assert(pDevice != NULL && IS_PSEYEDEVICE_BASE(pDevice));
#endif

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"����ͷ");
	//Set description.
	HANDLE_GROUP_MAJOR->SetDescription(L"PSEye����ͷ����Ҫ������");

	{
		//Create property.
		HANDLE_PSEYE_FPS = new CMFCPropertyGridProperty(L"֡��",
			(_variant_t) pPSEyeDevice->getFps(), L"PSEye����ͷ�Ĳ�׽Ƶ���ʡ�ע��ÿ��ץȡ��֡����");
		//Disable it.
		HANDLE_PSEYE_FPS->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_PSEYE_FPS);

		//Create property.
		HANDLE_PSEYE_COLOR_MODE = new CMFCPropertyGridProperty(L"��ɫģʽ",
			(_variant_t) CPSEyeDevice::getColorModeDescription(pPSEyeDevice->getColorMode()), L"PSEye����ͷ����ɫģʽ��");
		//Add option.
		HANDLE_PSEYE_COLOR_MODE->AddOption(CPSEyeDevice::getColorModeDescription(CLEYE_COLOR_RAW));
		HANDLE_PSEYE_COLOR_MODE->AddOption(CPSEyeDevice::getColorModeDescription(CLEYE_COLOR_PROCESSED));
		HANDLE_PSEYE_COLOR_MODE->AddOption(CPSEyeDevice::getColorModeDescription(CLEYE_MONO_RAW));
		HANDLE_PSEYE_COLOR_MODE->AddOption(CPSEyeDevice::getColorModeDescription(CLEYE_MONO_PROCESSED));
		HANDLE_PSEYE_COLOR_MODE->AddOption(CPSEyeDevice::getColorModeDescription(CLEYE_BAYER_RAW));
		//Disable it.
		HANDLE_PSEYE_COLOR_MODE->Enable(FALSE);
		HANDLE_PSEYE_COLOR_MODE->AllowEdit(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_PSEYE_COLOR_MODE);

		//Create property.
		HANDLE_PSEYE_RESOLUTION = new CMFCPropertyGridProperty(L"�ֱ���ģʽ",
			(_variant_t) CPSEyeDevice::getResolutionDescription(pPSEyeDevice->getResolution()), L"PSEye����ͷ�ķֱ���ģʽ��");
		//Add option.
		HANDLE_PSEYE_RESOLUTION->AddOption(CPSEyeDevice::getResolutionDescription(CLEYE_VGA));
		HANDLE_PSEYE_RESOLUTION->AddOption(CPSEyeDevice::getResolutionDescription(CLEYE_QVGA));
		//Disable it.
		HANDLE_PSEYE_RESOLUTION->Enable(FALSE);
		HANDLE_PSEYE_COLOR_MODE->AllowEdit(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_PSEYE_RESOLUTION);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_PSEYE_SENSOR = new CMFCPropertyGridProperty(L"������");
	//Set description.
	HANDLE_PSEYE_SENSOR->SetDescription(L"PSEye����ͷ�Ĵ�����������");

	{
		//Create property.
		HANDLE_PSEYE_SENSOR_GAIN = new CMFCPropertyGridProperty(L"�ź�����",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_GAIN), L"PSEye����ͷ���ź����档ȡֵ��Χ�ڣ�0��79��");
		//Disable it.
		HANDLE_PSEYE_SENSOR_GAIN->Enable(TRUE);
		//Add subitem.
		HANDLE_PSEYE_SENSOR->AddSubItem(HANDLE_PSEYE_SENSOR_GAIN);

		//Create property.
		HANDLE_PSEYE_SENSOR_EXPOSURE = new CMFCPropertyGridProperty(L"�ع�ǿ��",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_EXPOSURE), L"PSEye����ͷ���ع�ǿ�ȡ�ȡֵ��Χ�ڣ�0��511��");
		//Disable it.
		HANDLE_PSEYE_SENSOR_EXPOSURE->Enable(TRUE);
		//Add subitem.
		HANDLE_PSEYE_SENSOR->AddSubItem(HANDLE_PSEYE_SENSOR_EXPOSURE);

		//Create property.
		HANDLE_PSEYE_SENSOR_AUTOGAIN = new CMFCPropertyGridProperty(L"�����Զ�����",
			(_variant_t) (pPSEyeDevice->getValue(CLEYE_AUTO_GAIN) ? true : false), L"PSEye����ͷ�����Զ�������");
		//Disable it.
		HANDLE_PSEYE_SENSOR_AUTOGAIN->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_SENSOR->AddSubItem(HANDLE_PSEYE_SENSOR_AUTOGAIN);

		//Create property.
		HANDLE_PSEYE_SENSOR_AUTOEXPOSURE = new CMFCPropertyGridProperty(L"�ع��Զ�����",
			(_variant_t) (pPSEyeDevice->getValue(CLEYE_AUTO_EXPOSURE) ? true : false), L"PSEye����ͷ�ع��Զ�������");
		//Disable it.
		HANDLE_PSEYE_SENSOR_AUTOEXPOSURE->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_SENSOR->AddSubItem(HANDLE_PSEYE_SENSOR_AUTOEXPOSURE);

		//Create property.
		HANDLE_PSEYE_SENSOR_AUTOWHITEBALANCE = new CMFCPropertyGridProperty(L"��ƽ���Զ�����",
			(_variant_t) (pPSEyeDevice->getValue(CLEYE_AUTO_WHITEBALANCE) ? true : false), L"PSEye����ͷ��ƽ���Զ�������");
		//Disable it.
		HANDLE_PSEYE_SENSOR_AUTOWHITEBALANCE->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_SENSOR->AddSubItem(HANDLE_PSEYE_SENSOR_AUTOWHITEBALANCE);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PSEYE_SENSOR);

	//Create property.
	HANDLE_PSEYE_LINEAR = new CMFCPropertyGridProperty(L"���Բ���");
	//Set description.
	HANDLE_PSEYE_LINEAR->SetDescription(L"PSEye����ͷ�����Բ�����");

	{
		//Create property.
		HANDLE_PSEYE_LINEAR_ZOOM = new CMFCPropertyGridProperty(L"���ű���",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_ZOOM), L"PSEye����ͷ�����ű�����ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_LINEAR_ZOOM->Enable(TRUE);
		//Add subitem.
		HANDLE_PSEYE_LINEAR->AddSubItem(HANDLE_PSEYE_LINEAR_ZOOM);

		//Create property.
		HANDLE_PSEYE_LINEAR_ROTATION = new CMFCPropertyGridProperty(L"��ת�Ƕ�",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_ROTATION), L"PSEye����ͷ����ת�Ƕȡ�ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_LINEAR_ROTATION->Enable(TRUE);
		//Add subitem.
		HANDLE_PSEYE_LINEAR->AddSubItem(HANDLE_PSEYE_LINEAR_ROTATION);

		//Create property.
		HANDLE_PSEYE_LINEAR_XOFFSET = new CMFCPropertyGridProperty(L"Xƫ��",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_XOFFSET), L"PSEye����ͷ��Xƫ�ơ�ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_LINEAR_XOFFSET->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_LINEAR->AddSubItem(HANDLE_PSEYE_LINEAR_XOFFSET);

		//Create property.
		HANDLE_PSEYE_LINEAR_YOFFSET = new CMFCPropertyGridProperty(L"Yƫ��",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_YOFFSET), L"PSEye����ͷ��Yƫ�ơ�ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_LINEAR_YOFFSET->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_LINEAR->AddSubItem(HANDLE_PSEYE_LINEAR_YOFFSET);

		//Create property.
		HANDLE_PSEYE_LINEAR_HFLIP = new CMFCPropertyGridProperty(L"ˮƽ��",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_HFLIP), L"PSEye����ͷ��ˮƽ�ߡ�ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_LINEAR_HFLIP->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_LINEAR->AddSubItem(HANDLE_PSEYE_LINEAR_HFLIP);

		//Create property.
		HANDLE_PSEYE_LINEAR_VFLIP = new CMFCPropertyGridProperty(L"��ֱ��",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_HFLIP), L"PSEye����ͷ�Ĵ�ֱ�ߡ�ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_LINEAR_VFLIP->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_LINEAR->AddSubItem(HANDLE_PSEYE_LINEAR_VFLIP);

		//Create property.
		HANDLE_PSEYE_LINEAR_HKEYSTONE = new CMFCPropertyGridProperty(L"ˮƽ��׼",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_HKEYSTONE), L"PSEye����ͷ��ˮƽ��׼��ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_LINEAR_HKEYSTONE->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_LINEAR->AddSubItem(HANDLE_PSEYE_LINEAR_HKEYSTONE);

		//Create property.
		HANDLE_PSEYE_LINEAR_VKEYSTONE = new CMFCPropertyGridProperty(L"��ֱ��׼",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_VKEYSTONE), L"PSEye����ͷ�Ĵ�ֱ��׼��ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_LINEAR_VKEYSTONE->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_LINEAR->AddSubItem(HANDLE_PSEYE_LINEAR_VKEYSTONE);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PSEYE_LINEAR);

	//Create property.
	HANDLE_PSEYE_NONELINEAR = new CMFCPropertyGridProperty(L"�����Բ���");
	//Set description.
	HANDLE_PSEYE_NONELINEAR->SetDescription(L"PSEye����ͷ�ķ����Բ�����");

	{
		//Create property.
		HANDLE_PSEYE_NONELINEAR_LENSBRIGHTNESS = new CMFCPropertyGridProperty(L"��ͷ����",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_LENSBRIGHTNESS), L"PSEye����ͷ�ľ�ͷ���ȡ�ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_NONELINEAR_LENSBRIGHTNESS->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_NONELINEAR->AddSubItem(HANDLE_PSEYE_NONELINEAR_LENSBRIGHTNESS);

		//Create property.
		HANDLE_PSEYE_NONELINEAR_LENSCORRECTION1 = new CMFCPropertyGridProperty(L"��ͷУ��1",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_LENSCORRECTION1), L"PSEye����ͷ�ľ�ͷУ��1��ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_NONELINEAR_LENSCORRECTION1->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_NONELINEAR->AddSubItem(HANDLE_PSEYE_NONELINEAR_LENSCORRECTION1);

		//Create property.
		HANDLE_PSEYE_NONELINEAR_LENSCORRECTION2 = new CMFCPropertyGridProperty(L"��ͷУ��2",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_LENSCORRECTION2), L"PSEye����ͷ�ľ�ͷУ��2��ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_NONELINEAR_LENSCORRECTION2->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_NONELINEAR->AddSubItem(HANDLE_PSEYE_NONELINEAR_LENSCORRECTION2);

		//Create property.
		HANDLE_PSEYE_NONELINEAR_LENSCORRECTION3 = new CMFCPropertyGridProperty(L"��ͷУ��3",
			(_variant_t) pPSEyeDevice->getValue(CLEYE_LENSCORRECTION3), L"PSEye����ͷ�ľ�ͷУ��3��ȡֵ��Χ�ڣ�-500��+500��");
		//Disable it.
		HANDLE_PSEYE_NONELINEAR_LENSCORRECTION3->Enable(FALSE);
		//Add subitem.
		HANDLE_PSEYE_NONELINEAR->AddSubItem(HANDLE_PSEYE_NONELINEAR_LENSCORRECTION3);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PSEYE_NONELINEAR);
}
