// GroundMeshDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "GroundMeshDialog.h"
#include "afxdialogex.h"

// CGroundMeshDialog dialog

IMPLEMENT_DYNAMIC(CGroundMeshDialog, CDialogEx)

	CGroundMeshDialog::CGroundMeshDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CGroundMeshDialog::IDD, pParent)
	, m_strName(_T("��̬����"))
	, m_strDeviceName(_T(""))
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CGroundMeshDialog::~CGroundMeshDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CGroundMeshDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GROUND_MESH_NAME, m_strName);
	DDX_Control(pDX, IDC_COMBO_DEVICE_LIST, m_devices);
	DDX_CBString(pDX, IDC_COMBO_DEVICE_LIST, m_strDeviceName);
}


BEGIN_MESSAGE_MAP(CGroundMeshDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGroundMeshDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CGroundMeshDialog message handlers

BOOL CGroundMeshDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add devices.
	m_pDoc->addKinectOptions(&m_devices);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGroundMeshDialog::OnBnClickedOk()
{
	//Update data.
	UpdateData(TRUE);

	//Get primitive name.
	CNormalString primitiveName(m_strName.GetBuffer());
	//Get device name.
	CNormalString deviceName(m_strDeviceName.GetBuffer());

	//Check result.
	if(primitiveName.length() <= 0)
	{
		//Show message.
		AfxMessageBox(_T("û�ж��嶯̬�������ơ�\n\n�����벢ȷ����̬���ε����ơ�"), MB_OK | MB_ICONSTOP);
		return;
	}

	//Check result.
	if(deviceName.length() <= 0)
	{
		//Show message.
		AfxMessageBox(_T("û�ж��嶯̬�����������������豸��\n\n��ѡ��ȷ�������豸�����ơ�"), MB_OK | MB_ICONSTOP);
		return;
	}

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Check result.
	if(m_pDoc->application->getForeground()->getObject(primitiveName) != NULL)
	{
		//Show message.
		AfxMessageBox(_T("�������������ж����������ظ���\n\n�����벢ȷ����̬���ε����ơ�"), MB_OK | MB_ICONSTOP);
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add resources.
	m_pDoc->addInputGroundMesh(primitiveName,deviceName);
}
