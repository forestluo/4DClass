// CompoundBoxDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "CompoundBoxDialog.h"
#include "afxdialogex.h"

#include "CompoundBoxObject.h"

// CCompoundBoxDialog dialog

IMPLEMENT_DYNAMIC(CCompoundBoxDialog, CDialogEx)

	CCompoundBoxDialog::CCompoundBoxDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompoundBoxDialog::IDD, pParent)
	, m_fMass(1.0f)
	, m_fLength(1.0f)
	, m_fHeight(1.0f)
	, m_fDepth(1.0f)
	, m_nXRotate(0)
	, m_nYRotate(0)
	, m_nZRotate(0)
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

CCompoundBoxDialog::~CCompoundBoxDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CCompoundBoxDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MASS, m_fMass);
	DDV_MinMaxFloat(pDX, m_fMass, 0.0f, 10000.0f);

	DDX_Text(pDX, IDC_EDIT_LENGTH, m_fLength);
	DDV_MinMaxFloat(pDX, m_fLength, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_fHeight);
	DDV_MinMaxFloat(pDX, m_fHeight, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_DEPTH, m_fDepth);
	DDV_MinMaxFloat(pDX, m_fDepth, 0.01f, 10.0f);

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


BEGIN_MESSAGE_MAP(CCompoundBoxDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCompoundBoxDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCompoundBoxDialog message handlers


void CCompoundBoxDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Set scaling.
	C4DVector3 scaling(1.0f,1.0f,1.0f);
	//Set position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotate.
	C4DVector3 rotation(m_nXRotate / 180.0f * D3DX_PI,m_nYRotate / 180.0f * D3DX_PI,m_nZRotate / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Create compound.
	m_pDoc->application->createCompound(CCompoundBoxObject::getClassCode(),m_fMass,scaling,rotation,position);
}
