// SphereDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "SphereDialog.h"
#include "afxdialogex.h"


// CSphereDialog dialog

IMPLEMENT_DYNAMIC(CSphereDialog, CDialogEx)

CSphereDialog::CSphereDialog(bool bHemisphere,CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSphereDialog::IDD, pParent)
	, m_bHemisphere(bHemisphere)
	, m_fMass(1.0f)
	, m_fXRadius(0.2f)
	, m_fYRadius(0.2f)
	, m_fZRadius(0.2f)
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

CSphereDialog::~CSphereDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CSphereDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MASS, m_fMass);
	DDV_MinMaxFloat(pDX, m_fMass, 0.0f, 10000.0f);

	DDX_Text(pDX, IDC_EDIT_RADIUS_X, m_fXRadius);
	DDV_MinMaxFloat(pDX, m_fXRadius, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_RADIUS_Y, m_fYRadius);
	DDV_MinMaxFloat(pDX, m_fYRadius, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_RADIUS_Z, m_fZRadius);
	DDV_MinMaxFloat(pDX, m_fZRadius, 0.01f, 10.0f);

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


BEGIN_MESSAGE_MAP(CSphereDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSphereDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CSphereDialog message handlers


void CSphereDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Set scale.
	C4DVector3 scale(m_fXRadius,m_fYRadius,m_fZRadius);
	//Set position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotate.
	C4DVector3 rotation(m_nXRotate / 180.0f * D3DX_PI,m_nYRotate / 180.0f * D3DX_PI,m_nZRotate / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Create model.	
	m_pDoc->application->createModel(m_bHemisphere ? CPrimitiveAttribute::hemisphere0Primitive : CPrimitiveAttribute::sphere0Primitive,m_fMass,scale,rotation,position);
}
