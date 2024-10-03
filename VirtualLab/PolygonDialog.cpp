// PolygonDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "PolygonDialog.h"
#include "afxdialogex.h"


// CPolygonDialog dialog

IMPLEMENT_DYNAMIC(CPolygonDialog, CDialogEx)

	CPolygonDialog::CPolygonDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CPolygonDialog::IDD, pParent)
	, m_fMass(1.0f)
	, m_fRadius(0.2f)
	, m_nXRotate(0)
	, m_nYRotate(0)
	, m_nZRotate(0)
	, m_fXPosition(0.0f)
	, m_fYPosition(2.0f)
	, m_fZPosition(0.0f)
{
	//No one was selected.
	m_nFaces = 0;

#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CPolygonDialog::~CPolygonDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CPolygonDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MASS, m_fMass);
	DDV_MinMaxFloat(pDX, m_fMass, 0.0f, 10000.0f);

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


BEGIN_MESSAGE_MAP(CPolygonDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPolygonDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CPolygonDialog message handlers


void CPolygonDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Get current selection.
	int nSelection = m_polygon.GetCurSel();
	//Get selection.
	switch(nSelection)
	{
	case 0:
		m_nFaces = 4;
		break;
	case 1:
		m_nFaces = 6;
		break;
	case 2:
		m_nFaces = 8;
		break;
	case 3:
		m_nFaces = 12;
		break;
	case 4:
		m_nFaces = 20;
		break;
	default:
		m_nFaces = 0;
	}
	//Set scale.
	C4DVector3 scale(m_fRadius,m_fRadius,m_fRadius);
	//Set position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotate.
	C4DVector3 rotation(m_nXRotate / 180.0f * D3DX_PI,m_nYRotate / 180.0f * D3DX_PI,m_nZRotate / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Check face.
	switch(m_nFaces)
	{
	case 4:
		//Create model.	
		m_pDoc->application->createModel(CPrimitiveAttribute::polygon4Primitive,m_fMass,scale,rotation,position);
		break;
	case 6:
		//Create model.	
		m_pDoc->application->createModel(CPrimitiveAttribute::polygon6Primitive,m_fMass,scale,rotation,position);
		break;
	case 8:
		//Create model.	
		m_pDoc->application->createModel(CPrimitiveAttribute::polygon8Primitive,m_fMass,scale,rotation,position);
		break;
	case 12:
		//Create model.	
		m_pDoc->application->createModel(CPrimitiveAttribute::polygon12Primitive,m_fMass,scale,rotation,position);
		break;
	case 20:
		//Create model.	
		m_pDoc->application->createModel(CPrimitiveAttribute::polygon20Primitive,m_fMass,scale,rotation,position);
		break;
	}
}
