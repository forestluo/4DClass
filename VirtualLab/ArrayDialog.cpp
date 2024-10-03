// ArrayDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "ArrayDialog.h"
#include "afxdialogex.h"


// CArrayDialog dialog

IMPLEMENT_DYNAMIC(CArrayDialog, CDialogEx)

CArrayDialog::CArrayDialog(int nPrimitiveType,int nArrayType,CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CArrayDialog::IDD, pParent)
	, m_nArrayType(nArrayType)
	, m_nPrimitiveType(nPrimitiveType)
	, m_nColumn(1)
	, m_nRow(1)
	, m_fXPosition(0.0f)
	, m_fYPosition(0.0f)
	, m_fZPosition(0.0f)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	m_pDoc = pDoc;
}

CArrayDialog::~CArrayDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CArrayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X_COUNT, m_nRow);
	DDV_MinMaxInt(pDX, m_nRow, 1, 100);
	DDX_Text(pDX, IDC_EDIT_Z_COUNT, m_nColumn);
	DDV_MinMaxInt(pDX, m_nColumn, 1, 100);

	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0f, 500.0f);
}


BEGIN_MESSAGE_MAP(CArrayDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CArrayDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CArrayDialog message handlers


void CArrayDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Get scene.
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Origin.
	C4DVector3 vOrigin(m_fXPosition,m_fYPosition,m_fZPosition);
	//Check primitive type.
	if(m_nPrimitiveType == CPrimitiveAttribute::floor0Primitive)
	{
		//Add floor.
		m_pDoc->application->createFloor(m_nArrayType,m_nRow,m_nColumn,vOrigin);
	}
	else if(m_nPrimitiveType == CPrimitiveAttribute::sphere0Primitive)
	{
		//Add sphere.
		m_pDoc->application->createSphereArray(m_nArrayType,m_nRow,m_nColumn,vOrigin);
	}
	else if(m_nPrimitiveType == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Add cuboid.
		m_pDoc->application->createCuboidArray(m_nArrayType,m_nRow,m_nColumn,vOrigin);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}
