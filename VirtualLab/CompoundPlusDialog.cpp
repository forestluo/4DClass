// CompoundPlusDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "CompoundPlusDialog.h"
#include "afxdialogex.h"

#include "CompoundPlusObject.h"

// CCompoundPlusDialog dialog

IMPLEMENT_DYNAMIC(CCompoundPlusDialog, CDialogEx)

	CCompoundPlusDialog::CCompoundPlusDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompoundPlusDialog::IDD, pParent)
	, m_fMass(1.0f)
	, m_fXLength(1.0f)
	, m_fYLength(1.0f)
	, m_fWidth(0.2f)
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

CCompoundPlusDialog::~CCompoundPlusDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CCompoundPlusDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MASS, m_fMass);
	DDV_MinMaxFloat(pDX, m_fMass, 0.0f, 10000.0f);

	DDX_Text(pDX, IDC_EDIT_LENGTH_X, m_fXLength);
	DDV_MinMaxFloat(pDX, m_fXLength, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_LENGTH_Y, m_fYLength);
	DDV_MinMaxFloat(pDX, m_fYLength, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_fWidth);
	DDV_MinMaxFloat(pDX, m_fWidth, 0.01f, 10.0f);

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


BEGIN_MESSAGE_MAP(CCompoundPlusDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCompoundPlusDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCompoundPlusDialog message handlers


void CCompoundPlusDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Set scale.
	C4DVector3 scaling(1.0f,1.0f,1.0f);
	//Set position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotate.
	C4DVector3 rotation(m_nXRotate / 180.0f * D3DX_PI,m_nYRotate / 180.0f * D3DX_PI,m_nZRotate / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Create compound.
	m_pDoc->application->createCompound(CCompoundPlusObject::getClassCode(),m_fMass,scaling,rotation,position);
}
