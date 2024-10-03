// PutBallJointDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "CustomBallJointDialog.h"
#include "afxdialogex.h"


// CCustomBallJointDialog dialog

IMPLEMENT_DYNAMIC(CCustomBallJointDialog, CDialogEx)

CCustomBallJointDialog::CCustomBallJointDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCustomBallJointDialog::IDD, pParent)
	, m_strChild(_T(""))
	, m_strParent(_T(""))
	, m_bSelfCollision(TRUE)
	, m_fXPosition(0)
	, m_fYPosition(0)
	, m_fZPosition(0)
	, m_nMaxConeAngle(175)
	, m_nMaxTwistAngle(-90)
	, m_nMinTwistAngle(+90)
	, m_fXMajor(0)
	, m_fYMajor(0)
	, m_fZMajor(0)
	, m_nXRMajor(0)
	, m_nYRMajor(0)
	, m_nZRMajor(0)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;

	//Get default attribute.
	CJointAttribute attribute = CWorldJointObject::getDefaultAttribute(CJointAttribute::customBallJoint);
	//Set major.
	m_fXMajor = attribute.jointData.jointCustomBall.direction[0];
	m_fYMajor = attribute.jointData.jointCustomBall.direction[1];
	m_fZMajor = attribute.jointData.jointCustomBall.direction[2];
}

CCustomBallJointDialog::~CCustomBallJointDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CCustomBallJointDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHILD, m_children);
	DDX_CBString(pDX, IDC_COMBO_CHILD, m_strChild);
	DDX_Control(pDX, IDC_COMBO_PARENT, m_parents);
	DDX_CBString(pDX, IDC_COMBO_PARENT, m_strParent);
	DDX_Check(pDX, IDC_CHECK_SELF_COLLISION, m_bSelfCollision);
	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_MAX_CONE_ANGLE, m_nMaxConeAngle);
	DDV_MinMaxInt(pDX, m_nMaxConeAngle, 5, 175);
	DDX_Text(pDX, IDC_EDIT_MAX_TWIST_ANGLE, m_nMaxTwistAngle);
	DDV_MinMaxInt(pDX, m_nMaxTwistAngle, -90, 90);
	DDX_Text(pDX, IDC_EDIT_MIN_TWIST_ANGLE, m_nMinTwistAngle);
	DDV_MinMaxInt(pDX, m_nMinTwistAngle, -90, 90);
	DDX_Text(pDX, IDC_EDIT_MAJOR_X, m_fXMajor);
	DDV_MinMaxFloat(pDX, m_fXMajor, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_MAJOR_Y, m_fYMajor);
	DDV_MinMaxFloat(pDX, m_fYMajor, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_MAJOR_Z, m_fZMajor);
	DDV_MinMaxFloat(pDX, m_fZMajor, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_MAJOR_XR, m_nXRMajor);
	DDV_MinMaxInt(pDX, m_nXRMajor, -360, 360);
	DDX_Text(pDX, IDC_EDIT_MAJOR_YR, m_nYRMajor);
	DDV_MinMaxInt(pDX, m_nYRMajor, -360, 360);
	DDX_Text(pDX, IDC_EDIT_MAJOR_ZR, m_nZRMajor);
	DDV_MinMaxInt(pDX, m_nZRMajor, -360, 360);
}


BEGIN_MESSAGE_MAP(CCustomBallJointDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCustomBallJointDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCustomBallJointDialog message handlers

BOOL CCustomBallJointDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add joint parents.
	m_pDoc->addParentOptions(&m_parents);
	//Add joint children.
	m_pDoc->addChildrenOptions(&m_children);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomBallJointDialog::OnBnClickedOk()
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
	attribute.setType(CJointAttribute::customBallJoint);
	//Set stiffness.
	attribute.stiffness = 1.0f;
	//Set self collision.
	attribute.selfCollision = m_bSelfCollision;
	//Position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set max cone angle.
	attribute.jointData.jointCustomBall.maxConeAngle = m_nMaxConeAngle * D3DX_PI / 180.0f;
	//Set max twist angle.
	attribute.jointData.jointCustomBall.maxTwistAngle = m_nMaxTwistAngle * D3DX_PI / 180.0f;
	//Set min twist angle.
	attribute.jointData.jointCustomBall.minTwistAngle = m_nMinTwistAngle * D3DX_PI / 180.0f;
	//Get rotation.
	C4DQuaternion rotation(C4DVector3(m_nXRMajor * D3DX_PI / 180.0f,m_nYRMajor * D3DX_PI / 180.0f,m_nZRMajor * D3DX_PI / 180.0f));
	//Rotate a default vector.
	C4DVector3 direction = rotation.rotate(CWorldJointObject::getDefaultMajorDirection(CJointAttribute::customBallJoint));
	//Set direction.
	attribute.jointData.jointCustomBall.direction[0] = direction.x();
	attribute.jointData.jointCustomBall.direction[1] = direction.y();
	attribute.jointData.jointCustomBall.direction[2] = direction.z();
	//Create joint.
	m_pDoc->application->createJoint(attribute,childName,position,parentName);
}
