// Custom6DOFJointDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "Custom6DOFJointDialog.h"
#include "afxdialogex.h"


// CCustom6DOFJointDialog dialog

IMPLEMENT_DYNAMIC(CCustom6DOFJointDialog, CDialogEx)

CCustom6DOFJointDialog::CCustom6DOFJointDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCustom6DOFJointDialog::IDD, pParent)
	, m_strChild(_T(""))
	, m_fXPosition(0)
	, m_fYPosition(0)
	, m_fZPosition(0)
	, m_nXRotate(0)
	, m_nYRotate(0)
	, m_nZRotate(0)
	, m_fXLimitMin(0)
	, m_fXLimitMax(0)
	, m_fYLimitMin(0)
	, m_fYLimitMax(0)
	, m_fZLimitMin(0)
	, m_fZLimitMax(0)
	, m_nXRLimitMin(0)
	, m_nXRLimitMax(0)
	, m_nYRLimitMin(0)
	, m_nYRLimitMax(0)
	, m_nZRLimitMin(0)
	, m_nZRLimitMax(0)
	, m_strParent(_T(""))
	, m_fStiffness(1.0)
	, m_bSelfCollision(TRUE)
	, m_fXMajor(0)
	, m_fYMajor(0)
	, m_fZMajor(0)
	, m_nXRMajor(0)
	, m_nYRMajor(0)
	, m_nZRMajor(0)
	, m_fXMinor(0)
	, m_fYMinor(0)
	, m_fZMinor(0)
	, m_nXRMinor(0)
	, m_nYRMinor(0)
	, m_nZRMinor(0)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;

	//Get default attribute.
	CJointAttribute attribute = CWorldJointObject::getDefaultAttribute(CJointAttribute::custom6DOFJoint);
	//Set limit min.
	m_fXLimitMin = attribute.jointData.jointCustom6DOF.minLinearLimits[0];
	m_fYLimitMin = attribute.jointData.jointCustom6DOF.minLinearLimits[1];
	m_fZLimitMin = attribute.jointData.jointCustom6DOF.minLinearLimits[2];
	//Set limit max.
	m_fXLimitMax = attribute.jointData.jointCustom6DOF.maxLinearLimits[0];
	m_fYLimitMax = attribute.jointData.jointCustom6DOF.maxLinearLimits[1];
	m_fZLimitMax = attribute.jointData.jointCustom6DOF.maxLinearLimits[2];
	//Set rotation min.
	m_nXRLimitMin = (int)(attribute.jointData.jointCustom6DOF.minAngulaLimits[0] * 180.0f / D3DX_PI);
	m_nYRLimitMin = (int)(attribute.jointData.jointCustom6DOF.minAngulaLimits[1] * 180.0f / D3DX_PI);
	m_nZRLimitMin = (int)(attribute.jointData.jointCustom6DOF.minAngulaLimits[2] * 180.0f / D3DX_PI);
	//Set rotation max.
	m_nXRLimitMax = (int)(attribute.jointData.jointCustom6DOF.maxAngulaLimits[0] * 180.0f / D3DX_PI);
	m_nYRLimitMax = (int)(attribute.jointData.jointCustom6DOF.maxAngulaLimits[1] * 180.0f / D3DX_PI);
	m_nZRLimitMax = (int)(attribute.jointData.jointCustom6DOF.maxAngulaLimits[2] * 180.0f / D3DX_PI);
	//Set major.
	m_fXMajor = attribute.jointData.jointCustom6DOF.majorDirection[0];
	m_fYMajor = attribute.jointData.jointCustom6DOF.majorDirection[1];
	m_fZMajor = attribute.jointData.jointCustom6DOF.majorDirection[2];
	//Set minor.
	m_fXMinor = attribute.jointData.jointCustom6DOF.minorDirection[0];
	m_fYMinor = attribute.jointData.jointCustom6DOF.minorDirection[1];
	m_fZMinor = attribute.jointData.jointCustom6DOF.minorDirection[2];
}

