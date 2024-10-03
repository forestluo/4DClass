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

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties.
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CD3DXRenderableObject* pRenderableObject)
{
#ifdef _DEBUG
	assert(pRenderableObject != NULL);
#endif

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"����");

	{
		//Create property.
		HANDLE_NAME = new CMFCPropertyGridProperty(L"����",
			pRenderableObject->getAlias().getCString(), L"�ɻ���������ڲ����ơ�");
		//Add item.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_OBJECT_TRANSFORM = new CMFCPropertyGridProperty(L"�任");
	//Set description.
	HANDLE_OBJECT_TRANSFORM->SetDescription(L"��ģ��ģ�ͱ任����������ϵ�£�����ʹ�õı任����");

	{
		//Get scale.
		C4DVector3 scale = pRenderableObject->getScale();

		//Create property.
		HANDLE_OBJECT_TRANSFORM_SCALE = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_OBJECT_TRANSFORM_SCALE->SetDescription(L"ģ��ģ������ʹ�õ����Ų�����");

		//Create property.
		HANDLE_OBJECT_TRANSFORM_SCALE_X = new CMFCPropertyGridProperty(L"x�����",
			(_variant_t) scale.x(), L"ģ��ģ����x�����ŵı���������");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_SCALE_X->Enable(pRenderableObject->isScalable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_SCALE->AddSubItem(HANDLE_OBJECT_TRANSFORM_SCALE_X);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_SCALE_Y = new CMFCPropertyGridProperty(L"y�����",
			(_variant_t) scale.y(), L"ģ��ģ����y�����ŵı���������");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_SCALE_Y->Enable(pRenderableObject->isScalable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_SCALE->AddSubItem(HANDLE_OBJECT_TRANSFORM_SCALE_Y);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_SCALE_Z = new CMFCPropertyGridProperty(L"z�����",
			(_variant_t) scale.z(), L"ģ��ģ����z�����ŵı���������");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_SCALE_Z->Enable(pRenderableObject->isScalable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_SCALE->AddSubItem(HANDLE_OBJECT_TRANSFORM_SCALE_Z);

		//Add item.
		HANDLE_OBJECT_TRANSFORM->AddSubItem(HANDLE_OBJECT_TRANSFORM_SCALE);
	}

	{
		//Get eular.
		C4DVector3 eular = pRenderableObject->getRotation().eular();
		//Adjust it.
		eular *= 180.0f / D3DX_PI;

		//Create property.
		HANDLE_OBJECT_TRANSFORM_ROTATE = new CMFCPropertyGridProperty(L"��ת");
		//Set description.
		HANDLE_OBJECT_TRANSFORM_ROTATE->SetDescription(L"ģ��ģ������ʹ�õ���ת������");

		//Create property.
		HANDLE_OBJECT_TRANSFORM_ROTATE_X = new CMFCPropertyGridProperty(L"��x��",
			(_variant_t) eular.x(), L"ģ��ģ����x����ת�ĽǶȲ�����");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_ROTATE_X->Enable(pRenderableObject->isRotatable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_ROTATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_ROTATE_X);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_ROTATE_Y = new CMFCPropertyGridProperty(L"��y��",
			(_variant_t) eular.y(), L"ģ��ģ����y����ת�ĽǶȲ�����");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_ROTATE_Y->Enable(pRenderableObject->isRotatable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_ROTATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_ROTATE_Y);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_ROTATE_Z = new CMFCPropertyGridProperty(L"��z��",
			(_variant_t) eular.z(), L"ģ��ģ����z����ת�ĽǶȲ�����");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_ROTATE_Z->Enable(pRenderableObject->isRotatable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_ROTATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_ROTATE_Z);

		//Add item.
		HANDLE_OBJECT_TRANSFORM->AddSubItem(HANDLE_OBJECT_TRANSFORM_ROTATE);
	}

	{
		//Get position.
		C4DVector3 position = pRenderableObject->getPosition();

		//Create property.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE = new CMFCPropertyGridProperty(L"ƽ��");
		//Set description.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE->SetDescription(L"ģ��ģ������ʹ�õ�ƽ�Ʋ�����");

		//Create property.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_X = new CMFCPropertyGridProperty(L"��x��",
			(_variant_t) position.x(), L"ģ��ģ����x��ƽ�Ƶľ��������");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_X->Enable(pRenderableObject->isMovable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_TRANSLATE_X);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y = new CMFCPropertyGridProperty(L"��y��",
			(_variant_t) position.y(), L"ģ��ģ����y��ƽ�Ƶľ��������");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y->Enable(pRenderableObject->isMovable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z = new CMFCPropertyGridProperty(L"��z��",
			(_variant_t) position.z(), L"ģ��ģ����z��ƽ�Ƶľ��������");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z->Enable(pRenderableObject->isMovable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z);

		//Add item.
		HANDLE_OBJECT_TRANSFORM->AddSubItem(HANDLE_OBJECT_TRANSFORM_TRANSLATE);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_OBJECT_TRANSFORM);

	//Create property.
	HANDLE_OBJECT_CONTROL = new CMFCPropertyGridProperty(L"����");
	//Set description.
	HANDLE_OBJECT_CONTROL->SetDescription(L"����������ϵ�£�ģ��ģ�Ϳɿ��Ʋ�����");

	{
		//Get value.
		bool bScalable = pRenderableObject->isScalable() ? true : false;
		//Create property.
		HANDLE_OBJECT_CONTROL_SCALABLE = new CMFCPropertyGridProperty(L"������",
			(_variant_t) bScalable, L"ģ��ģ���Ƿ�ɽ������ſ��ơ��������Ų������Ա༭��");
		//Check object.
		if(pRenderableObject->isJointObject() ||
			pRenderableObject->isCompoundObject())
		{
			//Disable it.
			HANDLE_OBJECT_CONTROL_SCALABLE->Enable(FALSE);
		}
		else
		{
			//Get top object.
			CWorldObject* pTopParent = (CWorldObject *)CWorldObject::getTopParent((CWorldObject *)pRenderableObject);
			//Check result.
			if(pTopParent != NULL && pTopParent->isJointObject()) HANDLE_OBJECT_CONTROL_SCALABLE->Enable(FALSE);
		}
		//Add item.
		HANDLE_OBJECT_CONTROL->AddSubItem(HANDLE_OBJECT_CONTROL_SCALABLE);

		//Get value.
		bool bRotatable = pRenderableObject->isRotatable() ? true : false;
		//Create property.
		HANDLE_OBJECT_CONTROL_ROTATABLE = new CMFCPropertyGridProperty(L"����ת",
			(_variant_t) bRotatable, L"ģ��ģ���Ƿ�ɽ�����ת���ơ�������ת�������Ա༭��");
		//Check object.
		if(pRenderableObject->isJointObject()) HANDLE_OBJECT_CONTROL_ROTATABLE->Enable(FALSE);
		else
		{
			//Get top object.
			CWorldObject* pTopParent = (CWorldObject *)CWorldObject::getTopParent((CWorldObject *)pRenderableObject);
			//Check result.
			if(pTopParent != NULL && pTopParent->isJointObject()) HANDLE_OBJECT_CONTROL_ROTATABLE->Enable(FALSE);
		}
		//Add item.
		HANDLE_OBJECT_CONTROL->AddSubItem(HANDLE_OBJECT_CONTROL_ROTATABLE);

		//Get value.
		bool bMovable = pRenderableObject->isMovable() ? true : false;
		//Create property.
		HANDLE_OBJECT_CONTROL_MOVABLE = new CMFCPropertyGridProperty(L"��ƽ��",
			(_variant_t) bMovable, L"ģ��ģ���Ƿ�ɽ���ƽ�ƿ��ơ�����ƽ�Ʋ������Ա༭��");
		//Check object.
		if(pRenderableObject->isJointObject()) HANDLE_OBJECT_CONTROL_MOVABLE->Enable(FALSE);
		else
		{
			//Get top object.
			CWorldObject* pTopParent = (CWorldObject *)CWorldObject::getTopParent((CWorldObject *)pRenderableObject);
			//Check result.
			if(pTopParent != NULL && pTopParent->isJointObject()) HANDLE_OBJECT_CONTROL_MOVABLE->Enable(FALSE);
		}
		//Add item.
		HANDLE_OBJECT_CONTROL->AddSubItem(HANDLE_OBJECT_CONTROL_MOVABLE);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_OBJECT_CONTROL);

	//Create property.
	HANDLE_GROUP_MISC = new CMFCPropertyGridProperty(L"����");

	{
		//Get sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();

		//Get value.
		bool bDrawPicked  = pSketcher != NULL ? true : false;
		//Create property.
		HANDLE_OBJECT_MISC_PICKED = new CMFCPropertyGridProperty(L"ѡ��",
			(_variant_t) bDrawPicked, L"�Ƿ�������屻ѡ�б�ǡ�");
		//Add item.
		HANDLE_GROUP_MISC->AddSubItem(HANDLE_OBJECT_MISC_PICKED);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MISC);
}
