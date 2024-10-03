// CustomSliderJointDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "CustomSliderJointDialog.h"
#include "afxdialogex.h"


// CCustomSliderJointDialog dialog

IMPLEMENT_DYNAMIC(CCustomSliderJointDialog, CDialogEx)

CCustomSliderJointDialog::CCustomSliderJointDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCustomSliderJointDialog::IDD, pParent)
	, m_strChild(_T(""))
	, m_strParent(_T(""))
	, m_fXPosition(0)
	, m_fYPosition(0)
	, m_fZPosition(0)
	, m_bSelfCollision(TRUE)
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
	CJointAttribute attribute = CWorldJointObject::getDefaultAttribute(CJointAttribute::customSliderJoint);
	//Set major.
	m_fXMajor = attribute.jointData.jointCustomSlider.direction[0];
	m_fYMajor = attribute.jointData.jointCustomSlider.direction[1];
	m_fZMajor = attribute.jointData.jointCustomSlider.direction[2];
}

CCustomSliderJointDialog::~CCustomSliderJointDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CCustomSliderJointDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHILD, m_children);
	DDX_CBString(pDX, IDC_COMBO_CHILD, m_strChild);
	DDX_Control(pDX, IDC_COMBO_PARENT, m_parents);
	DDX_CBString(pDX, IDC_COMBO_PARENT, m_strParent);
	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0, 500.0);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0, 500.0);
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
}


BEGIN_MESSAGE_MAP(CCustomSliderJointDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCustomSliderJointDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCustomSliderJointDialog message handlers

BOOL CCustomSliderJointDialog::OnInitDialog()
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

void CCustomSliderJointDialog::OnBnClickedOk()
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
	attribute.setType(CJointAttribute::customSliderJoint);
	//Set stiffness.
	attribute.stiffness = 1.0f;
	//Set self collision.
	attribute.selfCollision = m_bSelfCollision;
	//Position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Get rotation.
	C4DQuaternion rotation(C4DVector3(m_nXRMajor * D3DX_PI / 180.0f,m_nYRMajor * D3DX_PI / 180.0f,m_nZRMajor * D3DX_PI / 180.0f));
	//Rotate a default vector.
	C4DVector3 direction = rotation.rotate(CWorldJointObject::getDefaultMajorDirection(CJointAttribute::customSliderJoint));
	//Set direction.
	attribute.jointData.jointCustomSlider.direction[0] = direction.x();
	attribute.jointData.jointCustomSlider.direction[1] = direction.y();
	attribute.jointData.jointCustomSlider.direction[2] = direction.z();
	//Create joint.
	m_pDoc->application->createJoint(attribute,childName,position,parentName);
}