CCustom6DOFJointDialog::~CCustom6DOFJointDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CCustom6DOFJointDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHILD, m_children);
	DDX_CBString(pDX, IDC_COMBO_CHILD, m_strChild);
	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_X_MIN, m_fXLimitMin);
	DDV_MinMaxFloat(pDX, m_fXLimitMin, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_X_MAX, m_fXLimitMax);
	DDV_MinMaxFloat(pDX, m_fXLimitMax, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y_MIN, m_fYLimitMin);
	DDV_MinMaxFloat(pDX, m_fYLimitMin, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y_MAX, m_fYLimitMax);
	DDV_MinMaxFloat(pDX, m_fYLimitMax, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z_MIN, m_fZLimitMin);
	DDV_MinMaxFloat(pDX, m_fZLimitMin, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z_MAX, m_fZLimitMax);
	DDV_MinMaxFloat(pDX, m_fZLimitMax, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_XR_MIN, m_nXRLimitMin);
	DDV_MinMaxInt(pDX, m_nXRLimitMin, -360, 360);
	DDX_Text(pDX, IDC_EDIT_XR_MAX, m_nXRLimitMax);
	DDV_MinMaxInt(pDX, m_nXRLimitMax, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR_MIN, m_nYRLimitMin);
	DDV_MinMaxInt(pDX, m_nYRLimitMin, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR_MAX, m_nYRLimitMax);
	DDV_MinMaxInt(pDX, m_nYRLimitMax, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR_MIN, m_nZRLimitMin);
	DDV_MinMaxInt(pDX, m_nZRLimitMin, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR_MAX, m_nZRLimitMax);
	DDV_MinMaxInt(pDX, m_nZRLimitMax, -360, 360);
	DDX_Control(pDX, IDC_COMBO_PARENT, m_parents);
	DDX_CBString(pDX, IDC_COMBO_PARENT, m_strParent);
	DDX_Text(pDX, IDC_EDIT_STIFFNESS, m_fStiffness);
	DDV_MinMaxFloat(pDX, m_fStiffness, 0.0, 1.0);
	DDX_Check(pDX, IDC_CHECK_SELF_COLLISION, m_bSelfCollision);
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
	DDX_Text(pDX, IDC_EDIT_MINOR_X, m_fXMinor);
	DDV_MinMaxFloat(pDX, m_fXMinor, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_MINOR_Y, m_fYMinor);
	DDV_MinMaxFloat(pDX, m_fYMinor, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_MINOR_Z, m_fZMinor);
	DDV_MinMaxFloat(pDX, m_fZMinor, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_MINOR_XR, m_nXRMinor);
	DDV_MinMaxInt(pDX, m_nXRMinor, -360, 360);
	DDX_Text(pDX, IDC_EDIT_MINOR_YR, m_nYRMinor);
	DDV_MinMaxInt(pDX, m_nYRMinor, -360, 360);
	DDX_Text(pDX, IDC_EDIT_MINOR_ZR, m_nZRMinor);
	DDV_MinMaxInt(pDX, m_nZRMinor, -360, 360);
}


BEGIN_MESSAGE_MAP(CCustom6DOFJointDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCustom6DOFJointDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCustom6DOFJointDialog message handlers


BOOL CCustom6DOFJointDialog::OnInitDialog()
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

void CCustom6DOFJointDialog::OnBnClickedOk()
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
	attribute.setType(CJointAttribute::custom6DOFJoint);
	//Set stiffness.
	attribute.stiffness = m_fStiffness;
	//Set self collision.
	attribute.selfCollision = m_bSelfCollision;
	//Position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set min linear limits.
	attribute.jointData.jointCustom6DOF.minLinearLimits[0] = m_fXLimitMin;
	attribute.jointData.jointCustom6DOF.minLinearLimits[1] = m_fYLimitMin;
	attribute.jointData.jointCustom6DOF.minLinearLimits[2] = m_fZLimitMin;
	//Set max linear limits.
	attribute.jointData.jointCustom6DOF.maxLinearLimits[0] = m_fXLimitMax;
	attribute.jointData.jointCustom6DOF.maxLinearLimits[1] = m_fYLimitMax;
	attribute.jointData.jointCustom6DOF.maxLinearLimits[2] = m_fZLimitMax;
	//Set min angular limits.
	attribute.jointData.jointCustom6DOF.minAngulaLimits[0] = m_nXRLimitMin * D3DX_PI / 180.0f;
	attribute.jointData.jointCustom6DOF.minAngulaLimits[1] = m_nYRLimitMin * D3DX_PI / 180.0f;
	attribute.jointData.jointCustom6DOF.minAngulaLimits[2] = m_nZRLimitMin * D3DX_PI / 180.0f;
	//Set max Angular limits.
	attribute.jointData.jointCustom6DOF.maxAngulaLimits[0] = m_nXRLimitMax * D3DX_PI / 180.0f;
	attribute.jointData.jointCustom6DOF.maxAngulaLimits[1] = m_nYRLimitMax * D3DX_PI / 180.0f;
	attribute.jointData.jointCustom6DOF.maxAngulaLimits[2] = m_nZRLimitMax * D3DX_PI / 180.0f;
	//Get rotation.
	C4DQuaternion rotation1(C4DVector3(m_nXRMajor * D3DX_PI / 180.0f,m_nYRMajor * D3DX_PI / 180.0f,m_nZRMajor * D3DX_PI / 180.0f));
	//Rotate a default vector.
	C4DVector3 majorDirection = rotation1.rotate(CWorldJointObject::getDefaultMajorDirection(CJointAttribute::custom6DOFJoint));
	//Set direction.
	attribute.jointData.jointCustom6DOF.majorDirection[0] = majorDirection.x();
	attribute.jointData.jointCustom6DOF.majorDirection[1] = majorDirection.y();
	attribute.jointData.jointCustom6DOF.majorDirection[2] = majorDirection.z();
	//Get rotation.
	C4DQuaternion rotation2(C4DVector3(m_nXRMinor * D3DX_PI / 180.0f,m_nYRMinor * D3DX_PI / 180.0f,m_nZRMinor * D3DX_PI / 180.0f));
	//Rotate a default vector.
	C4DVector3 minorDirection = rotation1.rotate(CWorldJointObject::getDefaultMinorDirection(CJointAttribute::custom6DOFJoint));
	//Set direction.
	attribute.jointData.jointCustom6DOF.minorDirection[0] = minorDirection.x();
	attribute.jointData.jointCustom6DOF.minorDirection[1] = minorDirection.y();
	attribute.jointData.jointCustom6DOF.minorDirection[2] = minorDirection.z();
	//Create joint.
	m_pDoc->application->createJoint(attribute,childName,position,parentName);
}

