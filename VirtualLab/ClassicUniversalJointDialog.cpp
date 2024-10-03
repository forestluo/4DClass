// ClassicUniversalJointDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "ClassicUniversalJointDialog.h"
#include "afxdialogex.h"


// CClassicUniversalJointDialog dialog

IMPLEMENT_DYNAMIC(CClassicUniversalJointDialog, CDialogEx)

CClassicUniversalJointDialog::CClassicUniversalJointDialog(bool bChildOnly,CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CClassicUniversalJointDialog::IDD, pParent)
	, m_bChildOnly(bChildOnly)
	, m_strChild(_T(""))
	, m_strParent(_T(""))
	, m_fStiffness(1.0f)
	, m_bSelfCollision(TRUE)
	, m_fXPosition(0)
	, m_fYPosition(0)
	, m_fZPosition(0)
	, m_nXRotate(0)
	, m_nYRotate(0)
	, m_nZRotate(0)
	, m_nXRotate2(0)
	, m_nYRotate2(0)
	, m_nZRotate2(0)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CClassicUniversalJointDialog::~CClassicUniversalJointDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CClassicUniversalJointDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHILD, m_children);
	DDX_CBString(pDX, IDC_COMBO_CHILD, m_strChild);
	DDX_Control(pDX, IDC_COMBO_PARENT, m_parents);
	DDX_CBString(pDX, IDC_COMBO_PARENT, m_strParent);
	DDX_Text(pDX, IDC_EDIT_STIFFNESS, m_fStiffness);
	DDV_MinMaxFloat(pDX, m_fStiffness, 0.0, 1.0);
	DDX_Check(pDX, IDC_CHECK_SELF_COLLISION, m_bSelfCollision);
	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_XR, m_nXRotate);
	DDV_MinMaxInt(pDX, m_nXRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR, m_nYRotate);
	DDV_MinMaxInt(pDX, m_nYRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR, m_nZRotate);
	DDV_MinMaxInt(pDX, m_nZRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_XR2, m_nXRotate2);
	DDV_MinMaxInt(pDX, m_nXRotate2, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR2, m_nYRotate2);
	DDV_MinMaxInt(pDX, m_nYRotate2, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR2, m_nZRotate2);
	DDV_MinMaxInt(pDX, m_nZRotate2, -360, 360);
}


BEGIN_MESSAGE_MAP(CClassicUniversalJointDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CClassicUniversalJointDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CClassicUniversalJointDialog message handlers


BOOL CClassicUniversalJointDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add joint parents.
	m_pDoc->addParentOptions(&m_parents);
	//Add joint children.
	m_pDoc->addChildrenOptions(&m_children);
	//Check child only.
	m_parents.EnableWindow(m_bChildOnly ? FALSE : TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CClassicUniversalJointDialog::OnBnClickedOk()
{
	//Update data.
	UpdateData(TRUE);

	//Get child name.
	CNormalString childName(m_strChild.GetBuffer());
	//Get parent name.
	CNormalString parentName(m_strParent.GetBuffer());

	//Check result.
	if(childName.length() <= 0 && parentName.length() > 0)
	{
		//Show message.
		AfxMessageBox(_T("没有定义子链接体，但是定义了父链接体。\n\n请选择并确定子链接体。"), MB_OK | MB_ICONSTOP);
		return;
	}

	//Check result.
	if(childName.length() > 0 && parentName.length() > 0 && childName == parentName)
	{
		//Show message.
		AfxMessageBox(_T("子链接体和父链接体不能是同一个物体。\n\n请重新选择子链接体或者父链接体。"), MB_OK | MB_ICONSTOP);
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif

	//Joint attribute.
	CJointAttribute attribute;
	//Set type.
	attribute.setType(CJointAttribute::classicUniversalJoint);
	//Set stiffness.
	attribute.stiffness = m_fStiffness;
	//Set self collision.
	attribute.selfCollision = m_bSelfCollision;
	//Position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Get rotation.
	C4DQuaternion rotation1(C4DVector3(m_nXRotate * D3DX_PI / 180.0f,m_nYRotate * D3DX_PI / 180.0f,m_nZRotate * D3DX_PI / 180.0f));
	//Rotate a default vector.
	C4DVector3 majorDirection = rotation1.rotate(CWorldJointObject::getDefaultMajorDirection(CJointAttribute::classicUniversalJoint));
	//Set direction.
	attribute.jointData.jointClassicUniversal.majorDirection[0] = majorDirection.x();
	attribute.jointData.jointClassicUniversal.majorDirection[1] = majorDirection.y();
	attribute.jointData.jointClassicUniversal.majorDirection[2] = majorDirection.z();
	//Get rotation.
	C4DQuaternion rotation2(C4DVector3(m_nXRotate2 * D3DX_PI / 180.0f,m_nYRotate2 * D3DX_PI / 180.0f,m_nZRotate2 * D3DX_PI / 180.0f));
	//Rotate a default vector.
	C4DVector3 minorDirection = rotation2.rotate(CWorldJointObject::getDefaultMinorDirection(CJointAttribute::classicUniversalJoint));
	//Set direction.
	attribute.jointData.jointClassicUniversal.minorDirection[0] = minorDirection.x();
	attribute.jointData.jointClassicUniversal.minorDirection[1] = minorDirection.y();
	attribute.jointData.jointClassicUniversal.minorDirection[2] = minorDirection.z();
	//Create joint.
	m_pDoc->application->createJoint(attribute,childName,position,parentName);
}
