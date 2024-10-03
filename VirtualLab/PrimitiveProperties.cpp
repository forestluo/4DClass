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
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"常规");

	{
		//Create property.
		HANDLE_NAME = new CMFCPropertyGridProperty(L"名称",
			pPrimitive->getName().getCString(), L"基本几何体的内部名称。");
		HANDLE_NAME->Enable(FALSE);
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"类型",
			L"基本几何体", L"基本几何体的内部类型。");
		HANDLE_TYPE->Enable(FALSE);
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

		//Create property.
		HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"被引用次数",
			(_variant_t) pPrimitive->countReference(), L"基本几何体被引用的次数。");
		HANDLE_REFERENCED_COUNT->Enable(FALSE);
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_GROUP_PARAMETER = new CMFCPropertyGridProperty(L"参数");

	//Basic
	{
		//Create property.
		HANDLE_PRIMITIVE_BASIC = new CMFCPropertyGridProperty(L"基本");
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_PRIMITIVE_BASIC);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_SEGMENT_COUNT = new CMFCPropertyGridProperty(L"分段数",
			(_variant_t) pPrimitive->getSegmentsCount(), L"基本几何体的分段数（Segment Count）。注：基本几何体均用离散方式进行描述。此参数为基本几何体离散分段数。如果为1，则表明未在此环节上进行离散处理。");
		HANDLE_PRIMITIVE_BASIC_SEGMENT_COUNT->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_SEGMENT_COUNT);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_RING_COUNT = new CMFCPropertyGridProperty(L"分环数",
			(_variant_t) pPrimitive->getRingsCount(), L"基本几何体的分环数（Ring Count）。注：基本几何体均用离散方式进行描述。此参数为基本几何体离散分环数。如果为1，则表明未在此环节上进行离散处理。");
		HANDLE_PRIMITIVE_BASIC_RING_COUNT->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_RING_COUNT);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_VERTEX_COUNT = new CMFCPropertyGridProperty(L"顶点数",
			(_variant_t) pPrimitive->getVertexCount(), L"基本几何体的顶点数（Vertex Count）。");
		HANDLE_PRIMITIVE_BASIC_VERTEX_COUNT->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_VERTEX_COUNT);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_INDEX_COUNT = new CMFCPropertyGridProperty(L"索引数",
			(_variant_t) pPrimitive->getIndexCount(), L"基本几何体的索引数（Index Count）。");
		HANDLE_PRIMITIVE_BASIC_INDEX_COUNT->Enable(FALSE);
		HANDLE_PRIMITIVE_BASIC->AddSubItem(HANDLE_PRIMITIVE_BASIC_INDEX_COUNT);

		//Create property.
		HANDLE_PRIMITIVE_BASIC_VERTEX_SIZE = new CMFCPropertyGridProperty(L"顶点大小（字节）",
			(_variant_t) pPrimitive->getVertexSize(), L"基本几何体顶点描述的内存占用大小（字节）。");
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
		HANDLE_PRIMITIVE_GEOMETRY = new CMFCPropertyGridProperty(L"几何体");
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY);

		if(attribute.getType() == CPrimitiveAttribute::cone0Primitive ||
			attribute.getType() == CPrimitiveAttribute::cone3Primitive ||
			attribute.getType() == CPrimitiveAttribute::cone4Primitive ||
			attribute.getType() == CPrimitiveAttribute::cone6Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("锥体"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"整体高度",
				(_variant_t) attribute.primitiveData.cone.height, L"锥体的整体高度。注：高度定义平行于y轴。");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"底面半径",
				(_variant_t) attribute.primitiveData.cone.radius, L"锥体的底面半径。注：底面定义平行于xz平面。");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::cuboid0Primitive ||
				attribute.getType() == CPrimitiveAttribute::floor0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("矩形体"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"高度",
				(_variant_t) attribute.primitiveData.cuboid.height, L"矩形体的高度。注：高度定义平行于y轴。");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_WIDTH = new CMFCPropertyGridProperty(L"宽度",
				(_variant_t) attribute.primitiveData.cuboid.width, L"矩形体的宽度。注：宽度定义平行于x轴。");
			HANDLE_PRIMITIVE_GEOMETRY_WIDTH->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_WIDTH);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_DEPTH = new CMFCPropertyGridProperty(L"深度",
				(_variant_t) attribute.primitiveData.cuboid.depth, L"矩形体的深度。注：深度定义平行于z轴。");
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
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("网格面"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"单元高度",
				(_variant_t) attribute.primitiveData.grid.quadHeight, L"网格面的单位高度。注：高度定义平行于y轴。");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_WIDTH = new CMFCPropertyGridProperty(L"单元宽度",
				(_variant_t) attribute.primitiveData.grid.quadWidth, L"网格单元面的宽度。注：宽度定义平行于x轴。");
			HANDLE_PRIMITIVE_GEOMETRY_WIDTH->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_WIDTH);
		}
		else if(attribute.getType() == CPrimitiveAttribute::frustum0Primitive ||
				attribute.getType() == CPrimitiveAttribute::frustum3Primitive ||
				attribute.getType() == CPrimitiveAttribute::frustum4Primitive ||
				attribute.getType() == CPrimitiveAttribute::frustum6Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("台体"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"整体高度",
				(_variant_t) attribute.primitiveData.frustum.height, L"台体的整体高度。注：高度定义平行于y轴。");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS1 = new CMFCPropertyGridProperty(L"顶面半径",
				(_variant_t) attribute.primitiveData.frustum.topRadius, L"台体的顶面半径。注：顶面定义平行于xz平面。");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS1->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS1);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS2 = new CMFCPropertyGridProperty(L"地面半径",
				(_variant_t) attribute.primitiveData.frustum.bottomRadius, L"台体的地面半径。注：底面定义平行于xz平面。");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS2->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS2);
		}
		else if(attribute.getType() == CPrimitiveAttribute::cylinder0Primitive ||
				attribute.getType() == CPrimitiveAttribute::cylinder3Primitive ||
				attribute.getType() == CPrimitiveAttribute::cylinder5Primitive ||
				attribute.getType() == CPrimitiveAttribute::cylinder6Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("柱体"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"整体高度",
				(_variant_t) attribute.primitiveData.cylinder.height, L"柱体的整体高度。注：高度的定义平行于y轴。");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"底面半径",
				(_variant_t) attribute.primitiveData.cylinder.radius, L"柱体的底面半径。注：底面定义平行于xz平面。");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::chamferCylider0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("圆饼体"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"整体高度",
				(_variant_t) attribute.primitiveData.chamferCylinder.height, L"圆饼体的整体高度。注：高度的定义平行于y轴。");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"地面半径",
				(_variant_t) attribute.primitiveData.chamferCylinder.radius, L"圆饼体的整体半径。注：底面定义平行于xz平面。");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::sphere0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("球体"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"球体半径",
				(_variant_t) attribute.primitiveData.sphere.radius, L"球体的半径。");
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
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("圆面"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"圆面半径",
				(_variant_t) attribute.primitiveData.circle.radius, L"圆面的半径。");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::hemisphere0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("半球体"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"球体半径",
				(_variant_t) attribute.primitiveData.hemisphere.radius, L"球体的半径。");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::capsule0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("胶囊体"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT = new CMFCPropertyGridProperty(L"柱体高度",
				(_variant_t) attribute.primitiveData.capsule.height, L"胶囊体的柱体高度。注：高度的定义平行于y轴。");
			HANDLE_PRIMITIVE_GEOMETRY_HEIGHT->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_HEIGHT);

			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS = new CMFCPropertyGridProperty(L"球体半径",
				(_variant_t) attribute.primitiveData.capsule.radius, L"胶囊体顶端球体的半径。");
			HANDLE_PRIMITIVE_GEOMETRY_RADIUS->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_RADIUS);
		}
		else if(attribute.getType() == CPrimitiveAttribute::triangle0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("三角形"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Vertex A
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1 = new CMFCPropertyGridProperty(L"顶点A");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) attribute.primitiveData.triangle.a[0], L"三角形顶点A的x坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) attribute.primitiveData.triangle.a[1], L"三角形顶点A的y坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Z = new CMFCPropertyGridProperty(L"z坐标",
					(_variant_t) attribute.primitiveData.triangle.a[2], L"三角形顶点A的z坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Z->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Z);
			}

			//Vertex B
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2 = new CMFCPropertyGridProperty(L"顶点B");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) attribute.primitiveData.triangle.b[0], L"三角形顶点B的x坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) attribute.primitiveData.triangle.b[1], L"三角形顶点B的y坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Z = new CMFCPropertyGridProperty(L"z坐标",
					(_variant_t) attribute.primitiveData.triangle.b[2], L"三角形顶点B的z坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Z->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Z);
			}

			//Vertex C
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3 = new CMFCPropertyGridProperty(L"顶点C");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) attribute.primitiveData.triangle.c[0], L"三角形顶点C的x坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) attribute.primitiveData.triangle.c[1], L"三角形顶点C的y坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Z = new CMFCPropertyGridProperty(L"z坐标",
					(_variant_t) attribute.primitiveData.triangle.c[2], L"三角形顶点C的z坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Z->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Z);
			}
		}
		else if(attribute.getType() == CPrimitiveAttribute::quadrangle0Primitive)
		{
			//Create property.
			HANDLE_PRIMITIVE_GEOMETRY_TYPE = new CMFCPropertyGridProperty(L"类型",
				(_variant_t) _T("四边形"), L"基本几何体所属类型。");
			HANDLE_PRIMITIVE_GEOMETRY_TYPE->Enable(FALSE);
			HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_TYPE);

			//Vertex A
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1 = new CMFCPropertyGridProperty(L"顶点A");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) attribute.primitiveData.quadrangle.a[0], L"四边形顶点A的x坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) attribute.primitiveData.quadrangle.a[1], L"四边形顶点A的y坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX1->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX1_Y);
			}

			//Vertex B
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2 = new CMFCPropertyGridProperty(L"顶点B");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) attribute.primitiveData.quadrangle.b[0], L"四边形顶点B的x坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) attribute.primitiveData.quadrangle.b[1], L"四边形顶点B的y坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX2->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX2_Y);
			}

			//Vertex C
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3 = new CMFCPropertyGridProperty(L"顶点C");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) attribute.primitiveData.quadrangle.c[0], L"四边形顶点C的x坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) attribute.primitiveData.quadrangle.c[1], L"四边形顶点C的y坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX3->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX3_Y);
			}

			//Vertex D
			{
				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4 = new CMFCPropertyGridProperty(L"顶点D");
				HANDLE_PRIMITIVE_GEOMETRY->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX4);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) attribute.primitiveData.quadrangle.c[0], L"四边形顶点D的x坐标值。");
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_X->Enable(FALSE);
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4->AddSubItem(HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_X);

				//Create property.
				HANDLE_PRIMITIVE_GEOMETRY_VERTEX4_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) attribute.primitiveData.quadrangle.c[1], L"四边形顶点D的y坐标值。");
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
