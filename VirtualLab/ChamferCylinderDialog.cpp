// CapsuleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "ChamferCylinderDialog.h"
#include "afxdialogex.h"


// CChamferCylinderDialog dialog

IMPLEMENT_DYNAMIC(CChamferCylinderDialog, CDialogEx)

CChamferCylinderDialog::CChamferCylinderDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CChamferCylinderDialog::IDD, pParent)
	, m_fMass(1.0f)
	, m_fRadius(0.2f)
	, m_fHeight(0.08f)
	, m_nXRotate(0)
	, m_nYRotate(0)
	, m_nZRotate(0)
	, m_fXPosition(0)
	, m_fYPosition(2.0f)
	, m_fZPosition(0)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CChamferCylinderDialog::~CChamferCylinderDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CChamferCylinderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MASS, m_fMass);
	DDV_MinMaxFloat(pDX, m_fMass, 0.0f, 10000.0f);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_fRadius);
	DDV_MinMaxFloat(pDX, m_fRadius, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_fHeight);
	DDV_MinMaxFloat(pDX, m_fHeight, 0.01f, 100.0f);

	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0f, 500.0f);
	
	DDX_Text(pDX, IDC_EDIT_XR, m_nXRotate);
	DDV_MinMaxInt(pDX, m_nXRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR, m_nYRotate);
	DDV_MinMaxInt(pDX, m_nYRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR, m_nZRotate);
	DDV_MinMaxInt(pDX, m_nZRotate, -360, 360);
}


BEGIN_MESSAGE_MAP(CChamferCylinderDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChamferCylinderDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CChamferCylinderDialog message handlers


void CChamferCylinderDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Geometry.
	CPrimitiveAttribute attribute;
	//Set type.
	attribute.setType(CPrimitiveAttribute::chamferCylider0Primitive);
	//Set height.
	attribute.primitiveData.chamferCylinder.height = m_fHeight;
	//Set radius.
	attribute.primitiveData.chamferCylinder.radius = m_fRadius;

	//Set scale.
	C4DVector3 scale(1.0,1.0,1.0);
	//Set position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotation.
	C4DVector3 rotation(m_nXRotate / 180.0f * D3DX_PI,m_nYRotate / 180.0f * D3DX_PI,m_nZRotate / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add chamfer cylinder into scene.
	m_pDoc->application->createModel(attribute,m_fMass,scale,rotation,position);
}
