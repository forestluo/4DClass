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
// Definitions
//
///////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Primitive
const LPCTSTR PRIMITIVE_PROPERTIES[] =
{
	PROPERTY_GENERAL,
	PROPERTY_FENCE,
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXPrimitive* pPrimitive)
{
#ifdef _DEBUG
	assert(pPrimitive != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL) pDoc->application->setFocused(pPrimitive);
	}
	//Set selected property page.
	nSelectedPropertyPage = 0;
	//Set window text.
	SetWindowTextW(pPrimitive->getName().getCString());

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Remove all selections.
	m_wndObjectCombo.ResetContent();
	//Add properties.
	for(int i = 0;i < sizeof(PRIMITIVE_PROPERTIES) / sizeof(LPCTSTR);i ++)
	{
		//Add string.
		m_wndObjectCombo.AddString(PRIMITIVE_PROPERTIES[i]);
	}
	//Set current selection.
	m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);

	//Fill properties.
	FillProperties(pPrimitive);
}

///////////////////////////////////////////////////////////////////////////////
//
// ChangePropertyPage
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangePropertyPage(CD3DXPrimitive* pPrimitive,int nSelected)
{
#ifdef _DEBUG
	assert(pPrimitive != NULL);
#endif

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Check selected.
	if(nSelected == PROPERTY_GENERAL_SELECTION)
	{
		//Fill properties.
		FillProperties(pPrimitive);
	}
	else if(nSelected == PROPERTY_FENCE_SELECTION)
	{
		//Fill box properties.
		FillBoxProperties(pPrimitive);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CD3DXPrimitive* pPrimitive)
{
#ifdef _DEBUG
	assert(pPrimitive != NULL);
#endif

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"����");

	{
		//Create property.
		HANDLE_NAME = new CMFCPropertyGridProperty(L"����",
			pPrimitive->getName().getCString(), L"������������ڲ����ơ�");
		HANDLE_NAME->Enable(FALSE);
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"����������", L"������������ڲ����͡�");
		HANDLE_TYPE->Enable(FALSE);
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

		//Create property.
		HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"�����ô���",
			(_variant_t) pPrimitive->countReference(), L"���������屻���õĴ�����");
		HANDLE_REFERENCED_COUNT->Enable(FALSE);
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_GROUP_PARAMETER = new CMFCPropertyGridProperty(L"����");

	//Basic
	{
		//Create property.
		HANDLE_PRIMITIVE_BASIC = new CMFCPropertyGridProperty(L"����");
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_PRIMITIVE_BASIC);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_SEGMENT_COUNT = new CMFCPropertyGridProperty(L"�ֶ���",
			(_variant_t) pPrimitive->getSegmentsCount(), L"����������ķֶ�����Segment Count����ע�����������������ɢ��ʽ�����������˲���Ϊ������������ɢ�ֶ��������Ϊ1�������δ�ڴ˻����Ͻ�����ɢ����");
		HANDLE_PRIMITIVE_BASIC_SEGMENT_COUNT->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_SEGMENT_COUNT);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_RING_COUNT = new CMFCPropertyGridProperty(L"�ֻ���",
			(_variant_t) pPrimitive->getRingsCount(), L"����������ķֻ�����Ring Count����ע�����������������ɢ��ʽ�����������˲���Ϊ������������ɢ�ֻ��������Ϊ1�������δ�ڴ˻����Ͻ�����ɢ����");
		HANDLE_PRIMITIVE_BASIC_RING_COUNT->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_RING_COUNT);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_VERTEX_COUNT = new CMFCPropertyGridProperty(L"������",
			(_variant_t) pPrimitive->getVertexCount(), L"����������Ķ�������Vertex Count����");
		HANDLE_PRIMITIVE_BASIC_VERTEX_COUNT->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_VERTEX_COUNT);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_INDEX_COUNT = new CMFCPropertyGridProperty(L"������",
			(_variant_t) pPrimitive->getIndexCount(), L"�������������������Index Count����");
		HANDLE_PRIMITIVE_BASIC_INDEX_COUNT->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_INDEX_COUNT);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_VERTEX_SIZE = new CMFCPropertyGridProperty(L"�����С���ֽڣ�",
			(_variant_t) pPrimitive->getVertexSize(), L"���������嶥���������ڴ�ռ�ô�С���ֽڣ���");
		HANDLE_PRIMITIVE_BASIC_VERTEX_SIZE->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_VERTEX_SIZE);

		//Expand all.
		HANDLE_PRIMITIVE_BASIC->Expand(TRUE);
	}	

	//Geometry
	{
		//Get geometry.
		CPrimitiveAttribute attribute = pPrimitive->getPrimitiveAttribute();

		//Create property.
		HANDLE_PRIMITIVE_GEOMETRY = new CMFCPropertyGridProperty(L"������");
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY);

		if(attribute.getType() == CPrimitiveAttribute::cone0Primitive ||
			attribute.getType() == CPrimitiveAttribute::cone3Primitive ||
			attribute.getType() == CPrimitiveAttribute::cone4Primitive ||
			attribute.getType() == CPrimitiveAttribute::cone6Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("׶��"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"����߶�",
				(_variant_t) attribute.primitiveData.cone.height, L"׶�������߶ȡ�ע���߶ȶ���ƽ����y�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"����뾶",
				(_variant_t) attribute.primitiveData.cone.radius, L"׶��ĵ���뾶��ע�����涨��ƽ����xzƽ�档");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::cuboid0Primitive ||
				attribute.getType() == CPrimitiveAttribute::floor0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("������"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"�߶�",
				(_variant_t) attribute.primitiveData.cuboid.height, L"������ĸ߶ȡ�ע���߶ȶ���ƽ����y�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_WIDTH = new CMFCPropertyGridProperty(L"���",
				(_variant_t) attribute.primitiveData.cuboid.width, L"������Ŀ�ȡ�ע����ȶ���ƽ����x�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_WIDTH->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_WIDTH);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_DEPTH = new CMFCPropertyGridProperty(L"���",
				(_variant_t) attribute.primitiveData.cuboid.depth, L"���������ȡ�ע����ȶ���ƽ����z�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_DEPTH->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_DEPTH);
		}
		else if(attribute.getType() == CPrimitiveAttribute::grid4x3Primitive ||
				attribute.getType() == CPrimitiveAttribute::grid20x15Primitive ||
				attribute.getType() == CPrimitiveAttribute::ground80x60Primitive ||
				attribute.getType() == CPrimitiveAttribute::ground320x240Primitive ||
				attribute.getType() == CPrimitiveAttribute::ground640x480Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("������"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"��Ԫ�߶�",
				(_variant_t) attribute.primitiveData.grid.quadHeight, L"������ĵ�λ�߶ȡ�ע���߶ȶ���ƽ����y�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_WIDTH = new CMFCPropertyGridProperty(L"��Ԫ���",
				(_variant_t) attribute.primitiveData.grid.quadWidth, L"����Ԫ��Ŀ�ȡ�ע����ȶ���ƽ����x�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_WIDTH->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_WIDTH);
		}
		else if(attribute.getType() == CPrimitiveAttribute::frustum0Primitive ||
				attribute.getType() == CPrimitiveAttribute::frustum3Primitive ||
				attribute.getType() == CPrimitiveAttribute::frustum4Primitive ||
				attribute.getType() == CPrimitiveAttribute::frustum6Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("̨��"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"����߶�",
				(_variant_t) attribute.primitiveData.frustum.height, L"̨�������߶ȡ�ע���߶ȶ���ƽ����y�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS1 = new CMFCPropertyGridProperty(L"����뾶",
				(_variant_t) attribute.primitiveData.frustum.topRadius, L"̨��Ķ���뾶��ע�����涨��ƽ����xzƽ�档");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS1->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS1);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS2 = new CMFCPropertyGridProperty(L"����뾶",
				(_variant_t) attribute.primitiveData.frustum.bottomRadius, L"̨��ĵ���뾶��ע�����涨��ƽ����xzƽ�档");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS2->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS2);
		}
		else if(attribute.getType() == CPrimitiveAttribute::cylinder0Primitive ||
				attribute.getType() == CPrimitiveAttribute::cylinder3Primitive ||
				attribute.getType() == CPrimitiveAttribute::cylinder5Primitive ||
				attribute.getType() == CPrimitiveAttribute::cylinder6Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("����"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"����߶�",
				(_variant_t) attribute.primitiveData.cylinder.height, L"���������߶ȡ�ע���߶ȵĶ���ƽ����y�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"����뾶",
				(_variant_t) attribute.primitiveData.cylinder.radius, L"����ĵ���뾶��ע�����涨��ƽ����xzƽ�档");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::chamferCylider0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("Բ����"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"����߶�",
				(_variant_t) attribute.primitiveData.chamferCylinder.height, L"Բ���������߶ȡ�ע���߶ȵĶ���ƽ����y�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"����뾶",
				(_variant_t) attribute.primitiveData.chamferCylinder.radius, L"Բ���������뾶��ע�����涨��ƽ����xzƽ�档");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::sphere0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("����"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"����뾶",
				(_variant_t) attribute.primitiveData.sphere.radius, L"����İ뾶��");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::circle0Primitive ||
				attribute.getType() == CPrimitiveAttribute::circle3Primitive ||
				attribute.getType() == CPrimitiveAttribute::circle4Primitive ||
				attribute.getType() == CPrimitiveAttribute::circle5Primitive ||
				attribute.getType() == CPrimitiveAttribute::circle6Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("Բ��"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"Բ��뾶",
				(_variant_t) attribute.primitiveData.circle.radius, L"Բ��İ뾶��");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::hemisphere0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("������"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"����뾶",
				(_variant_t) attribute.primitiveData.hemisphere.radius, L"����İ뾶��");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::capsule0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("������"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"����߶�",
				(_variant_t) attribute.primitiveData.capsule.height, L"�����������߶ȡ�ע���߶ȵĶ���ƽ����y�ᡣ");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"����뾶",
				(_variant_t) attribute.primitiveData.capsule.radius, L"�����嶥������İ뾶��");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::triangle0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("������"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Vertex A
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1 = new CMFCPropertyGridProperty(L"����A");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) attribute.primitiveData.triangle.a[0], L"�����ζ���A��x����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) attribute.primitiveData.triangle.a[1], L"�����ζ���A��y����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) attribute.primitiveData.triangle.a[2], L"�����ζ���A��z����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Z->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Z);
			}

			//Vertex B
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2 = new CMFCPropertyGridProperty(L"����B");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) attribute.primitiveData.triangle.b[0], L"�����ζ���B��x����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) attribute.primitiveData.triangle.b[1], L"�����ζ���B��y����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) attribute.primitiveData.triangle.b[2], L"�����ζ���B��z����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Z->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Z);
			}

			//Vertex C
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3 = new CMFCPropertyGridProperty(L"����C");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) attribute.primitiveData.triangle.c[0], L"�����ζ���C��x����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) attribute.primitiveData.triangle.c[1], L"�����ζ���C��y����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) attribute.primitiveData.triangle.c[2], L"�����ζ���C��z����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Z->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Z);
			}
		}
		else if(attribute.getType() == CPrimitiveAttribute::quadrangle0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"����",
				(_variant_t) _T("�ı���"), L"�����������������͡�");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Vertex A
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1 = new CMFCPropertyGridProperty(L"����A");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) attribute.primitiveData.quadrangle.a[0], L"�ı��ζ���A��x����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) attribute.primitiveData.quadrangle.a[1], L"�ı��ζ���A��y����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y);
			}

			//Vertex B
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2 = new CMFCPropertyGridProperty(L"����B");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) attribute.primitiveData.quadrangle.b[0], L"�ı��ζ���B��x����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) attribute.primitiveData.quadrangle.b[1], L"�ı��ζ���B��y����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y);
			}

			//Vertex C
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3 = new CMFCPropertyGridProperty(L"����C");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) attribute.primitiveData.quadrangle.c[0], L"�ı��ζ���C��x����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) attribute.primitiveData.quadrangle.c[1], L"�ı��ζ���C��y����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y);
			}

			//Vertex D
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4 = new CMFCPropertyGridProperty(L"����D");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX4);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) attribute.primitiveData.quadrangle.c[0], L"�ı��ζ���D��x����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) attribute.primitiveData.quadrangle.c[1], L"�ı��ζ���D��y����ֵ��");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_Y);
			}
		}

		//Expand all.
		HANDLE_PRIMITIVE_GEOMETRY->Expand(TRUE);
	}	

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_PARAMETER);
}
