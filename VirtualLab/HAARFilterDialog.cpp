// HAARFilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "HAARFilterDialog.h"
#include "afxdialogex.h"


// CHAARFilterDialog dialog

IMPLEMENT_DYNAMIC(CHAARFilterDialog, CDialogEx)

CHAARFilterDialog::CHAARFilterDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CHAARFilterDialog::IDD, pParent)
	, m_strName(_T("����ʶ��"))
	, m_strDeviceName(_T(""))
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CHAARFilterDialog::~CHAARFilterDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CHAARFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DATA_FILTER_NAME, m_strName);
	DDX_Control(pDX, IDC_COMBO_DEVICE_LIST, m_devices);
	DDX_CBString(pDX, IDC_COMBO_DEVICE_LIST, m_strDeviceName);
}


BEGIN_MESSAGE_MAP(CHAARFilterDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHAARFilterDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CHAARFilterDialog message handlers

BOOL CHAARFilterDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add devices.
	m_pDoc->addDeviceOptions(&m_devices);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CHAARFilterDialog::OnBnClickedOk()
{
	//Update data.
	UpdateData(TRUE);

	//Get filter name.
	CNormalString filterName(m_strName.GetBuffer());
	//Get device name.
	CNormalString deviceName(m_strDeviceName.GetBuffer());

	//Check result.
	if(filterName.length() <= 0)
	{
		//Show message.
		AfxMessageBox(_T("û�ж������ݹ��������ơ�\n\n�����벢ȷ�����ݹ����������ơ�"), MB_OK | MB_ICONSTOP);
		return;
	}

	//Check result.
	if(deviceName.length() <= 0)
	{
		//Show message.
		AfxMessageBox(_T("û�ж������ݹ������������������豸��\n\n��ѡ��ȷ�������豸�����ơ�"), MB_OK | MB_ICONSTOP);
		return;
	}

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Check result.
	if(m_pDoc->application->getResource(filterName) != NULL)
	{
		//Show message.
		AfxMessageBox(_T("���ݹ�����������������Դ�������ظ���\n\n�����벢ȷ�����ݹ����������ơ�"), MB_OK | MB_ICONSTOP);
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add resources.
	m_pDoc->addHAARFilter(filterName,deviceName);
}
