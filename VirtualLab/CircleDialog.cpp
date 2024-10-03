// CircleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "CircleDialog.h"
#include "afxdialogex.h"


// CCircleDialog dialog

IMPLEMENT_DYNAMIC(CCircleDialog, CDialogEx)

	CCircleDialog::CCircleDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCircleDialog::IDD, pParent)
	, m_fRadius(0.2f)
	, m_nXRotate(90)
	, m_nYRotate(0)
	, m_nZRotate(0)
	, m_fXPosition(0.0f)
	, m_fYPosition(2.0f)
	, m_fZPosition(0.0f)
{
	//No one was selected.
	m_nType = 0;

#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CCircleDialog::~CCircleDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CCircleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_POLYGON, m_polygon);

	DDX_Text(pDX, IDC_EDIT_RADIUS, m_fRadius);
	DDV_MinMaxFloat(pDX, m_fRadius, 0.01f, 10.0f);

	DDX_Text(pDX, IDC_EDIT_XR, m_nXRotate);
	DDV_MinMaxInt(pDX, m_nXRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR, m_nYRotate);
	DDV_MinMaxInt(pDX, m_nYRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR, m_nZRotate);
	DDV_MinMaxInt(pDX, m_nZRotate, -360, 360);

	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0f, 500.0f);
}


BEGIN_MESSAGE_MAP(CCircleDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCircleDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCircleDialog message handlers


void CCircleDialog::OnBnClickedOk()
{
	//Update data.
	UpdateData(TRUE);

	//Get current selection.
	int nSelection = m_polygon.GetCurSel();
	//Get selection.
	switch(nSelection)
	{
	case 0:
		m_nType = CPrimitiveAttribute::circle0Primitive;
		break;
	case 1:
		m_nType = CPrimitiveAttribute::circle3Primitive;
		break;
	case 2:
		m_nType = CPrimitiveAttribute::circle4Primitive;
		break;
	case 3:
		m_nType = CPrimitiveAttribute::circle5Primitive;
		break;
	case 4:
		m_nType = CPrimitiveAttribute::circle6Primitive;
		break;
	default:
		m_nType = 0;
		//Show message.
		AfxMessageBox(_T("没有定义多边形！\n\n请选择并确定多边形。"), MB_OK | MB_ICONSTOP);
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Set scale.
	C4DVector3 scale(m_fRadius,m_fRadius,m_fRadius);
	//Set position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotate.
	C4DVector3 rotation(m_nXRotate / 180.0f * D3DX_PI,m_nYRotate / 180.0f * D3DX_PI,m_nZRotate / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Check type.
	if(m_nType == CPrimitiveAttribute::circle0Primitive ||
		m_nType == CPrimitiveAttribute::circle3Primitive ||
		m_nType == CPrimitiveAttribute::circle4Primitive ||
		m_nType == CPrimitiveAttribute::circle5Primitive ||
		m_nType == CPrimitiveAttribute::circle6Primitive)
	{
		//Create model.	
		m_pDoc->application->createModel(m_nType,0.0f,scale,rotation,position);
	}
}
