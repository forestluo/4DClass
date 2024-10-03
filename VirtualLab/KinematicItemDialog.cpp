// KinematicItemDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "KinematicItemDialog.h"
#include "afxdialogex.h"

// CKinematicItemDialog dialog

IMPLEMENT_DYNAMIC(CKinematicItemDialog, CDialogEx)

	CKinematicItemDialog::CKinematicItemDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CKinematicItemDialog::IDD, pParent)
	, m_strName(_T("可控矩阵"))
	, m_strDeviceName(_T(""))
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CKinematicItemDialog::~CKinematicItemDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CKinematicItemDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONTROLLED_BALL, m_strName);
	DDX_Control(pDX, IDC_COMBO_DEVICE_LIST, m_devices);
	DDX_CBString(pDX, IDC_COMBO_DEVICE_LIST, m_strDeviceName);
}


BEGIN_MESSAGE_MAP(CKinematicItemDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CKinematicItemDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CKinematicItemDialog message handlers

BOOL CKinematicItemDialog::OnInitDialog()
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

void CKinematicItemDialog::OnBnClickedOk()
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
		AfxMessageBox(_T("没有定义可控球体名称。\n\n请输入并确定可控球体的名称。"), MB_OK | MB_ICONSTOP);
		return;
	}

	//Check result.
	if(deviceName.length() <= 0)
	{
		//Show message.
		AfxMessageBox(_T("没有定义可控球体所依赖的输入设备。\n\n请选择并确定输入设备的名称。"), MB_OK | MB_ICONSTOP);
		return;
	}

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Check result.
	if(m_pDoc->application->getForeground()->getObject(primitiveName) != NULL)
	{
		//Show message.
		AfxMessageBox(_T("地形名称与现有对象名称相重复。\n\n请输入并确定动态地形的名称。"), MB_OK | MB_ICONSTOP);
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add resources.
	m_pDoc->addKinematicItemArray(primitiveName,deviceName);
}
