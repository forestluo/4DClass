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
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"常规");

	{
		//Create property.
		HANDLE_NAME = new CMFCPropertyGridProperty(L"名称",
			pRenderableObject->getAlias().getCString(), L"可绘制物体的内部名称。");
		//Add item.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_OBJECT_TRANSFORM = new CMFCPropertyGridProperty(L"变换");
	//Set description.
	HANDLE_OBJECT_TRANSFORM->SetDescription(L"将模板模型变换至世界坐标系下，所需使用的变换矩阵。");

	{
		//Get scale.
		C4DVector3 scale = pRenderableObject->getScale();

		//Create property.
		HANDLE_OBJECT_TRANSFORM_SCALE = new CMFCPropertyGridProperty(L"缩放");
		//Set description.
		HANDLE_OBJECT_TRANSFORM_SCALE->SetDescription(L"模板模型所需使用的缩放参数。");

		//Create property.
		HANDLE_OBJECT_TRANSFORM_SCALE_X = new CMFCPropertyGridProperty(L"x轴比例",
			(_variant_t) scale.x(), L"模板模型沿x轴缩放的比例参数。");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_SCALE_X->Enable(pRenderableObject->isScalable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_SCALE->AddSubItem(HANDLE_OBJECT_TRANSFORM_SCALE_X);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_SCALE_Y = new CMFCPropertyGridProperty(L"y轴比例",
			(_variant_t) scale.y(), L"模板模型沿y轴缩放的比例参数。");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_SCALE_Y->Enable(pRenderableObject->isScalable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_SCALE->AddSubItem(HANDLE_OBJECT_TRANSFORM_SCALE_Y);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_SCALE_Z = new CMFCPropertyGridProperty(L"z轴比例",
			(_variant_t) scale.z(), L"模板模型沿z轴缩放的比例参数。");
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
		HANDLE_OBJECT_TRANSFORM_ROTATE = new CMFCPropertyGridProperty(L"旋转");
		//Set description.
		HANDLE_OBJECT_TRANSFORM_ROTATE->SetDescription(L"模板模型所需使用的旋转参数。");

		//Create property.
		HANDLE_OBJECT_TRANSFORM_ROTATE_X = new CMFCPropertyGridProperty(L"绕x轴",
			(_variant_t) eular.x(), L"模板模型绕x轴旋转的角度参数。");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_ROTATE_X->Enable(pRenderableObject->isRotatable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_ROTATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_ROTATE_X);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_ROTATE_Y = new CMFCPropertyGridProperty(L"绕y轴",
			(_variant_t) eular.y(), L"模板模型绕y轴旋转的角度参数。");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_ROTATE_Y->Enable(pRenderableObject->isRotatable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_ROTATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_ROTATE_Y);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_ROTATE_Z = new CMFCPropertyGridProperty(L"绕z轴",
			(_variant_t) eular.z(), L"模板模型绕z轴旋转的角度参数。");
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
		HANDLE_OBJECT_TRANSFORM_TRANSLATE = new CMFCPropertyGridProperty(L"平移");
		//Set description.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE->SetDescription(L"模板模型所需使用的平移参数。");

		//Create property.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_X = new CMFCPropertyGridProperty(L"沿x轴",
			(_variant_t) position.x(), L"模板模型沿x轴平移的距离参数。");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_X->Enable(pRenderableObject->isMovable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_TRANSLATE_X);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y = new CMFCPropertyGridProperty(L"沿y轴",
			(_variant_t) position.y(), L"模板模型沿y轴平移的距离参数。");
		//Set enabled.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y->Enable(pRenderableObject->isMovable());
		//Add subitem.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE->AddSubItem(HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y);

		//Create property.
		HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z = new CMFCPropertyGridProperty(L"沿z轴",
			(_variant_t) position.z(), L"模板模型沿z轴平移的距离参数。");
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
	HANDLE_OBJECT_CONTROL = new CMFCPropertyGridProperty(L"控制");
	//Set description.
	HANDLE_OBJECT_CONTROL->SetDescription(L"在世界坐标系下，模板模型可控制参数。");

	{
		//Get value.
		bool bScalable = pRenderableObject->isScalable() ? true : false;
		//Create property.
		HANDLE_OBJECT_CONTROL_SCALABLE = new CMFCPropertyGridProperty(L"可缩放",
			(_variant_t) bScalable, L"模板模型是否可进行缩放控制。即：缩放参数可以编辑。");
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
		HANDLE_OBJECT_CONTROL_ROTATABLE = new CMFCPropertyGridProperty(L"可旋转",
			(_variant_t) bRotatable, L"模板模型是否可进行旋转控制。即：旋转参数可以编辑。");
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
		HANDLE_OBJECT_CONTROL_MOVABLE = new CMFCPropertyGridProperty(L"可平移",
			(_variant_t) bMovable, L"模板模型是否可进行平移控制。即：平移参数可以编辑。");
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
	HANDLE_GROUP_MISC = new CMFCPropertyGridProperty(L"其他");

	{
		//Get sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();

		//Get value.
		bool bDrawPicked  = pSketcher != NULL ? true : false;
		//Create property.
		HANDLE_OBJECT_MISC_PICKED = new CMFCPropertyGridProperty(L"选中",
			(_variant_t) bDrawPicked, L"是否绘制物体被选中标记。");
		//Add item.
		HANDLE_GROUP_MISC->AddSubItem(HANDLE_OBJECT_MISC_PICKED);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MISC);
}
