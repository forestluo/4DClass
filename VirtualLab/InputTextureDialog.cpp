// InputTextureDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "InputTextureDialog.h"
#include "afxdialogex.h"

// CInputTextureDialog dialog

IMPLEMENT_DYNAMIC(CInputTextureDialog, CDialogEx)

CInputTextureDialog::CInputTextureDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputTextureDialog::IDD, pParent)
	, m_strName(_T("动态纹理"))
	, m_strDeviceName(_T(""))
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CInputTextureDialog::~CInputTextureDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CInputTextureDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DYNAMIC_TEXTURE_NAME, m_strName);
	DDX_Control(pDX, IDC_COMBO_DEVICE_LIST, m_devices);
	DDX_CBString(pDX, IDC_COMBO_DEVICE_LIST, m_strDeviceName);
}


BEGIN_MESSAGE_MAP(CInputTextureDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputTextureDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputTextureDialog message handlers

BOOL CInputTextureDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add devices.
	m_pDoc->addDeviceOptions(&m_devices);
	//Add filters.
	m_pDoc->addFilterOptions(&m_devices);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CInputTextureDialog::OnBnClickedOk()
{
	//Update data.
	UpdateData(TRUE);

	//Get texture name.
	CNormalString textureName(m_strName.GetBuffer());
	//Get device name.
	CNormalString deviceName(m_strDeviceName.GetBuffer());

	//Check result.
	if(textureName.length() <= 0)
	{
		//Show message.
		AfxMessageBox(_T("没有定义动态纹理名称。\n\n请输入并确定动态纹理的名称。"), MB_OK | MB_ICONSTOP);
		return;
	}

	//Check result.
	if(deviceName.length() <= 0)
	{
		//Show message.
		AfxMessageBox(_T("没有定义动态纹理所依赖的输入设备。\n\n请选择并确定输入设备的名称。"), MB_OK | MB_ICONSTOP);
		return;
	}

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Check result.
	if(m_pDoc->application->getResource(textureName) != NULL)
	{
		//Show message.
		AfxMessageBox(_T("纹理名称与现有资源名称相重复。\n\n请输入并确定动态纹理的名称。"), MB_OK | MB_ICONSTOP);
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Add resources.
	m_pDoc->addInputTexture(textureName,deviceName);
}
