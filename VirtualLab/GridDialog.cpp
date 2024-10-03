// GridDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "GridDialog.h"
#include "afxdialogex.h"


// CGridDialog dialog

IMPLEMENT_DYNAMIC(CGridDialog, CDialogEx)

	CGridDialog::CGridDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CGridDialog::IDD, pParent)
	, m_fQuadWidth(1.0f)
	, m_fQuadHeight(0.001f)
	, m_nXRotate(0)
	, m_nYRotate(0)
	, m_nZRotate(0)
	, m_fXPosition(0.0f)
	, m_fYPosition(0.0f)
	, m_fZPosition(0.0f)
{
	//Set type.
	m_nType = 0;

#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	m_pDoc = pDoc;
}

CGridDialog::~CGridDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CGridDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_LENGTH, m_fQuadWidth);
	DDV_MinMaxFloat(pDX, m_fQuadWidth, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_fQuadHeight);
	DDV_MinMaxFloat(pDX, m_fQuadHeight, 0.001f, 1.0f);

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
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_resolution);
}


BEGIN_MESSAGE_MAP(CGridDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGridDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CGridDialog message handlers


void CGridDialog::OnBnClickedOk()
{
	//Update data.
	UpdateData(TRUE);

	//Get current selection.
	int nSelection = m_resolution.GetCurSel();
	//Get selection.
	switch(nSelection)
	{
	case 0:
		m_nType = CPrimitiveAttribute::grid4x3Primitive;
		break;
	case 1:
		m_nType = CPrimitiveAttribute::grid20x15Primitive;
		break;
	case 2:
		m_nType = CPrimitiveAttribute::ground80x60Primitive;
		break;
	case 3:
		m_nType = CPrimitiveAttribute::ground320x240Primitive;
		break;
	case 4:
		m_nType = CPrimitiveAttribute::ground640x480Primitive;
		break;
	default:
		//Show message.
		AfxMessageBox(_T("没有定义分辨率！\n\n请选择并确定分辨率。"), MB_OK | MB_ICONSTOP);
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Attribute.
	CPrimitiveAttribute attribute;
	//Set type.
	attribute.setType(m_nType);
	//Set width
	attribute.primitiveData.grid.quadWidth = m_fQuadWidth;
	//Set height.
	attribute.primitiveData.grid.quadHeight = m_fQuadHeight;

	//Set scale.
	C4DVector3 scale(1.0f,1.0f,1.0f);
	//Set position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotation.
	C4DVector3 rotation(m_nXRotate / 180.0f * D3DX_PI,m_nYRotate / 180.0f * D3DX_PI,m_nZRotate / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add cuboid into scene.
	m_pDoc->application->createModel(attribute,0.0f,scale,rotation,position);
}
