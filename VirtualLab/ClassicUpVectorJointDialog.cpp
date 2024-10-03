// ClassicUpVectorJointDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "ClassicUpVectorJointDialog.h"
#include "afxdialogex.h"


// CClassicUpVectorJointDialog dialog

IMPLEMENT_DYNAMIC(CClassicUpVectorJointDialog, CDialogEx)

CClassicUpVectorJointDialog::CClassicUpVectorJointDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CClassicUpVectorJointDialog::IDD, pParent)
	, m_strChild(_T(""))
	, m_fXPosition(0)
	, m_fYPosition(0)
	, m_fZPosition(0)
	, m_nXRotate(0)
	, m_nZRotate(0)
	, m_nYRotate(0)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CClassicUpVectorJointDialog::~CClassicUpVectorJointDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CClassicUpVectorJointDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_COMBO_CHILD, m_children);
	DDX_CBString(pDX, IDC_COMBO_CHILD, m_strChild);
	
	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0, 500.0);

	DDX_Text(pDX, IDC_EDIT_XR, m_nXRotate);
	DDV_MinMaxInt(pDX, m_nXRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR, m_nYRotate);
	DDV_MinMaxInt(pDX, m_nZRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR, m_nZRotate);
	DDV_MinMaxInt(pDX, m_nYRotate, -360, 360);
}


BEGIN_MESSAGE_MAP(CClassicUpVectorJointDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CClassicUpVectorJointDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CClassicUpVectorJointDialog message handlers

BOOL CClassicUpVectorJointDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add joint children.
	m_pDoc->addChildrenOptions(&m_children);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CClassicUpVectorJointDialog::OnBnClickedOk()
{
	//Update data.
	UpdateData(TRUE);

	//Get child name.
	CNormalString childName(m_strChild.GetBuffer());

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif

	//Joint attribute.
	CJointAttribute attribute;
	//Set type.
	attribute.setType(CJointAttribute::classicUpVectorJoint);
	//Set stiffness.
	attribute.stiffness = 1.0f;
	//Set self collision.
	attribute.selfCollision = _TRUE;
	//Position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Get rotation.
	C4DQuaternion rotation(C4DVector3(m_nXRotate * D3DX_PI / 180.0f,m_nYRotate * D3DX_PI / 180.0f,m_nZRotate * D3DX_PI / 180.0f));
	//Rotate a default vector.
	C4DVector3 direction = rotation.rotate(CWorldJointObject::getDefaultMajorDirection(CJointAttribute::classicUpVectorJoint));
	//Set direction.
	attribute.jointData.jointClassicUpVector.direction[0] = direction.x();
	attribute.jointData.jointClassicUpVector.direction[1] = direction.y();
	attribute.jointData.jointClassicUpVector.direction[2] = direction.z();
	//Create joint.
	m_pDoc->application->createJoint(attribute,childName,position);
}

