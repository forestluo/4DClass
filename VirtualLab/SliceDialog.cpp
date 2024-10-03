// SliceDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "SliceDialog.h"
#include "afxdialogex.h"

#include "PrimitiveAttribute.h"

// CSliceDialog dialog

IMPLEMENT_DYNAMIC(CSliceDialog, CDialogEx)

CSliceDialog::CSliceDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSliceDialog::IDD, pParent)
	, m_fMass(1.0f)
	, m_fWidth(1.0f)
	, m_fLength(1.0f)
	, m_nXRotation(0)
	, m_nYRotation(0)
	, m_nZRotation(0)
	, m_fXPosition(0.0f)
	, m_fYPosition(2.0f)
	, m_fZPosition(0.0f)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CSliceDialog::~CSliceDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CSliceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MASS, m_fMass);
	DDV_MinMaxFloat(pDX, m_fMass, 0.0f, 10000.0f);

	DDX_Text(pDX, IDC_EDIT_WIDTH, m_fWidth);
	DDV_MinMaxFloat(pDX, m_fWidth, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_fLength);
	DDV_MinMaxFloat(pDX, m_fLength, 0.01f, 10.0f);

	DDX_Text(pDX, IDC_EDIT_XR, m_nXRotation);
	DDV_MinMaxInt(pDX, m_nXRotation, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR, m_nYRotation);
	DDV_MinMaxInt(pDX, m_nYRotation, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR, m_nZRotation);
	DDV_MinMaxInt(pDX, m_nZRotation, -360, 360);

	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0f, 500.0f);
}


BEGIN_MESSAGE_MAP(CSliceDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSliceDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CSliceDialog message handlers


void CSliceDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Set scale.
	C4DVector3 scale(m_fWidth,1.0f,m_fLength);
	//Set translate.
	C4DVector3 translate(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotate.
	C4DVector3 rotate(m_nXRotation / 180.0f * D3DX_PI,m_nYRotation / 180.0f * D3DX_PI,m_nZRotation / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL && m_pDoc->application != NULL);
#endif
	//Add slice into scene.
	m_pDoc->application->createModel(CPrimitiveAttribute::floor0Primitive,m_fMass,scale,rotate,translate);
}
